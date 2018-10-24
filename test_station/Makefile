# Makefile for the socket programming example
#

station_server_objects = ServerSocket.o Socket.o station_server_main.o


all : station_server

station_server: $(station_server_objects)
	g++ -o station_server $(station_server_objects) -lwiringPi

Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
station_server_main: station_server_main.cpp


clean:
	rm -f *.o station_server
