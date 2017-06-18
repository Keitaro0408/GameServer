/*
 * WaitScene.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "WaitScene.h"
#include <cstdlib>
#include <arpa/inet.h>
#include "../../GameDataManager/GameDataManager.h"


WaitScene::WaitScene():
SceneBase(SceneBase::SCENE_WAIT)
{
	FD_ZERO(&m_Readfds);
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

	m_Addr.sin_family = AF_INET;
	m_Addr.sin_port = htons(50000);
	m_Addr.sin_addr.s_addr = INADDR_ANY;

	bind(m_Socket, (sockaddr *)&m_Addr, sizeof(m_Addr));

	FD_SET(m_Socket, &m_Readfds);

	m_TimeOut.tv_sec = 2;
	m_TimeOut.tv_usec = 0;
	m_SendData.Id = 0;
	m_SendData.IsStart = false;
}

WaitScene::~WaitScene()
{
	close(m_Socket);
}

SceneBase::SceneID WaitScene::Update()
{
	memcpy(&m_Fds, &m_Readfds, sizeof(fd_set));
	select(0, &m_Fds, NULL, NULL, &m_TimeOut);

	if (FD_ISSET(m_Socket,&m_Fds))
	{
		RecvControl(m_Socket);
	}

	return m_SceneID;
}

void WaitScene::RecvControl(int _socket)
{
	auto CheckIsStart = [&]()
	{
		for(unsigned int i = 0;i < m_PlayerList.size();i++)
		{
			if(!m_PlayerList[i].IsOk)
			{
				return false;
			}
		}
		return true;
	};

	auto SetIsOk = [&]()
	{
		for(unsigned int i = 0;i < m_PlayerList.size();i++)
		{
			if(m_PlayerList[i].Id == m_RecvData.Id)
			{
				printf("%d Ready", m_RecvData.Id);
				m_PlayerList[i].IsOk = m_RecvData.IsOk;
				break;
			}
		}
	};

	socklen_t addr_len = sizeof(sockaddr_in);
	recvfrom(_socket, reinterpret_cast<char*>(&m_RecvData), sizeof(RecvData), 0, (sockaddr*)&m_Addr, &addr_len);
	if(m_PlayerList.size() == 0)
	{
		PlayerData playerData;
		playerData.IsOk = false;
		playerData.Addr = m_Addr;
		playerData.Id = 1;
		m_PlayerList.push_back(playerData);
		printf("join from : %s\n",inet_ntoa(m_Addr.sin_addr));
		printf("       Id : %d\n\n",playerData.Id);
	}
	else
	{
		if(m_RecvData.Id == 0)
		{
			PlayerData playerData;
			playerData.IsOk = false;
			playerData.Id = m_PlayerList.size() + 1;
			playerData.Addr = m_Addr;
			m_PlayerList.push_back(playerData);
			printf("join from : %s\n",inet_ntoa(m_Addr.sin_addr));
			printf("       Id : %d\n\n",playerData.Id);
		}
	}


	SetIsOk();

	for(unsigned int i = 0; i < m_PlayerList.size();i++)
	{
		m_SendData.Id = m_PlayerList[i].Id;
		m_Addr = m_PlayerList[i].Addr;
		m_SendData.IsStart = false;
		m_SendData.PlayerNum = m_PlayerList.size();
		if(CheckIsStart())
		{
			m_SendData.IsStart = true;
		}

		sendto(_socket, reinterpret_cast<char*>(&m_SendData),
					sizeof(SendData), 0, (struct sockaddr *)&m_Addr, sizeof(m_Addr));
	}

	if(CheckIsStart())
	{
		GameDataManager::GetInstance()->SetPlayerNum(m_PlayerList.size());
		m_SceneID = SceneBase::SCENE_GAME;
	}
}
