

#ifndef Hiker_H__
#define Hiker_H__

#include <string.h>

namespace ForestHikeSim {

class Hiker {
 private:
  std::string mName;
  double mSpeed;

 public:
  Hiker() : mSpeed(0){};

  const std::string& getName() const { return mName; }
  void setName(std::string name) { mName = name; }

  double getSpeed() const { return mSpeed; }
  void setSpeed(double speed) { mSpeed = speed; }
};

}  // namespace ForestHikeSim

#endif
