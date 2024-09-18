#include "../includes/ServiceObject.hpp"

ServiceObject::ServiceObject(const std::string& name) {
    serviceName = name;
}

std::string ServiceObject::getName() const {
    return serviceName;
}