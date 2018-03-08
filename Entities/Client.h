#ifndef ENTITIES_CLIENT_H_
#define ENTITIES_CLIENT_H_

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <string>
#include <memory>
#include <vector>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../Unity/Position.h"
#include "../Unity/Rotation.h"
#include "../Util/InterfaceManager.h"

using boost::asio::ip::tcp;

typedef boost::property_tree::ptree tree;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SmartSocket;
typedef std::shared_ptr<Position> SmartPosition;
typedef std::shared_ptr<Rotation> SmartRotation;

class Client {
private:
	SmartSocket sock;
	std::string id;
	std::shared_ptr<InterfaceManager> manager;
	std::shared_ptr<Position> position;
	std::shared_ptr<Rotation> rotation;

	void session();
	void update_transform(tree);
	tree get_ptree(std::string);
public:
	void send_to_client(std::string);

	// Constructor and deconstructor
	Client(SmartSocket, std::shared_ptr<InterfaceManager>);
	virtual ~Client();

	// Getters and Setters
	std::string get_id() const;
	std::shared_ptr<Position> get_position() const;
	std::shared_ptr<Rotation> get_rotation() const;
};

#endif
