#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "ServerStateDisplay/ServerStateDisplay.h"
#include <thread>

enum KEYSTATE
{
	KEY_PUSH,
	KEY_RELEASE,
	KEY_ON,
	KEY_OFF
};

enum KEY_COMMAND
{
	KEY_LEFT,
	KEY_UP,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_MAX
};

struct PlayerData
{
	int32_t	Id;
	float	PosX, PosY;
	float	RectX, RectY;
};

struct SendData
{
	PlayerData playerData;
};

struct RecvData
{
	int32_t		  PlayerId;
	KEYSTATE KeyCommand[KEY_MAX];
};

int main()
{
	ServerStateDisplay* m_pServerStateDisplay;
	m_pServerStateDisplay = new ServerStateDisplay();

	SendData	 sendData;
	RecvData	 recvData;
	memset(&recvData, 0, sizeof(recvData));
	memset(&sendData, 0, sizeof(sendData));

	int sock;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(sockaddr_in);

	fd_set fds, readfds;
	FD_ZERO(&readfds);
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
		memcpy(&fds, &readfds, sizeof(fd_set));

		select(sock+1, &fds, NULL, NULL, &timeOut);
		m_pServerStateDisplay->SetPlayerState(1,1,1);

		if (FD_ISSET(sock,&fds))
		{
			recvfrom(sock, reinterpret_cast<char*>(&recvData), sizeof(RecvData), 0, (sockaddr*)&addr, &addr_len);
			if (recvData.KeyCommand[KEY_LEFT] == KEY_ON)
			{
				sendData.playerData.PosX -= 2.5f;
			}
			if (recvData.KeyCommand[KEY_RIGHT] == KEY_ON)
			{
				sendData.playerData.PosX += 2.5f;
			}
			if (recvData.KeyCommand[KEY_UP] == KEY_ON)
			{
				sendData.playerData.PosY -= 2.5f;
			}
			if (recvData.KeyCommand[KEY_DOWN] == KEY_ON)
			{
				sendData.playerData.PosY += 2.5f;
			}
			sendto(sock, reinterpret_cast<char*>(&sendData), sizeof(SendData), 0, (struct sockaddr *)&addr, sizeof(addr));
		}
	}

	delete m_pServerStateDisplay;
	close(sock);

	return 0;
}
