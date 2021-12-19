/*
* Loading and predicting from torch scripted model.
*/

#include <iostream>
#include <torch/script.h>
#include <torch/torch.h>
#include <vector>

int main(void) {

  // These form input to model.
  int x = 90;
  int y = 30;
  int n = 89;
  int a = 9;

  // Load Model
  torch::jit::script::Module net = torch::jit::load("../twinnet.pt");
  
  // Prepare Data
  std::vector<float> xp = {(float)x, (float)y, (float)n, (float)a};
  std::vector<torch::jit::IValue> input;
  
  // Input is single vector<torch::jit::IValue> type.
  input.emplace_back(torch::tensor(xp));
  input.emplace_back(torch::tensor(xp));

  // Predicted Output o1, o2 = model(xp, xp)
  auto output = net.forward(input);
  
  // Tuples Output (o1, o2)
  torch::Tensor t0 = output.toTuple()->elements()[0].toTensor();
  torch::Tensor t1 = output.toTuple()->elements()[1].toTensor();
  
  // Extract and print tuple output value.
  std::cout << t0[0].item<float>() << "\n";
  
  return 0;
}

/*
CMakeLists.txt (Add This)

set(CMAKE_PREFIX_PATH /home/clustfuzz/libtorch/)
find_package(Torch REQUIRED)
include_directories(include)

add_executable (code src/code.c)
set_property(TARGET code PROPERTY CXX_STANDARD 17)
*/
