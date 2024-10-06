#ifndef NeuralNetwork.h // prevent multiple linking/reference errors
#define NeuralNetwork.h

class NeuralNetwork
{
public:
    int NeuralNetwork();
    int add_layer(std::string activation,
                  std::string out_connection,
                  int width);
    int forward_pass();
    int backpropagate();
    std::ostream& operator<<;

private:
    std::vector<std::vector<auto>> layers;
}

#endif // NEURAL_NETWORK_H
