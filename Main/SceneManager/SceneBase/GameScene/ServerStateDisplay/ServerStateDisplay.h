/*
 * ServerStateDisplay.h
 *
 *  Created on: 2017/06/02
 *      Author: kei
 */

#ifndef SERVERSTATEDISPLAY_H_
#define SERVERSTATEDISPLAY_H_
#include <thread>
#include "../GameScene.h"
#include "../../../GameDataManager/GameDataManager.h"


class ServerStateDisplay {
public:
	ServerStateDisplay();
	~ServerStateDisplay();

	void Loop();

	inline void SetPlayerData(GameScene::PlayerData* _playerData)
	{
		m_pPlayerData = _playerData;
	}
private:
	struct PlayerData
	{
		int32_t	Id;
		float PosX,PosY;
	};

	GameScene::PlayerData* m_pPlayerData;
	std::thread* m_pThread;
	bool		 m_IsEnd;
};

#endif /* SERVERSTATEDISPLAY_H_ */
