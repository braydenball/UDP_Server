//Brayden Ball
//bb2498
/* 02/18/23 */
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	struct sockaddr_in client;
	int mysocket = 0;
	int i  = 0;
	socklen_t clen = sizeof(client);
	char payload[512];

	//the random port chosen
	int rand_port = rand() % 1024 + 64511;

	if ((mysocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		cout << "ERROR in socket creation \n";

	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(6363);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(mysocket, (struct sockaddr *)&server, sizeof(server)) == -1)
		cout << "ERROR in binding. \n";

	cout << "Random port: " << rand_port << "\n";
	
	if (recvfrom(mysocket, payload, 512, 0, (struct sockaddr *)&client, &clen) == -1)
			cout << "Failed to receive. \n";

	cout << "Client received data: " << payload << endl;
	
	char ack[] = "Sent from server ";


	if (sendto(mysocket, ack, 64, 0, (struct sockaddr *) &client, clen) == -1)
		cout << "Error in sendto function. \n";

	close(mysocket);
	return 0;

}
