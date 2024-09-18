#ifndef SERVICE_OBJ_HPP
#define SERVICE_OBJ_HPP

#include <string>

class ServiceObject {
    std::string serviceName;

    public:
    ServiceObject(const std::string& name);

    std::string getName() const;
};

#endif