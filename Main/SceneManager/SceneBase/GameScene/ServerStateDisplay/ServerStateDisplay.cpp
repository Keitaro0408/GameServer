/*
 * ServerStateDisplay.cpp
 *
 *  Created on: 2017/06/02
 *      Author: kei
 */

#include "ServerStateDisplay.h"
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>


ServerStateDisplay::ServerStateDisplay()
{
	m_IsEnd = false;
	m_pThread = new std::thread(&ServerStateDisplay::Loop,this);
	m_pPlayerData = nullptr;
}

ServerStateDisplay::~ServerStateDisplay()
{
	m_IsEnd = true;
	m_pThread->join();
	delete m_pThread;
}

void ServerStateDisplay::Loop()
{
	while(!m_IsEnd)
	{
		sleep(1);
		std::system("clear");
		printf("+------------+\n");
		printf("| PlayerData |\n");
		printf("+------------+\n");

		int playerNum = GameDataManager::GetInstance()->GetPlayerNum();
		for(int i = 0; i < playerNum;i++)
		{
			printf(" ID = %d \n", m_pPlayerData[i].Id);
			printf("  X = %f \n", m_pPlayerData[i].PosX);
			printf("  Y = %f \n\n", m_pPlayerData[i].PosY);
		}
	}
}
