/*
 * ServerStateDisplay.h
 *
 *  Created on: 2017/06/02
 *      Author: kei
 */

#ifndef SERVERSTATEDISPLAY_H_
#define SERVERSTATEDISPLAY_H_
#include <thread>

class ServerStateDisplay {
public:
	ServerStateDisplay();
	~ServerStateDisplay();

	void Loop();

	inline void SetPlayerState(int32_t _id, float _posX, float _posY)
	{
		m_PlayerData.Id = _id;
		m_PlayerData.PosX = _posX;
		m_PlayerData.PosY = _posY;

	}
private:
	struct PlayerData
	{
		int32_t	Id;
		float PosX,PosY;
	};

	std::thread* m_pThread;
	PlayerData   m_PlayerData;
	bool		 m_IsEnd;
};

#endif /* SERVERSTATEDISPLAY_H_ */
