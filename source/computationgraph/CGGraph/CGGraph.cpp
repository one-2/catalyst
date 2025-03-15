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

using namespace datahandlers;

namespace computationgraph
{

// public
CGGraph::CGGraph() : last_loss_(nullptr) {}

void CGGraph::add_neural_layer(int width) {
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
            SharedCGNodePtr outer_node = reverse_topo[i];

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
        torch::Tensor current_layer_activation_tally = torch::empty({1, 1, 1});
        
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
    // Retrieve the adjacency list and reverse topo sort it
    std::vector<SharedCGNodePtr> sorted_nodes = reverse_topo_sort_();

    // For each node in the sorted list
    for (SharedCGNodePtr& node : sorted_nodes) {
        // Compute the partial derivatives of the ReLU wrt the loss
        node->compute_gradients(last_loss_);
    }

    // Optimise the weights and biases
    optimise_();

}

std::vector<int> CGGraph::get_graph_dimensions() {
    return dims_;
}

SharedTensorPtr get_last_loss() {
    return last_loss_;
}

// private
std::vector<SharedCGNodePtr> CGGraph::topo_sort_() { // TODO: add caching
    // TODO: implement a topo sort, baby
    return std::vector<SharedCGNodePtr>();
}

std::vector<SharedCGNodePtr> CGGraph::reverse_topo_sort_() { // TODO: add caching
    // Turn the adjacency list into an ordered vector of nodes, finish-to-start
    std::vector<SharedCGNodePtr> sorted = topo_sort_();
    std::reverse(sorted.begin(), sorted.end());
    return sorted;
}

void CGGraph::optimise_() {
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

}

} // namespace computationgraph
