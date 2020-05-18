//#include "this/package/foo.h"

#include <iostream>

#include "foresthikeyaml.h"
#include "gtest/gtest.h"

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class ForestHikeYamlTest : public ::testing::Test {
 protected:
  ForestHikeYamlTest() {
    // set-up work for each test here.
  }

  ~ForestHikeYamlTest() override {
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
};

// Tests empty yaml file
TEST_F(ForestHikeYamlTest, YamlParseEmpty) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_empty.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with only bridge
TEST_F(ForestHikeYamlTest, YamlParseBridge) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_bridge.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with empty name
TEST_F(ForestHikeYamlTest, YamlParseEmptyName) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_empty_name.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with empty speed
TEST_F(ForestHikeYamlTest, YamlParseEmptySpeed) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_empty_speed.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with negative bridge length
TEST_F(ForestHikeYamlTest, YamlParseNegativeBridgeLength) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data =
      "../tests/data/yamlparse_negative_bridge_length.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml wtih negative speed
TEST_F(ForestHikeYamlTest, YamlParseNetativeSpeed) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_negative_speed.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with hiker with no name
TEST_F(ForestHikeYamlTest, YamlParseNoName) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_no_name.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with hiker with no speed
TEST_F(ForestHikeYamlTest, YamlParseNoSpeed) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_no_speed.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with zero bridge length
TEST_F(ForestHikeYamlTest, YamlParseZeroBridgeLength) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_zero_bridge_length.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

// Tests yaml with hiker with zero_speed
TEST_F(ForestHikeYamlTest, YamlParseZeroSpeed) {
  ForestHikeSim::ForestHikeYaml fhy;
  const std::string data = "../tests/data/yamlparse_zero_speed.yaml";
  EXPECT_EQ(fhy.read(data), false);
  EXPECT_EQ(fhy.getBridges().size(), 0);
}

}  // namespace
}  // namespace project
}  // namespace my
