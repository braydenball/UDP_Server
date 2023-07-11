//Brayden Ball
//bb2498
/* 02/18/23 */
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fstream>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
	//declaring a file to write on
	fstream file;

	struct hostent *s;
	s = gethostbyname(argv[1]);
	
	struct sockaddr_in server;
	int mysocket = 0;
	socklen_t slen = sizeof(server);
	char payload[512] = "ABC";

	//prints the pay load.. abc
	cout << "Payload conains:  " << payload << endl;


	//if socket fails  to open, print this error
	if ((mysocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		cout << "ERROR in creating socket. \n";

	//setting destinations
	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(6363);
	bcopy((char *)s->h_addr, (char *)&server.sin_addr.s_addr, s->h_length);

	//obtained from client.cpp class file
	
	//prints out name, alias, and localhost ip addresses
	struct in_addr a;

	//prints the lines of code;
	file.open("upload.txt", ios::out | ios::trunc | ios::binary);
	if(file.is_open())
	{
		cout << "This is line one" << endl;
		file << "This is line one" << endl;

		cout << "This is line two" << endl;
		file << "This is line two" << endl;

		cout << "This is line three" << endl;
		file << "This is line three" << endl;

		cout << "This is line four" << endl;
		file << "This is line four" << endl;

		file.close();
	}
	else
	{
		cout << "File creation failed " << endl;
	}
	if (sendto(mysocket, payload, 8, 0, (struct sockaddr *) &server, slen) == -1)
		cout << "Error in sendto function. \n";


	char ack[512];

	recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen);
	cout << ack << endl;



	close(mysocket);
	return 0;
}
