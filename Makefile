CXXFLAGS =	-O3 -g -Wall -fmessage-length=0 -std=c++11 -fopenmp

OBJS =		network_server.o Entities/Client.o Unity/Position.o Unity/Rotation.o Util/NetworkManager.o Util/InterfaceManager.o

LIBS =		-fopenmp -L/usr/lib -lmysqlcppconn -lboost_thread -lboost_system -lboost_chrono -pthread

TARGET =	network_server

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

	