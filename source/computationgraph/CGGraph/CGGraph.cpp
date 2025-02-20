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

    // Get final layer reference
    std::vector<SharedCGNodePtr>& final_layer = graph_adj_list_.back();

    // Add nodes to final layer
    for (int i : width) {
        // Make a new node
        SharedCGNodePtr new_node = std::make_shared<CGNode>;

        // Push it to the final graph layer
        final_layer.push_back(new_node);
    };
}

void CGGraph::forward(DataLoader& dataloader) {
    // TODO

}

void CGGraph::backward(DataLoader& dataloader) {
    // TODO

}

std::vector<int> CGGraph::get_graph_dimensions() {
    // TODO

}

// private
SharedCGNodePtr CGGraph::topo_sort_() {
    // TODO

}

void CGGraph::optimise_() {
    // TODO

}

} // namespace computationgraph
