
#include "foresthikeyaml.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "bridge.h"
#include "foresthike.h"
#include "hiker.h"
#include "yaml-cpp/yaml.h"

#define FOREST_YAML_DEBUG 0

using namespace std;

namespace ForestHikeSim {
void dbgNode(YAML::Node n, std::string d);
}

namespace YAML {
template <>
struct convert<vector<ForestHikeSim::Bridge>> {
  static Node encode(const vector<ForestHikeSim::Bridge>& rhs) {
    Node node;
    // TBD
    return node;
  }

  static bool decode(const Node& node, vector<ForestHikeSim::Bridge>& rhs) {
    if (!node.IsSequence()) {
      return false;
    }

    ForestHikeSim::dbgNode(node, "v<B>");

    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
      const YAML::Node& key = *it;
      // const YAML::Node& value = it->second;

      ForestHikeSim::Bridge b = key.as<ForestHikeSim::Bridge>();
      rhs.push_back(std::move(b));
    }

    return true;
  }
};
}  // namespace YAML

namespace YAML {
template <>
struct convert<ForestHikeSim::Bridge> {
  static Node encode(const ForestHikeSim::Bridge& rhs) {
    Node node;
    // TBD
    return node;
  }

  static bool decode(const Node& node, ForestHikeSim::Bridge& rhs) {
    if (!node.IsMap()) {
      return false;
    }

    ForestHikeSim::dbgNode(node, "<B>");

    rhs.setLength(node["length"].as<double>());
    const YAML::Node& hikersNode = node["hikers"];

    if (rhs.getLength() <= 0) {
      return false;
    }

    for (YAML::const_iterator it = hikersNode.begin(); it != hikersNode.end();
         ++it) {
      const YAML::Node& key = *it;

      ForestHikeSim::dbgNode(key, "<B>[]");

      ForestHikeSim::Hiker p = key.as<ForestHikeSim::Hiker>();
      rhs.addHiker(p);
    }

    return true;
  }
};
}  // namespace YAML

namespace YAML {
template <>
struct convert<ForestHikeSim::Hiker> {
  static Node encode(const ForestHikeSim::Hiker& rhs) {
    Node node;
    // TBD
    return node;
  }

  static bool decode(const Node& node, ForestHikeSim::Hiker& rhs) {
    if (!node.IsMap()) {
      return false;
    }

    ForestHikeSim::dbgNode(node, "<P>");

    rhs.setName(node["name"].as<std::string>());
    rhs.setSpeed(node["speed"].as<double>());

    if ((rhs.getSpeed() <= 0) || (rhs.getName().length() < 1)) {
      return false;
    }

    return true;
  }
};
}  // namespace YAML

void ForestHikeSim::dbgNode(YAML::Node n, std::string d) {
  if (ForestHike::Debug()) {
    cout << d << ": ";
    switch (n.Type()) {
      case YAML::NodeType::Null:
        cout << "Null" << endl;
        break;
      case YAML::NodeType::Scalar:
        cout << "Scalar" << endl;
        break;
      case YAML::NodeType::Sequence:
        cout << "Sequence" << endl;
        break;
      case YAML::NodeType::Map:
        cout << "Map" << endl;
        break;
      case YAML::NodeType::Undefined:
        cout << "Undefined" << endl;
        break;
      default:
        cout << "default" << endl;
        break;
    }
  }
}

bool ForestHikeSim::ForestHikeYaml::read(std::string file) {
  try {
    if (ForestHike::Debug()) {
      cout << "Input File: " << file << endl;
    }

    YAML::Node node = YAML::LoadFile(file);

    const YAML::Node& bs = node["bridges"];
    dbgNode(bs, "n[bridges]");

    mBridges = bs.as<vector<Bridge>>();

  } catch (const std::exception& exc) {
    if (ForestHike::Debug()) {
      cout << "Yaml File: " << file << " error: " << exc.what() << endl;
    }
    mBridges.clear();
    return false;
  }
  return true;
}
