#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>


class IIWAConfig {
public:
    IIWAConfig();

    ~IIWAConfig() {}

    void set_hostname(const std::string& hostname);

    void set_port(const unsigned int& port);

    void set_joint_names(int n, const std::string& mask);

    void print() const;

private:
    int n_;
    std::string hostname_;
    unsigned int port_;
    std::vector<std::string> joint_names_;
};


namespace YAML {
  template<>
  struct convert<IIWAConfig> {
    /**
     * @brief WARNING! Empty method.
     * 
     * @param config 
     * @return Node 
     */
    static Node encode(const IIWAConfig& config) {
      Node node;
      return node;
    }

    /**
     * @brief Decode `.yaml` config file to IIWAConfig instance.
     * 
     * @param node `YAML::Node` object.
     * @param config `IWAConfig` object.
     * 
     */
    static bool decode(const Node& node, IIWAConfig& config) {
      
      config.set_hostname(node["network"]["hostname"].as<std::string>());
      config.set_port(node["network"]["port"].as<int>());
      config.set_joint_names(node["joint"]["number"].as<int>(),
                            node["joint"]["mask"].as<std::string>());
      return true;
    }
  };
}
