#include <string.h>
#include <iostream>
#include <yaml-cpp/yaml.h>

// Inspired by
// https://stackoverflow.com/questions/41326112/how-to-merge-node-in-yaml-cpp
YAML::Node merge_nodes(YAML::Node a, YAML::Node b)
{
  // If b is not a map, merge result is b, unless b is null
  if (!b.IsMap()) {
    return b.IsNull() ? a : b;
  }

  // If a is not a map, merge result is b
  if (!a.IsMap()) {
    return b;
  }

  // Merge
  for (auto node : b) {
    auto key = node.first.as<std::string>();
    a[key] = merge_nodes(a[key], node.second);
  }

  return a;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    if (argc == 1) {
      std::cerr << "Missing filenames." << std::endl <<
        "Try '" << argv[0] << " --help' for more information." << std::endl;
    }

    return 1;
  }

  if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
    std::cout << "Usage: " << argv[0] << " [FILE]..." << std::endl <<
      "Merge each file (should be YAML) and print result to standard output." << std::endl;
    return 0;
  }

  if (argc == 2 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
    std::cout << "yaml-merge v0.0.1" << std::endl;
    return 0;
  }

  auto result = YAML::Node(YAML::NodeType::Map);
  for (int i = 1; i < argc; ++i) {
    result = merge_nodes(result, YAML::LoadFile(argv[i]));
  }

  YAML::Emitter out;
  out.SetStringFormat(YAML::DoubleQuoted);
  out << result;
  std::cout << out.c_str() << std::endl;

  return 0;
}
