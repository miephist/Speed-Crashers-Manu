#include "Client.h"
#include "Server.h"
#include "enums.h" 

int main(void)
{
	std::string str;
	bool isServer;

	Client *client = new Client();
	Server *server = new Server();

	printf("(C) or (S)erver?\n");
    std::cin >> str;

	if ((str[0]=='c')||(str[0]=='C')){
		isServer = false;
		client->Init();

	}else{

		isServer = true;
		server->Init();

	}

	if(!isServer) {
		client->setIP();
	}

    while (1){
		if(isServer){
			server->Update();
		}else{
			client->Update();
		}
	}


	if(isServer){
		delete server;
	}else{
		delete client;
	}


	return 0;
}
