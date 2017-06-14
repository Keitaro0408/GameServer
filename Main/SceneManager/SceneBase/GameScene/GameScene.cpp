/*
 * GameScene.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "GameScene.h"

GameScene::GameScene() :
SceneBase(SceneBase::SCENE_GAME)
{
	m_pServerStateDisplay = new ServerStateDisplay();
	FD_ZERO(&m_Readfds);
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	m_Addr.sin_family = AF_INET;
	m_Addr.sin_port = htons(50000);
	m_Addr.sin_addr.s_addr = INADDR_ANY;

	bind(m_Socket, (sockaddr *)&m_Addr, sizeof(m_Addr));
	FD_SET(m_Socket, &m_Readfds);

	m_TimeOut.tv_sec = 2;
	m_TimeOut.tv_usec = 0;

}

GameScene::~GameScene()
{
	close(m_Socket);
	delete m_pServerStateDisplay;
	m_pServerStateDisplay = nullptr;
}

SceneBase::SceneID GameScene::Update()
{
	memcpy(&m_Fds, &m_Readfds, sizeof(fd_set));

	select(m_Socket+1, &m_Fds, NULL, NULL, &m_TimeOut);
	socklen_t addr_len = sizeof(sockaddr_in);

	if (FD_ISSET(m_Socket,&m_Fds))
	{
		recvfrom(m_Socket, reinterpret_cast<char*>(&m_RecvData), sizeof(RecvData), 0, (sockaddr*)&m_Addr, &addr_len);
		if (m_RecvData.KeyCommand[KEY_LEFT] == KEY_ON)
		{
			m_SendData.playerData.PosX -= 2.5f;
		}
		if (m_RecvData.KeyCommand[KEY_RIGHT] == KEY_ON)
		{
			m_SendData.playerData.PosX += 2.5f;
		}
		if (m_RecvData.KeyCommand[KEY_UP] == KEY_ON)
		{
			m_SendData.playerData.PosY -= 2.5f;
		}
		if (m_RecvData.KeyCommand[KEY_DOWN] == KEY_ON)
		{
			m_SendData.playerData.PosY += 2.5f;
		}
		m_pServerStateDisplay->SetPlayerState(1,m_SendData.playerData.PosX,m_SendData.playerData.PosY);
		sendto(m_Socket, reinterpret_cast<char*>(&m_SendData), sizeof(SendData), 0, (struct sockaddr *)&m_Addr, sizeof(m_Addr));
	}
	return m_SceneID;
}

void GameScene::Draw()
{
}
