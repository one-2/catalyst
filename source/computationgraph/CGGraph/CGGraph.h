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
#include "../CGNode/CGNode.h"
#include "../../datahandlers/DataLoader/DataLoader.h"

using namespace tensorops;
using namespace datahandlers;

namespace computationgraph
{
typedef std::shared_ptr<CGNode> SharedCGNodePtr;

class CGGraph {
public:
    // Constructors
    CGGraph();

    // Graph operations
    void add_neural_layer(int width);

    // Graph execution
    void forward(DataLoader::Observation& observation);
    void backward();

    // Getters
    std::vector<int> get_graph_dimensions();
    SharedTensorPtr get_last_loss();
    
    std::vector<SharedCGNodePtr> topo_sort_();
    std::vector<SharedCGNodePtr> reverse_topo_sort_();

private:
    // Data
    std::unordered_map<SharedCGNodePtr, std::vector<SharedCGNodePtr>> graph_adj_list_;
    // TODO: requires custom hashing and equality comparator
    // note: using an adj list because the graph is sparse (|E| << |V|^2) and directed. p549 of CLRS.
    SharedTensorPtr last_loss_;
    std::vector<int> dims_;

    // Cache data
    bool is_topo_cache_valid_;
    std::vector<SharedCGNodePtr> topo_forward_ordering_cache_;

    // State modifiers
    void add_node(int layer);

    // Graph execution
    void optimise_();

};

} // namespace computationgraph

#endif // CGGRAPH_H