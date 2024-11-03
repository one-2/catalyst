// run_tests.h
//
// Stephen Elliott, 2024-10-06
//
// This file...
//

#include <torch/torch.h>
#include <iostream>

#include "tests/run_tests.h"

using namespace std;

int main(int argc, char** argv)
{
  // GOOGLE_PROTOBUF_VERIFY_VERSION; //TODO Un-comment when pbuf installed
  
  cout << "Hello world." << endl;

  torch::Tensor tensor = torch::rand({2, 3});
  cout << tensor << endl;

  return 0;
}

