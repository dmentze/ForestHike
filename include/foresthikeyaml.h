

#ifndef ForestHikeYaml_H__
#define ForestHikeYaml_H__

#include <string.h>

#include <vector>

#include "bridge.h"

namespace ForestHikeSim {

class ForestHikeYaml {
 private:
  std::vector<Bridge> mBridges;

 public:
  bool read(std::string file);
  std::vector<Bridge>& getBridges() { return mBridges; }
};

}  // namespace ForestHikeSim

#endif
