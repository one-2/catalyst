// source/computationgraph/CGGraph/CGGraph.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-11
//
// Description: 
//
// Usage: 
//


#ifndef CGGRAPH_H
#define CGGRAPH_H

#include <vector>
#include "../../tensorops/tensorops.h"
#include "CGNode.h"

using namespace tensorops;

namespace computationgraph
{

class CGGraph {
public:
    // Constructors
    CGGraph();

    // Graph operations
    void add_neural_layer(int width);

    // Graph execution
    void forward(Observation& observation);
    void backward();

    // Getters
    std::vector<int> get_graph_dimensions();
    
private:
    // Data
    std::unordered_map<SharedCGNodePtr, std::vector<SharedCGNodePtr>> graph_adj_list_; // TODO: requires custom hashing and equality comparator
    SharedTensorPtr last_loss_;
    std::vector<int> dims_;

    // State modifiers
    void add_node(int layer);

    // Graph execution
    std::vector<SharedCGNodePtr> topo_sort_();
    std::vector<SharedCGNodePtr> reverse_topo_sort_();
    void optimise_();

};

} // namespace computationgraph

#endif // CGGRAPH_H