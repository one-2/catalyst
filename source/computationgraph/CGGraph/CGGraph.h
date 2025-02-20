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
#include "CGNode.h"

namespace computationgraph
{

class CGGraph {
public:
    // Constructors
    CGGraph();

    // Setters
    void set_loss(std::function<void()> loss);

    // Graph operations
    void add_layer(TensorOps operation, std::function<void()> activation); // TODO change operation to a callback
    void add_neural_layer(int depth, int width);                                       //      how to do autodiff on these?
                                                                           //      probs need to write the callbacks
                                                                           //      to some interface

    // Graph execution
    void forward(DataLoader& dataloader);
    void backward(DataLoader& dataloader);

    
private:
    // Graph data
    std::vector<std::vector<int>> graph_adj_list_;
    std::vector<float> last_loss_;

    // Graph operations
    void add_layer_(TensorOps operation, std::function<void()> activation); // TODO change operation to a callback
    int validate_layer_(); // Checks validity of a newly added layer

    // Graph execution
    std::vector<CGNode> topo_sort_();
    void optimise_();

};

} // namespace computationgraph

#endif // CGGRAPH_H