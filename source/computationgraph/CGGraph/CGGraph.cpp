// source/computationgraph/CGGraph/CGGraph.cpp
//
// Author: Stephen Elliott
//
// Date: 2025-02-20
//
// Description: CGGraph class in computationgraph namespace. Holds
//              CGNodes and manages execution of computation graph
//              mathematics.
//
// Usage: Called by Model class.
//

// using namespace tensorops;

#include "./CGGraph.h"
#include <stack>

using namespace datahandlers;

namespace computationgraph
{

// public
CGGraph::CGGraph() : last_loss_(nullptr), is_topo_cache_valid_(false) {}

void CGGraph::add_neural_layer(int width) {
    // Invalidate the cache
    is_topo_cache_valid_ = false;

    // Create an object to hold the new nodes in the layer
    std::vector<SharedCGNodePtr> new_layer = {};

    // Create "width" number of new nodes
    for (int i = 0; i < width; i++) {
        SharedCGNodePtr new_node = std::make_shared<CGNode>();        
        new_layer.push_back(new_node);
    };

    // If the graph is empty,
    if (dims_.empty()) {
        // For each node in the new layer
        for (int i = 0; i < width; i++) {
            // Add the node to the adjacency list
            graph_adj_list_.insert({new_layer[i], std::vector<SharedCGNodePtr>()});
        }

    } else {
        // Otherwise, add the new layer to the CGGraph

        // First, point the final layer of the graph to the new nodes
        // Get the last layer of the graph
        int j = dims_.back();
        std::vector<SharedCGNodePtr> reverse_topo = reverse_topo_sort_();

        // For each node in the last layer of the graph,
        for (int i = 0; i < j; i++) {
            SharedCGNodePtr outer_node = reverse_topo[i];  // debug: segfault here

            // For each node in the new layer,
            for (int w = 0; w < width; w++) {
                SharedCGNodePtr new_node = new_layer[w];

                // Add the new node to the dependencies of the outer node
                graph_adj_list_[outer_node].push_back(new_node);
            }
        }

        // Second, add the new nodes to the graph itself
        // For each node in the new layer
        for (int i = 0; i < width; i++) {
            // Add the node to the adjacency list
            graph_adj_list_.insert({new_layer[i], std::vector<SharedCGNodePtr>()});
        }
    }

    // Update the dimension vector
    dims_.push_back(width);
}

void CGGraph::forward(DataLoader::Observation& observation) {
    // Retrieve the inputs
    SharedTensorPtr inputs = std::make_shared<torch::Tensor>(observation.input);
    // ^ todo: move ptr construction to DataLoader

    // For each layer in the graph
    std::vector<SharedCGNodePtr> topo_sorted_graph = topo_sort_();

    int layer_count = dims_.size();
    for (int layer_idx = 0; layer_idx < layer_count; layer_idx++) {
        // Work out the start index of the layer
        int layer_start = std::accumulate(dims_.begin(), dims_.begin() + layer_idx, 0);

        // For each node in the layer
        int nodes_in_layer = dims_[layer_idx];
        torch::Tensor current_layer_activation_tally = torch::empty({1, 1});
        
        for (int i = 0; i < nodes_in_layer; i++) {
            int current_node_idx = layer_start + i;
            SharedCGNodePtr node = topo_sorted_graph[current_node_idx];

            // Activate the node
            node->compute_activations(inputs);

            // Sum the node's activations with the current layer tally
            torch::Tensor this_node_activations = *(node->get_current_activations());
            current_layer_activation_tally = current_layer_activation_tally + this_node_activations;
        }

        // After a layer is complete,
        // Mean the activations across the layer
        torch::Tensor mean_activations = torch::mean(current_layer_activation_tally, 2);

        // Update the inputs for the next layer
        inputs = std::make_shared<torch::Tensor>(mean_activations);
    }


    // Retrieve the ouputs and predicted targets
    torch::Tensor targets = observation.target;
    torch::Tensor predicted_targets = *inputs;

    // Compute and save the loss
    torch::Tensor error = torch::sub(targets, predicted_targets);
    torch::Tensor loss = torch::mean(torch::square(error));
    last_loss_ = std::make_shared<torch::Tensor>(loss);
}

void CGGraph::backward() {
    // Executes backpropagation
    // Retrieve the adjacency list in reverse topo order
    std::vector<SharedCGNodePtr> sorted_nodes = reverse_topo_sort_();

    // For each node in the sorted list
    for (SharedCGNodePtr& node : sorted_nodes) {
        // Compute the partial derivatives of the ReLU wrt the loss
        node->compute_gradients(last_loss_);
    }

    // Set up a variable to store mean layer activations
    std::vector<torch::Tensor> mean_layer_gradients;
    
    // todo: factor out layer retrieval to allow easier layer-wise traversal
    // For each layer in the graph
    std::vector<SharedCGNodePtr> topo_sorted_graph = topo_sort_();

    int layer_count = dims_.size();
    for (int layer_idx = 0; layer_idx < layer_count; layer_idx++) {
        // Work out the start index of the layer
        int layer_start = std::accumulate(dims_.begin(), dims_.begin() + layer_idx, 0);

        // For each node in the layer
        int nodes_in_layer = dims_[layer_idx];
        torch::Tensor curr_layer_tally_ = torch::zeros_like(*(topo_sorted_graph[0]->get_current_gradients()));

        for (int node_idx = 0; node_idx < nodes_in_layer; node_idx++) {
            // Sum its gradients with the tally
            curr_layer_tally_[layer_idx] += *(topo_sorted_graph[node_idx]->get_current_gradients());
        };
        torch::Tensor layer_activations_mean = torch::mean(curr_layer_tally_);
        
        // Append the mean to the data vector
        mean_layer_gradients.push_back(layer_activations_mean);
    };
    
    // Optimise the weights and biases
    optimise_(mean_layer_gradients);

}

std::vector<int> CGGraph::get_graph_dimensions() {
    return dims_;
}

SharedTensorPtr CGGraph::get_last_loss() {
    return last_loss_;
}

std::vector<SharedCGNodePtr> CGGraph::topo_sort_() {
    // todo: add cache and dfs tests

    // note: A topological sort of the DAG is a linear ordering of all its vertices such that if 
    //       G contains an edge (u,v) then u appears before v in the ordering. (p573 CLRS)
    //       There are two implementations for serial computation of the topo sort,
    //       Kahn's Algorithm and the post-order DFS algorithm described by CLRS. Both are O(V+E).
    //       We implement the DFS algorithm, for more practice with DFS can't hurt.
    
    // If the cache is valid, return it
    if (is_topo_cache_valid_) {
        return topo_forward_ordering_cache_;
    };

    // Otherwise, the cache is not valid and we need to compute a new sort.
    // Set up a stack and a flag map mapping vertices to their visited status
    std::stack<SharedCGNodePtr> st;
    std::unordered_map<SharedCGNodePtr, bool> visited;

    for (auto& pair : graph_adj_list_) {
        visited[pair.first] = false;
    }

    // Define the dfs_visit function
    std::function<void(SharedCGNodePtr)> dfs_visit = [&](SharedCGNodePtr node) {
        visited[node] = true; // Mark the current node as visited

        // Recur for all its unvisited children
        for (auto& child : graph_adj_list_[node]) {
            if (!visited[child]) {
                dfs_visit(child);
            }
        }

        // When all subtree searches terminate, update the stack with this node
        st.push(node);
    };

    // Pick an unvisited vertex to start at and dfs all nodes in the graph
    for (auto& pair : graph_adj_list_) {
        if (!visited[pair.first]) {
            dfs_visit(pair.first);
        }
    }

    // The resulting stack is a reverse topological ordering of the nodes.
    // Pop from the stack to yield a forward topological ordering.
    std::vector<SharedCGNodePtr> forward_ordering;
    while (!st.empty()) {
        forward_ordering.push_back(st.top());
        st.pop();
    }

    // Save and validate the cache
    topo_forward_ordering_cache_ = forward_ordering;
    is_topo_cache_valid_ = true;

    return forward_ordering;
}

std::vector<SharedCGNodePtr> CGGraph::reverse_topo_sort_() { // TODO: add caching
    // Turn the adjacency list into an ordered vector of nodes, finish-to-start
    std::vector<SharedCGNodePtr> sorted = topo_sort_();
    std::reverse(sorted.begin(), sorted.end());
    return sorted;
}

// private
void CGGraph::optimise_(std::vector<torch::Tensor> mean_layer_gradients) {
    // Retrieve the graph
    std::vector<SharedCGNodePtr> graph = topo_sort_();

    // Set a fixed learning rate
    float learning_rate = 0.05;

    // For each node
    for (SharedCGNodePtr node : graph) {
        // Execute the gradient update rule using the last stored gradient (fixed learning rate)
        node->update_weight(learning_rate);
    }

    // TODO: update biases
    // Compute the new bias for each layer
    for (int i = 0; i < dims_.size(); i++) {
        // Get the start index of the layer
        int layer_start = std::accumulate(dims_.begin(), dims_.begin() + i, 0);

        // Get the number of nodes in the layer
        int nodes_in_layer = dims_[i];

        // Compute the new bias from the mean_layer_gradients
        float new_bias = graph[layer_start]->get_current_bias() - mean_layer_gradients[i]; // since relu derivative is 1
        // bug: type mismatch here. get_current_bias returns a float while mean_layer_gradients is a tensor

        // For each node in the layer
        for (int j = 0; j < nodes_in_layer; j++) {
            // Get the node
            SharedCGNodePtr node = graph[layer_start + j];

            // Update the bias
            node->update_bias(new_bias);
        }
    }

    // Call node->update_bias

}

} // namespace computationgraph
