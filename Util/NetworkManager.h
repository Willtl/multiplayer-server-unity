#ifndef UTIL_NETWORKMANAGER_H_
#define UTIL_NETWORKMANAGER_H_

#include <vector>

#include "../Entities/Client.h"
#include "InterfaceManager.h"

typedef boost::property_tree::ptree tree;

class NetworkManager: public virtual InterfaceManager {
private:
	int max_dist_update;
	std::vector<std::shared_ptr<Client>> clients;
public:
	virtual void broadcast(std::string, std::string);
	virtual void remove_client(std::string);

	void add_client(std::shared_ptr<Client>);
	void send_start(std::shared_ptr<Client>);
	void send_new_client_to_all(std::shared_ptr<Client>);
	void send_all_to_new_client(std::shared_ptr<Client>);
	float get_distance(std::shared_ptr<Client>, std::shared_ptr<Client>);
	std::string get_transform_info(std::shared_ptr<Client>, std::string);
	NetworkManager(int);
	virtual ~NetworkManager();
};

#endif
