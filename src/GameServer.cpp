//============================================================================
// Name        : GameServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


int main()
{
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(sockaddr_in);
	char buf[2048];

	fd_set fds, readfds;
	FD_ZERO(&readfds);
	int selectResult;
	timeval timeOut;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (sockaddr *)&addr, sizeof(addr));
	FD_SET(sock, &readfds);

	timeOut.tv_sec = 2;
	timeOut.tv_usec = 0;


	while (1)
	{
		sleep(1);
		memcpy(&fds, &readfds, sizeof(fd_set));
		int len = (int)sizeof(sockaddr_in);

		selectResult = select(sock+1, &fds, NULL, NULL, &timeOut);

		if (FD_ISSET(sock,&fds))
		{
			memset(buf, 0, sizeof(buf));
			recvfrom(sock, buf, 6, 0, (sockaddr*)&addr, &addr_len);
			printf("%s\n", buf);
			sendto(sock, "hello", 6, 0, (struct sockaddr *)&addr, sizeof(addr));
		}

	}


	close(sock);

	return 0;
}
