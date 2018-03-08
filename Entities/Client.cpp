#include "Client.h"

Client::Client(SmartSocket socket, std::shared_ptr<InterfaceManager> i_manager) {
	sock = socket;
	// For broadcast
	this->manager = i_manager;

	// Create UUID
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	id = to_string(uuid);
	std::cout << "Client " << id << " connected." << std::endl;

	// Define position and rotation
	this->position = SmartPosition(new Position(0, 0, 0));
	this->rotation = SmartRotation(new Rotation(0, 1, 0, 0));

	// Start client thread
	std::thread(&Client::session, this).detach();
}

void Client::send_to_client(std::string json_str) {
	try {
		// Add json length at the start of the message
		/*unsigned int json_length = json_str.size();
		 //std::vector<unsigned char> length = int_to_bytes(json_length);
		 unsigned char bytes[4];

		 bytes[0] = json_length & 0xFF;
		 bytes[1] = (json_length >> 8) & 0xFF;
		 bytes[2] = (json_length >> 16) & 0xFF;
		 bytes[3] = (json_length >> 24) & 0xFF;

		 char* length = reinterpret_cast<char*>(bytes);
		 char* json = const_cast<char*>(json_str.c_str());
		 std::string total(std::string(length) + json);*/

		const char* data = json_str.c_str();
		size_t data_length = std::strlen(data);
		boost::asio::write(*sock, boost::asio::buffer(data, data_length));
	} catch (std::exception& e) {
		std::cerr << "Exception in send_to_client(): " << e.what() << "\n";
	}
}

// Session thread
void Client::session() {
	try {
		for (;;) {
			char data[1024];
			boost::system::error_code error;
			size_t size = sock->read_some(boost::asio::buffer(data), error);

			if (error == boost::asio::error::eof) {
				puts("Connection closed cleanly by peer");
				break;
			} else if (error) {
				puts("Some other error");
				throw boost::system::system_error(error);
			}

			std::string json(data, size);
			std::cout << json << std::endl;

			tree ptree = get_ptree(json);
			update_transform(ptree);
			manager->broadcast(id, json);
		}
	} catch (std::exception& e) {
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
	std::cout << "Client " << id << " closed its connection." << std::endl;
	sock->close();
	manager->remove_client(id);
}

void Client::update_transform(tree ptree) {
	std::string action = ptree.get_child("action").get_value<std::string>();
	if (action != "logout" && action != "animation") {
		position->x = std::stof(ptree.get_child("position").get_child("X").get_value<std::string>());
		position->y = std::stof(ptree.get_child("position").get_child("Y").get_value<std::string>());
		position->z = std::stof(ptree.get_child("position").get_child("Z").get_value<std::string>());

		rotation->x = std::stof(ptree.get_child("rotation").get_child("X").get_value<std::string>());
		rotation->y = std::stof(ptree.get_child("rotation").get_child("Y").get_value<std::string>());
		rotation->z = std::stof(ptree.get_child("rotation").get_child("Z").get_value<std::string>());
		rotation->w = std::stof(ptree.get_child("rotation").get_child("W").get_value<std::string>());
	}
}

tree Client::get_ptree(std::string json) {
	std::stringstream ss;
	ss << json;

	boost::property_tree::ptree ptree;
	boost::property_tree::read_json(ss, ptree);
	return ptree;
}

Client::~Client() {
}

std::string Client::get_id() const {
	return id;
}

std::shared_ptr<Position> Client::get_position() const {
	return position;
}

std::shared_ptr<Rotation> Client::get_rotation() const {
	return rotation;
}
