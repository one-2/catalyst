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
    void forward(DataLoader& dataloader);
    void backward(DataLoader& dataloader);

    // Getters
    std::vector<int> get_graph_dimensions();
    
private:
    // Graph data
    std::vector<std::vector<SharedCGNodePtr>> graph_adj_list_;
    SharedTensorPtr last_loss_;

    // Graph execution
    SharedCGNodePtr topo_sort_();
    void optimise_();

};

} // namespace computationgraph

#endif // CGGRAPH_H