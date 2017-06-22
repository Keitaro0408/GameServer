/*
 * WaitScene.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef WAITSCENE_H_
#define WAITSCENE_H_
#include "../SceneBase.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include "../../GameDataManager/GameDataManager.h"


class WaitScene : public SceneBase
{
public:
	WaitScene();
	virtual ~WaitScene();

	virtual SceneBase::SceneID Update();

private:
	struct SendData
	{
		int32_t PlayerNum;
		int32_t Id;
		bool IsStart;
	};

	struct RecvData
	{
		int32_t Id;
		bool IsOk;
		bool IsMapLoad;
	};

	void RecvControl(int _socket);

	std::thread 		  KeyControlThread;
	std::vector<GameDataManager::PlayerData> m_PlayerList;
	RecvData			  m_RecvData;
	SendData			  m_SendData;
	int 	    		  m_Socket;
	sockaddr_in 		  m_Addr;
	fd_set  			  m_Fds, m_Readfds;
	timeval 			  m_TimeOut;

};

#endif /* WAITSCENE_H_ */
