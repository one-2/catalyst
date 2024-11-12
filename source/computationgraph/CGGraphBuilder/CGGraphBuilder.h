// source/computationgraph/CGGraphBuilder/CGGraphBuilder.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-12
//
// Description: Wraps a computation graph to tersely construct complicated components.
//              Keeps CGGraph minimal.
//
//              Tightly coupled to CGGraph interface.
//              => CGGraph should closed to change immediately.
//
// Usage: Model uses this to construct its computation graph.
//

#ifndef CGGRAPHBUILDER_H
#define CGGRAPHBUILDER_H


#include <string>
#include <list>

#include "computationgraph/CGGraph/CGGraph.h"


namespace computationgraph
{

class CGGraphBuilder
{
public:
    // Constructor
    CGGraphBuilder(CGGraph subject);

    // Standard components
    void add_graph_block(std::string type);
    void add_neural_network(int depth, std::list<int> width, std::string activation);
    // NOTE: Width both implicitly and explicitly specified to allow error handling
    //       for user misspecification.
    
    // Transformer components
    void create_decoder();
    void create_positional_encoder();
    void create_embedder();
    void create_masker();
    void create_transformer();

}

} // namespace computationgraph

#endif // CGGRAPHBUILDER_H