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
    graph_adj_list_ = std::vector<std::vector<SharedCGNodePtr>>();
    last_loss_ = nullptr;

}

void CGGraph::add_neural_layer(int width) {
    // Create new layer
    graph_adj_list_.push_back( {} ); // push an empty vector

    // Get a reference to the final layer we just added
    std::vector<SharedCGNodePtr>& final_layer = graph_adj_list_.back();

    // Add width number of nodes to the final layer
    for (int i : width) {
        SharedCGNodePtr new_node = std::make_shared<CGNode>;
        final_layer.push_back(new_node);
    };
}

void CGGraph::forward(Observation& observation) {
    // Retrieve the inputs
    torch::Tensor inputs = observation.inputs;

    // Create a tensor to store the layer activations
    torch::Tensor current_layer_activations = torch::empty({1, 1, 1});
    torch::Tensor all_layer_activations = torch::empty({1, 1, 1});

    // For each layer layer:
    for (std::vector<SharedCGNodePtr>& layer : graph_adj_list_) {
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
    // Retrieve the last loss
    torch::Tensor loss = last_loss_;

    // Retrieve the adjacency list and reverse topo sort it
    std::vector<SharedCGNodePtr> sorted_nodes = reverse_topo_sort_();

    // For each node in the sorted list
    for (SharedCGNodePtr& node : sorted_nodes) {
        // Compute the partial derivatives of the ReLU wrt the loss
        // Or backpropagate the loss with the chain rule
        node->compute_gradients(loss);

        // Save the gradients on the node
        node->store_gradients();
    }

    // Optimise the weights and biases
    optimise_();

}

std::vector<int> CGGraph::get_graph_dimensions() {
    std::vector<int> dims;
    
    // If the adjacency list is empty, return an empty vector
    if (graph_adj_list_.empty()) {
        return dims;
    }

    // Start from the first node in the adjacency list
    auto it = graph_adj_list_.begin();
    SharedCGNodePtr node = it->first;

    // Traverse along the feedforward chain
    while (graph_adj_list_.count(node)) {
        const std::vector<SharedCGNodePtr>& next_layer = graph_adj_list_[node];
        dims.push_back(next_layer.size()); // Save the width of the current layer

        // Move to the first node in the next layer
        if (!next_layer.empty()) {
            node = next_layer[0]; // Pick the first child as the next node
        } else {
            break; // Stop at an endpoint
        }
    }

    return dims;
}


// private
std::vector<SharedCGNodePtr> CGGraph::topo_sort_() { // TODO: add cache so this only has to be done once
    // TODO: implement a topo sort, baby
    return std::vector<SharedCGNodePtr>();
}



SharedCGNodePtr CGGraph::reverse_topo_sort_() {
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
