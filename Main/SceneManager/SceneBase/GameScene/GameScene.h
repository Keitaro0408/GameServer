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
#include <vector>

#define JUMP_POWER -20.f
#define GRAVITY 0.6f
#define BULLET_SPEED 15.f

class ServerStateDisplay;
class Map;

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
		KEY_FIRE,
		KEY_MAX
	};

	struct BulletData
	{
		float	PosX, PosY;
		bool 	IsRight,IsEnable;
	};

	struct SendData
	{
		int32_t	Id;
		BulletData bulletData[3];
		float	PosX, PosY;
		bool 	IsRight;
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
	struct PlayerState
	{
		bool IsJump;
		float JumpAcceleration;
		float InpactForceX;
		float InpactForceY;
	};

	void RecvControl();
	void PlayerCollisionCheck();
	void BulletControl();

	SendData* 			m_pPlayerData;
	std::vector<PlayerState> m_PlayerState;
	RecvData    		m_RecvData;
	Map*				m_pMap;
	ServerStateDisplay* m_pServerStateDisplay;
	std::thread*		m_pUdpThread;
	bool				m_IsThreadEnd;


};

#endif /* GAMESCENE_H_ */
