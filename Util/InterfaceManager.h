#ifndef UTIL_INTERFACEMANAGER_H_
#define UTIL_INTERFACEMANAGER_H_

#include<string>

class InterfaceManager {
public:
	virtual ~InterfaceManager();
	virtual void broadcast(std::string, std::string);
	virtual void remove_client(std::string);
};

#endif
