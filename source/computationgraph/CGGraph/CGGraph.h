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
#include <list>
#include <functional>
#include "TensorOps.h"

namespace computationgraph
{

class CGGraph {
public:
    // Constructors
    CGGraph();

    // Setters
    void set_optimiser(std::function<void()> optimiser);
    void set_loss(std::function<void()> loss);

    // Graph operations
    void add_layer(TensorOps operation, std::function<void()> activation); // TODO change operation to a callback
    void add_edge(int from, int to);                                       //      how to do autodiff on these?
                                                                           //      probs need to write the callbacks
                                                                           //      to some interface
    std::vector<int> topo_sort();
    void compile();
    static CGGraph merge(const std::list<CGGraph>& graphs);

private:
    std::vector<std::vector<int>> graph_adj_list;
    std::function<void()> optimiser_;
    int validate_layer();
};

} // namespace computationgraph

#endif // CGGRAPH_H