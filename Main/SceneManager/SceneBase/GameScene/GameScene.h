/*
 * GameScene.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "../SceneBase.h"
#include "ServerStateDisplay/ServerStateDisplay.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

class GameScene : public SceneBase
{
public:
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
		int32_t  PlayerId;
		KEYSTATE KeyCommand[KEY_MAX];
	};

	GameScene();
	virtual ~GameScene();

	SceneBase::SceneID Update() override;

	void Draw() override;

private:
	SendData    		m_SendData;
	RecvData    		m_RecvData;
	int 	    		m_Socket;
	sockaddr_in 		m_Addr;
	fd_set  			m_Fds, m_Readfds;
	timeval 			m_TimeOut;
	ServerStateDisplay* m_pServerStateDisplay;


};

#endif /* GAMESCENE_H_ */
