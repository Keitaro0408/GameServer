/*
 * GameDataManager.h
 *
 *  Created on: 2017/06/18
 *      Author: kei
 */

#ifndef GAMEDATAMANAGER_H_
#define GAMEDATAMANAGER_H_
#include <thread>
#include <netinet/in.h>
#include <vector>


class GameDataManager {
public:
	struct PlayerData
	{
		unsigned char Id;
		sockaddr_in Addr;
		bool IsOk;
	};

	static GameDataManager* GetInstance()
	{
		static GameDataManager instance;
		return &instance;
	}

	inline void SetId(unsigned char _id)
	{
		m_Id = _id;
	}

	inline unsigned char GetId()
	{
		return m_Id;
	}

	inline void SetPlayerNum(int _playerNum)
	{
		m_PlayerNum = _playerNum;
	}

	inline int GetPlayerNum()
	{
		return m_PlayerNum;
	}

	inline void SetPlayerData(const std::vector<PlayerData>& _playerData)
	{
		m_PlayerList = _playerData;
	}

	inline std::vector<PlayerData> GetPlayerData()
	{
		return m_PlayerList;
	}


private:
	GameDataManager();
	virtual ~GameDataManager();

	unsigned char m_Id;
	int		m_PlayerNum;
	std::vector<PlayerData> m_PlayerList;

};

#endif /* GAMEDATAMANAGER_H_ */
