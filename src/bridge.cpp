

#include "bridge.h"

#include <algorithm>

void ForestHikeSim::Bridge::addHiker(Hiker& hiker) {
  // hikers.push_back(hiker);
  mHikerCount++;
  assert(mHikerCount);  // check for rollover
  double speed = hiker.getSpeed();
  mMaxSpeed = std::max(mMaxSpeed, speed);
  mTotalInverseSpeeds += 1 / speed;
}
