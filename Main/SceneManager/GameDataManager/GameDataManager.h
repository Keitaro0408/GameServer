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
		int32_t Id;
		sockaddr_in Addr;
		bool IsOk;
	};

	static GameDataManager* GetInstance()
	{
		static GameDataManager instance;
		return &instance;
	}

	inline void SetId(int32_t _id)
	{
		m_Id = _id;
	}

	inline int32_t GetId()
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

	int32_t m_Id;
	int		m_PlayerNum;
	std::vector<PlayerData> m_PlayerList;

};

#endif /* GAMEDATAMANAGER_H_ */
