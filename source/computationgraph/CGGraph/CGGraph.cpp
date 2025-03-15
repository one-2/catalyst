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
CGGraph::CGGraph() {
    graph_adj_list_(); // Calls default constructor for std::unordered_map<SharedCGNodePtr, std::vector<SharedCGNodePtr>>
    last_loss_ = nullptr;
}

void CGGraph::add_neural_layer(int width) {
    // Create an object to hold the new nodes in the layer
    std::vector<SharedCGNodePtr> new_layer = {};

    // Create width new nodes
    for (int i = 0; i < width; i++) {
        SharedCGNodePtr new_node = std::make_shared<CGNode>;        
        new_layer.push_back(new_node);
    };

    // Get the current state of the graph
    // Reverse topo sort the graph
    std::vector<SharedCGNodePtr> graph = reverse_topo_sort_();
    
    // Get the graph dimensions
    std::vector<int> dims = get_graph_dimensions();

    // If the graph is empty,
    if (dims.empty()) {
        // For each node in the new layer
        for (int i = 0; i < width; i++) {
            // Add the node to the adjacency list
            graph_adj_list_.insert({new_layer[i], std::vector<SharedCGNodePtr>()});
        }
        return;

    } else {
        // Otherwise, add the new layer to the CGGraph
        // First, point the final layer of the graph to the new nodes
        // Get the number of nodes in the last layer of the graph
        int j = dims.back();

        // For each of the nodes in the last layer of the graph,
        for (int i = 0; i < j; i++) {
            // For each node in the new layer
            for (int i = 0; i < width; i++) {
                // Add the node to the adjacency list
                graph_adj_list_.insert({new_layer[i], std::vector<SharedCGNodePtr>()});
            }
        }

        // For each node in the new layer
        for (int i : width) {
            // Add the node to the adjacency list
            graph_adj_list_.insert({new_layer[i], std::vector<SharedCGNodePtr>()})
        }
        return;
    }
}

void CGGraph::forward(Observation& observation) {
    // Retrieve the inputs
    torch::Tensor inputs = observation.inputs;

    // Create a tensor to store the layer activations
    torch::Tensor current_layer_activations = torch::empty({1, 1, 1});
    torch::Tensor all_layer_activations = torch::empty({1, 1, 1});

    // For each layer layer:
    std::vector<SharedCGNodePtr> topod_list = topo_sort_();
    for (std::vector<SharedCGNodePtr>& layer : topod_list) {
        // Activate each neuron
        for (SharedCGNodePtr& node : layer) {
            node->compute_activations(inputs);

            // Sum the neuron's activations with the current layer tally
            current_layer_activations = torch::sum({current_layer_activations, node->get_current_activations()}, 2);
        }

        // After a layer is complete,
        // Mean the activations
        torch::Tensor mean_activations = torch::mean(current_layer_activations, 2);
        
        // Save the meaned activations
        all_layer_activations = torch::cat({all_layer_activations, mean_activations}, 2);

        // Update the inputs for the next layer
        inputs = mean_activations;

    }

    // Retrieve the ouputs and predicted outputs
    torch::Tensor outputs = observation.outputs;
    torch::Tensor predicted_outputs = all_layer_activations.back();

    // Compute and save the loss
    torch::Tensor error = torch::sub(outputs, predicted_outputs);
    last_loss_ = torch::mean(torch::square(error));

}

void CGGraph::backward() {
    // Executes backpropagation
    // Retrieve the last loss
    torch::Tensor loss = last_loss_;

    // Retrieve the adjacency list and reverse topo sort it
    std::vector<SharedCGNodePtr> sorted_nodes = reverse_topo_sort_();

    // For each node in the sorted list
    for (SharedCGNodePtr& node : sorted_nodes) {
        // Compute the partial derivatives of the ReLU wrt the loss
        node->compute_gradients(loss);
    }

    // Optimise the weights and biases
    optimise_();

}

std::vector<int> CGGraph::get_graph_dimensions() { // TODO: add caching
    // TODO

}


// private
std::vector<SharedCGNodePtr> CGGraph::topo_sort_() { // TODO: add caching
    // TODO: implement a topo sort, baby
    return std::vector<SharedCGNodePtr>();
}



SharedCGNodePtr CGGraph::reverse_topo_sort_() { // TODO: add caching
    // Turn the adjacency list into an ordered vector of nodes, finish-to-start
    std::vector<SharedCGNodePtr> sorted = topo_sort_();
    std::reverse(sorted.begin(), sorted.end());
    return sorted;
}

void CGGraph::optimise_() {
    // Retrieve the adjacency list

    // For each node

        // Execute the gradient update rule using the last stored gradient
        // and a fixed learning rate

}

} // namespace computationgraph
