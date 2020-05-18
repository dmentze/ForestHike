

#ifndef Bridge_H__
#define Bridge_H__

#include <string.h>

#include <iostream>
#include <vector>

#include "hiker.h"

namespace ForestHikeSim {

class Bridge {
 private:
  double mLength;  // units are feet
  double mMaxSpeed;
  double mTotalInverseSpeeds;  // sum of all speeds
  size_t mHikerCount;

 public:
  Bridge() : mLength(0), mMaxSpeed(0), mTotalInverseSpeeds(0), mHikerCount(0){};

  double getLength() const { return mLength; };
  void setLength(double length) { mLength = length; };

  // const Hiker& getHiker(size_t i) { return hikers[i]; };
  void addHiker(Hiker& hiker);

  size_t getHikerCount() const { return mHikerCount; };

  double getMaxSpeed() const { return mMaxSpeed; };

  double getTotalInverseSpeeds() const { return mTotalInverseSpeeds; };
};

}  // namespace ForestHikeSim

#endif
