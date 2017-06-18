/*
 * GameScene.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "../SceneBase.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <thread>

class ServerStateDisplay;

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


	struct RecvData
	{
		int32_t  PlayerId;
		KEYSTATE KeyCommand[KEY_MAX];
	};

	GameScene();
	virtual ~GameScene();

	SceneBase::SceneID Update() override;

	void ConnectLoop();

private:
	PlayerData* 		m_pPlayerData;
	RecvData    		m_RecvData;
	ServerStateDisplay* m_pServerStateDisplay;
	std::thread*		m_pUdpThread;
	bool				m_IsThreadEnd;


};

#endif /* GAMESCENE_H_ */
