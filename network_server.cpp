#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <string>
#include <memory>
#include <boost/asio.hpp>

#include "Entities/Client.h"
#include "Util/NetworkManager.h"

using boost::asio::ip::tcp;

void run_server(boost::asio::io_service&, tcp::endpoint&);

int main(int argc, char* argv[]) {
	try {
		boost::asio::io_service io_service;
		tcp::endpoint end_point(tcp::v6(), 9990);
		run_server(io_service, end_point);
		io_service.stop();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}

inline void run_server(boost::asio::io_service& io_service, tcp::endpoint& end_point) {
	std::shared_ptr<NetworkManager> manager(new NetworkManager(50));
	tcp::acceptor acceptor(io_service, end_point);
	for (;;) {
		std::cerr << "Waiting for new connection." << std::endl;
		acceptor.listen();
		SmartSocket sock(new tcp::socket(io_service));
		acceptor.accept(*sock);
		std::cerr << "New connection accepted." << std::endl;

		std::shared_ptr<Client> client(new Client(std::move(sock), manager));
		manager->add_client(client);
	}
	acceptor.close();
}
