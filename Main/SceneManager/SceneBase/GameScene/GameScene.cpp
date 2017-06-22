/*
 * GameScene.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "GameScene.h"
#include "../../GameDataManager/GameDataManager.h"
#include "ServerStateDisplay/ServerStateDisplay.h"
#include "Map/Map.h"


GameScene::GameScene() :
SceneBase(SceneBase::SCENE_GAME),
m_IsThreadEnd(false)
{
	m_pMap = new Map();
	m_pServerStateDisplay = new ServerStateDisplay();
	int playerNum = GameDataManager::GetInstance()->GetPlayerNum();
	m_pPlayerData = new SendData[playerNum];
	for(int i = 0;i < playerNum;i++)
	{
		m_pPlayerData[i].Id = 0;
		m_pPlayerData[i].PosX = 300.f;
		m_pPlayerData[i].PosY = 300.f;
		m_pPlayerData[i].IsRight = true;
		PlayerState playerState;
		playerState.IsJump = false;
		playerState.JumpAcceleration = 0.f;
		playerState.RectCollisionX = 0.f;
		playerState.RectCollisionY = 0.f;
		m_PlayerState.push_back(playerState);
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

	delete m_pMap;
	m_pMap = nullptr;
}

SceneBase::SceneID GameScene::Update()
{
	int playerNum = GameDataManager::GetInstance()->GetPlayerNum();

	for(int i = 0;i < playerNum;i++)
	{
		int underPlayerMapChipNumX = m_pPlayerData[i].PosX / CHIP_WIDTH;
		int underPlayerMapChipNumY = (m_pPlayerData[i].PosY + 20.f) / CHIP_WIDTH;

		int bottomPlayerMapChipNumX = m_pPlayerData[i].PosX / CHIP_WIDTH;
		int bottomPlayerMapChipNumY = (m_pPlayerData[i].PosY - 20.f) / CHIP_WIDTH;

		if(underPlayerMapChipNumX > MAP_WIDTH ||
				underPlayerMapChipNumY > MAP_HEIGHT )
		{
			m_pPlayerData[i].PosY = 200.f;
			m_pPlayerData[i].PosX = 600.f;
			m_PlayerState[i].JumpAcceleration = 0;
		}
		else
		{
			if(m_PlayerState[i].IsJump)
			{
				m_pPlayerData[i].PosY += m_PlayerState[i].JumpAcceleration;
				m_PlayerState[i].JumpAcceleration += GRAVITY;

				underPlayerMapChipNumX = m_pPlayerData[i].PosX / CHIP_WIDTH;
				underPlayerMapChipNumY = (m_pPlayerData[i].PosY + 20.f) / CHIP_WIDTH;

				bottomPlayerMapChipNumX = m_pPlayerData[i].PosX / CHIP_WIDTH;
				bottomPlayerMapChipNumY = (m_pPlayerData[i].PosY - 20.f) / CHIP_WIDTH;

				if(m_pMap->GetMapData().Data[bottomPlayerMapChipNumY][bottomPlayerMapChipNumX] == 1)
				{
					m_pPlayerData[i].PosY += (m_pPlayerData[i].PosY - 20.f) - (bottomPlayerMapChipNumY * 32 + 16);
					m_PlayerState[i].JumpAcceleration = 0;
				}

				if(m_pMap->GetMapData().Data[underPlayerMapChipNumY][underPlayerMapChipNumX] == 1)
				{
					m_pPlayerData[i].PosY -= (m_pPlayerData[i].PosY + 20.f) - (underPlayerMapChipNumY * 32 - 16);
					m_PlayerState[i].IsJump = false;
					m_PlayerState[i].JumpAcceleration = 0;
				}
			}
			else if(m_pMap->GetMapData().Data[underPlayerMapChipNumY+1][underPlayerMapChipNumX] == 0)
			{
				m_PlayerState[i].IsJump = true;
			}
		}
	}

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
					m_pPlayerData[m_RecvData.PlayerId-1].IsRight = false;
					m_pPlayerData[m_RecvData.PlayerId-1].PosX -= 2.5f;
					int leftPlayerMapChipNumX = (m_pPlayerData[m_RecvData.PlayerId-1].PosX - 30.f ) / CHIP_WIDTH;
					int leftPlayerMapChipNumY = m_pPlayerData[m_RecvData.PlayerId-1].PosY / CHIP_WIDTH;
					if(m_pMap->GetMapData().Data[leftPlayerMapChipNumY][leftPlayerMapChipNumX])
					{
						m_pPlayerData[m_RecvData.PlayerId-1].PosX += 2.5f;
					}
				}
				if (m_RecvData.KeyCommand[KEY_RIGHT] == KEY_ON)
				{
					m_pPlayerData[m_RecvData.PlayerId-1].IsRight = true;
					m_pPlayerData[m_RecvData.PlayerId-1].PosX += 2.5f;
					int rightPlayerMapChipNumX = (m_pPlayerData[m_RecvData.PlayerId-1].PosX + 30.f ) / CHIP_WIDTH;
					int rightPlayerMapChipNumY = m_pPlayerData[m_RecvData.PlayerId-1].PosY / CHIP_WIDTH;
					if(m_pMap->GetMapData().Data[rightPlayerMapChipNumY][rightPlayerMapChipNumX])
					{
						m_pPlayerData[m_RecvData.PlayerId-1].PosX -= 2.5f;
					}
				}
				if (m_RecvData.KeyCommand[KEY_UP] == KEY_PUSH && !m_PlayerState[m_RecvData.PlayerId-1].IsJump)
				{
					m_PlayerState[m_RecvData.PlayerId-1].IsJump = true;
					m_PlayerState[m_RecvData.PlayerId-1].JumpAcceleration = JUMP_POWER;
				}
				if (m_RecvData.KeyCommand[KEY_DOWN] == KEY_ON)
				{
				}
			}
			sendto(sock, reinterpret_cast<char*>(m_pPlayerData), sizeof(SendData)*playerNum, 0, (struct sockaddr *)&addr, sizeof(addr));
		}
	}
	close(sock);
}

void GameScene::CollisionCheck(SendData* _playerData)
{

}
