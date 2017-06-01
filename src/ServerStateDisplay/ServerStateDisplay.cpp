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
	m_PlayerData.Id = 0;
	m_PlayerData.PosX = 0;
	m_PlayerData.PosY= 0;
	m_pThread = new std::thread(&ServerStateDisplay::Loop,this);
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

		printf(" ID = %d \n",m_PlayerData.Id);
		printf(" X = %f \n", m_PlayerData.PosX);
		printf(" Y = %f \n", m_PlayerData.PosY);
	}
}
