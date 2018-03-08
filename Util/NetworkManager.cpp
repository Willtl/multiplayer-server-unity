#include "NetworkManager.h"

NetworkManager::NetworkManager(int dist) {
	this->max_dist_update = dist;
}

// Virtual methods
void NetworkManager::broadcast(std::string id, std::string msg) {
	std::shared_ptr<Client> c1;
	for (auto client : clients)
		if (client->get_id() == id)
			c1 = client;
	for (auto client : clients) {
		if (c1 != client) {
			float dist = get_distance(c1, client);
			if (dist < max_dist_update)
				client->send_to_client(msg);
		}
	}
}

void NetworkManager::remove_client(std::string id) {
	for (unsigned int i = 0; i < clients.size(); i++) {
		if (clients[i]->get_id() == id) {
			clients.erase(clients.begin() + i);
			break;
		}
	}
}

// Custom methods
void NetworkManager::add_client(std::shared_ptr<Client> client) {
	clients.push_back(client);
	std::cout << "Client added to the list of clients" << std::endl;
	std::cerr << "Current number of the clients: " << clients.size() << std::endl;
	send_start(client);
	send_new_client_to_all(client);
	send_all_to_new_client(client);
}

void NetworkManager::send_start(std::shared_ptr<Client> client) {
	std::string json = get_transform_info(client, "start");
	client->send_to_client(json);
	std::cout << "Start sent." << std::endl;
	std::cout << json << std::endl;
}

void NetworkManager::send_new_client_to_all(std::shared_ptr<Client> client) {
	for (auto connected_client : clients) {
		if (connected_client != client) {
			std::string json = get_transform_info(client, "newPlayer");
			connected_client->send_to_client(json);
		}
	}
}

void NetworkManager::send_all_to_new_client(std::shared_ptr<Client> client) {
	for (auto connected_client : clients) {
		if (connected_client != client) {
			std::cout << connected_client->get_position()->x << std::endl;
			std::cout << connected_client->get_position()->y << std::endl;
			std::cout << connected_client->get_position()->z << std::endl;

			std::string json = get_transform_info(connected_client, "newPlayer");
			client->send_to_client(json);
		}
	}
}

float NetworkManager::get_distance(std::shared_ptr<Client> c1, std::shared_ptr<Client> c2) {
	float x = std::pow(c1->get_position()->x, 2) + std::pow(c2->get_position()->x, 2);
	float y = std::pow(c1->get_position()->y, 2) + std::pow(c2->get_position()->y, 2);
	float z = std::pow(c1->get_position()->z, 2) + std::pow(c2->get_position()->z, 2);
	return std::sqrt(x + y + z);
}

std::string NetworkManager::get_transform_info(std::shared_ptr<Client> client, std::string action) {
	tree pos;
	pos.put("X", client->get_position()->x);
	pos.put("Y", client->get_position()->y);
	pos.put("Z", client->get_position()->z);
	tree rot;
	rot.put("X", client->get_rotation()->x);
	rot.put("Y", client->get_rotation()->y);
	rot.put("Z", client->get_rotation()->z);
	rot.put("W", client->get_rotation()->w);

	tree json;
	json.put("action", action);
	json.put("id", client->get_id());
	json.add_child("position", pos);
	json.add_child("rotation", rot);

	std::stringstream ss;
	boost::property_tree::json_parser::write_json(ss, json);
	std::string json_str = ss.str();

	return json_str;
}

NetworkManager::~NetworkManager() {
}

