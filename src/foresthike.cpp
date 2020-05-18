
#include "foresthike.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "bridge.h"
#include "foresthikeyaml.h"
#include "hiker.h"

using namespace std;
using namespace ForestHikeSim;

bool ForestHikeSim::ForestHike::sDebug = false;

bool ForestHikeSim::ForestHike::FindAndRemove(std::vector<std::string>& args,
                                              std::string s) {
  std::vector<std::string>::iterator it;
  it = std::find(args.begin(), args.end(), s);
  if (it != args.end()) {
    args.erase(it);
    return true;
  }
  return false;
}

void ForestHikeSim::ForestHike::RunSim(std::vector<std::string>& allArgs) {
  std::string file;

  // handle help flag
  if (ForestHike::FindAndRemove(allArgs, "--help") ||
      ForestHike::FindAndRemove(allArgs, "-h")) {
    cout << "OVERVIEW:  A tool to simulate a forest hike at night." << endl
         << endl;
    cout << "USAGE: foresthiker --help" << endl;
    cout << "       foresthiker [<file>] [--debug]" << endl << endl;
    cout << "If no arguments are specified then a default simulation input "
            "file is used."
         << endl
         << endl;
    return;
  }

  // set debug flag if needed
  if (ForestHike::FindAndRemove(allArgs, "--debug") ||
      ForestHike::FindAndRemove(allArgs, "-d")) {
    sDebug = true;
  }

  // set input file
  if (allArgs.size() <= 1) {
    file = "../tests/data/hike.yaml";
  } else {
    file = allArgs[1];
  }

  ForestHikeYaml forestHikeYaml;
  bool loadYaml = forestHikeYaml.read(file);

  if (!loadYaml) {
    cout << "Load YAML failed." << endl;
  }
  ForestHike forestHike;
  forestHike.hike(forestHikeYaml.getBridges());

  forestHike.printSummary();
  if (Debug()) {
    forestHike.dump();
  }
}

double ForestHikeSim::ForestHike::calcCrossTime(Bridge& bridge) {
  double returnTrips = 0;
  double inverseSpeeds = mTotalInverseSpeeds;  // handles the case of 1 hiker

  if (mTotalHikerCount > 2) {
    returnTrips = mTotalHikerCount - 2;
    inverseSpeeds = mTotalInverseSpeeds + (returnTrips - 1) / (mMaxHikerSpeed);
  } else if (mTotalHikerCount == 2) {
    inverseSpeeds = mTotalInverseSpeeds - (1 / (mMaxHikerSpeed));
  }

  return bridge.getLength() * inverseSpeeds;
}

void ForestHikeSim::ForestHike::hike(std::vector<Bridge>& aBridges) {
  mBridges = std::move(aBridges);

  for (int i = 0; i < mBridges.size(); i++) {
    Bridge& bridge = mBridges[i];
    double bridgeMax = bridge.getMaxSpeed();
    mMaxHikerSpeed = std::max(mMaxHikerSpeed, bridgeMax);
    mTotalInverseSpeeds += bridge.getTotalInverseSpeeds();
    mTotalHikerCount += bridge.getHikerCount();

    double crossTime = calcCrossTime(bridge);
    mCrossTimes.push_back(crossTime);
    mTotalTime += crossTime;
  }
}

void ForestHikeSim::ForestHike::dump() {
  if (mTotalHikerCount > 0) {
    cout << "total cross time: " << mTotalTime << endl;
    cout << "total hikers:  " << mTotalHikerCount << endl;
    cout << "max hiker speed: " << mMaxHikerSpeed << endl;
    cout << "total inverse speeds: " << mTotalInverseSpeeds << endl;
  }
  for (int i = 0; i < mBridges.size(); i++) {
    cout << "bridge: " << i << endl;
    cout << "  length: " << mBridges[i].getLength() << endl;
    cout << "  max speed: " << mBridges[i].getMaxSpeed() << endl;
    cout << "  total inverse speeds: " << mBridges[i].getTotalInverseSpeeds()
         << endl;
    cout << "  hiker count: " << mBridges[i].getHikerCount() << endl;
    if (i < this->mCrossTimes.size()) {
      cout << "  cross time: " << mCrossTimes[i] << endl;
    }
  }
}

void ForestHikeSim::ForestHike::printSummary() {
  cout << "total cross time: " << mTotalTime << endl;
  for (int i = 0; i < mBridges.size(); i++) {
    if (i < mCrossTimes.size()) {
      cout << "  bridge " << i << " cross time: " << mCrossTimes[i] << endl;
    }
  }
}
