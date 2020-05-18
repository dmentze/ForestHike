//#include "this/package/foo.h"

#include <iostream>

#include "foresthike.h"
#include "foresthikeyaml.h"
#include "gtest/gtest.h"

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class ForestHikeTest : public ::testing::Test {
 protected:
  ForestHikeTest() {
    // set-up work for each test here.
  }

  ~ForestHikeTest() override {
    // clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.

  // load the data file
  void testHike(const std::string data, size_t numBridges, size_t totalHikers,
                const double bridgeTimes[]) {
    const double precision = 0.001;

    ForestHikeSim::ForestHikeYaml fhy;
    EXPECT_EQ(fhy.read(data), true);
    EXPECT_EQ(fhy.getBridges().size(), numBridges);

    // apply the data file to a foresthike
    ForestHikeSim::ForestHike fh;
    fh.hike(fhy.getBridges());

    // check individual bridge cross times
    double totalTimes = 0;
    for (int i = 0; i < numBridges; i++) {
      EXPECT_NEAR(fh.getCrossTimes()[i], bridgeTimes[i], precision);
      totalTimes += bridgeTimes[i];
    }

    // check total results results
    EXPECT_NEAR(fh.getTotalTime(), totalTimes, 0.001);
    EXPECT_EQ(fh.getTotalHikerCount(), totalHikers);
  }
};

// Tests that the ForesHike::getTotalHikeCount() starts at 0
TEST_F(ForestHikeTest, TotalHikeCountInit) {
  ForestHikeSim::ForestHike fh;
  EXPECT_EQ(fh.getTotalHikerCount(), 0);
}

TEST_F(ForestHikeTest, TotalTimeInit) {
  ForestHikeSim::ForestHike fh;
  EXPECT_EQ(fh.getTotalTime(), 0);
}

// Tests yaml with bridge 1 with fastest hiker
TEST_F(ForestHikeTest, CalcBridge1Fastest) {
  // load the data file
  const std::string data = "../tests/data/calc_bridge1_fastest.yaml";
  const size_t numBridges = 3;
  const size_t totalHikers = 6;
  const double bridgeTimes[] = {50, 244.9353, 421.9845};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with bridge 2 with fastest hiker
TEST_F(ForestHikeTest, CalcBridge2Fastest) {
  // load the data file
  const std::string data = "../tests/data/calc_bridge2_fastest.yaml";
  const size_t numBridges = 3;
  const size_t totalHikers = 5;
  const double bridgeTimes[] = {50, 158.7705, 322.7691};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with last bridge 3 with fastest hiker
TEST_F(ForestHikeTest, CalcBridge3Fastest) {
  // load the data file
  const std::string data = "../tests/data/calc_bridge3_fastest.yaml";
  const size_t numBridges = 3;
  const size_t totalHikers = 5;
  const double bridgeTimes[] = {20, 184.0186, 394.1537};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with 1 hiker
TEST_F(ForestHikeTest, Calc1Hiker) {
  // load the data file
  const std::string data = "../tests/data/calc_hiker1.yaml";
  const size_t numBridges = 1;
  const size_t totalHikers = 1;
  const double bridgeTimes[] = {50};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with 2 hikers
TEST_F(ForestHikeTest, Calc2Hiker) {
  // load the data file
  const std::string data = "../tests/data/calc_hiker2.yaml";
  const size_t numBridges = 1;
  const size_t totalHikers = 2;
  const double bridgeTimes[] = {95.2381};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with 3 hikers
TEST_F(ForestHikeTest, Calc3Hiker) {
  // load the data file
  const std::string data = "../tests/data/calc_hiker3.yaml";
  const size_t numBridges = 1;
  const size_t totalHikers = 3;
  const double bridgeTimes[] = {234.9277};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with 4 hikers
TEST_F(ForestHikeTest, Calc4Hiker) {
  // load the data file
  const std::string data = "../tests/data/calc_hiker4.yaml";
  const size_t numBridges = 1;
  const size_t totalHikers = 4;
  const double bridgeTimes[] = {2463.8018};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with bridge with no additional hikers
TEST_F(ForestHikeTest, CalcBridgeNoAdditionalHikers) {
  // load the data file
  const std::string data = "../tests/data/calc_nohikers.yaml";
  const size_t numBridges = 4;
  const size_t totalHikers = 2;
  const double bridgeTimes[] = {0, 20, 40, 4};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with larger random case
TEST_F(ForestHikeTest, CalcBridgeRegression) {
  // load the data file
  const std::string data = "../tests/data/calc_regression.yaml";
  const size_t numBridges = 4;
  const size_t totalHikers = 7;
  const double bridgeTimes[] = {20, 542.8510, 271.6833, 524.3578};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

// Tests yaml with example file
TEST_F(ForestHikeTest, CalcExample) {
  // load the data file
  const std::string data = "../tests/data/hike.yaml";
  const size_t numBridges = 3;
  const size_t totalHikers = 7;
  const double bridgeTimes[] = {19, 150, 109};

  testHike(data, numBridges, totalHikers, bridgeTimes);
}

}  // namespace
}  // namespace project
}  // namespace my
