

#include <iostream>

#include "foresthike.h"

using namespace std;

int main(int argc, char *argv[]) {
  std::vector<std::string> allArgs;

  for (int i = 0; i < argc; i++) {
    allArgs.push_back(argv[i]);
  }

  ForestHikeSim::ForestHike::RunSim(allArgs);
  return 0;
}
