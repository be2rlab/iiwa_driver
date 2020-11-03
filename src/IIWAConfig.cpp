#include "IIWAConfig.h"

IIWAConfig::IIWAConfig() {}
IIWAConfig::~IIWAConfig() {}

void IIWAConfig::set_hostname(const std::string& hostname) {
    hostname_ = hostname;
}

void IIWAConfig::set_port(const unsigned int& port) {
    port_ = port;
}

void IIWAConfig::set_joint_names(int n, const std::string& mask) {
    n_ = n;
    for (size_t i = 0; i < n_; ++i) {
    joint_names_.push_back(mask + std::to_string(i));
    }
}

void IIWAConfig::print() const {
    std::cout << "Joints number: " << n_ << "\n";

    std::cout << "Joit names:";
    for (size_t i = 0; i < n_; i++) {
        std::cout << "\t" << joint_names_[i] << "\n";
    }

    std::cout << "Host name (server): " << hostname_ << "\n";
    std::cout << "Port: " << port_ << "\n";
}