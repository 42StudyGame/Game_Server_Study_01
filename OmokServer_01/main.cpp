#include <iostream>
#include <thread>

#include "Server.h"

int main()
{
	Server server;
	server.Init();

	std::thread runThread([&]() { 		
		server.Run(); }
	);


	
	std::cout << "press any key to exit...";
	getchar();

	server.Stop();
	runThread.join();

	return 0;
}