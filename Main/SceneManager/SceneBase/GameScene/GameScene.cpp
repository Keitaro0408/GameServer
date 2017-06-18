/*
 * GameScene.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "GameScene.h"
#include "../../GameDataManager/GameDataManager.h"
#include "ServerStateDisplay/ServerStateDisplay.h"


GameScene::GameScene() :
SceneBase(SceneBase::SCENE_GAME),
m_IsThreadEnd(false)
{
	m_pServerStateDisplay = new ServerStateDisplay();
	int playerNum = GameDataManager::GetInstance()->GetPlayerNum();
	m_pPlayerData = new PlayerData[playerNum];
	for(int i = 0;i < playerNum;i++)
	{
		m_pPlayerData[i].Id = 0;
		m_pPlayerData[i].PosX = 0;
		m_pPlayerData[i].PosY = 0;
		m_pPlayerData[i].RectX = 0;
		m_pPlayerData[i].RectY = 0;
	}
	m_pServerStateDisplay->SetPlayerData(m_pPlayerData);
	m_pUdpThread = new std::thread(&GameScene::ConnectLoop,this);
}

GameScene::~GameScene()
{
	m_IsThreadEnd = true;
	m_pUdpThread->join();
	delete m_pUdpThread;
	m_pUdpThread = nullptr;

	delete[] m_pPlayerData;

	delete m_pServerStateDisplay;
	m_pServerStateDisplay = nullptr;

}

SceneBase::SceneID GameScene::Update()
{
	return m_SceneID;
}

void GameScene::ConnectLoop()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(50000);
	addr.sin_addr.s_addr = INADDR_ANY;
	fd_set  			fds, readFds;
	timeval 			timeOut;

	FD_ZERO(&readFds);
	bind(sock, (sockaddr *)&addr, sizeof(addr));
	FD_SET(sock, &readFds);

	timeOut.tv_sec = 2;
	timeOut.tv_usec = 0;

	int playerNum = GameDataManager::GetInstance()->GetPlayerNum();

	while(!m_IsThreadEnd)
	{
		memcpy(&fds, &readFds, sizeof(fd_set));

		select(sock+1, &fds, NULL, NULL, &timeOut);
		socklen_t addr_len = sizeof(sockaddr_in);

		if (FD_ISSET(sock,&fds))
		{
			recvfrom(sock, reinterpret_cast<char*>(&m_RecvData), sizeof(RecvData), 0, (sockaddr*)&addr, &addr_len);
			if(m_RecvData.PlayerId <= playerNum)
			{
				m_pPlayerData[m_RecvData.PlayerId-1].Id = m_RecvData.PlayerId;
				if (m_RecvData.KeyCommand[KEY_LEFT] == KEY_ON)
				{
					m_pPlayerData[m_RecvData.PlayerId-1].PosX -= 2.5f;
				}
				if (m_RecvData.KeyCommand[KEY_RIGHT] == KEY_ON)
				{
					m_pPlayerData[m_RecvData.PlayerId-1].PosX += 2.5f;
				}
				if (m_RecvData.KeyCommand[KEY_UP] == KEY_ON)
				{
					m_pPlayerData[m_RecvData.PlayerId-1].PosY -= 2.5f;
				}
				if (m_RecvData.KeyCommand[KEY_DOWN] == KEY_ON)
				{
					m_pPlayerData[m_RecvData.PlayerId-1].PosY += 2.5f;
				}
			}
			sendto(sock, reinterpret_cast<char*>(m_pPlayerData), sizeof(PlayerData)*playerNum, 0, (struct sockaddr *)&addr, sizeof(addr));
		}
	}
	close(sock);
}
