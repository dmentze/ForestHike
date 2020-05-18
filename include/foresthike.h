

#ifndef ForestHike_H__
#define ForestHike_H__

#include <string.h>

#include <map>
#include <vector>

#include "bridge.h"

namespace ForestHikeSim {

class ForestHike {
 private:
  std::vector<Bridge> mBridges;
  std::vector<double> mCrossTimes;

  double mTotalTime;           // minutes
  double mTotalInverseSpeeds;  // feet per minute
  size_t mTotalHikerCount;
  double mMaxHikerSpeed;  // feet per minute

  double calcCrossTime(Bridge& bridge);

  static bool sDebug;

 public:
  static void RunSim(std::vector<std::string>& allArgs);

  ForestHike()
      : mTotalTime(0),
        mTotalInverseSpeeds(0),
        mTotalHikerCount(0),
        mMaxHikerSpeed(0){};

  void hike(std::vector<Bridge>& aBridges);

  size_t getTotalHikerCount() { return mTotalHikerCount; }
  double getTotalTime() { return mTotalTime; }
  const std::vector<double>& getCrossTimes() const { return mCrossTimes; }

  void dump();
  void printSummary();

  static bool Debug() { return sDebug; }
  static bool FindAndRemove(std::vector<std::string>& args, std::string s);
};

}  // namespace ForestHikeSim

#endif
