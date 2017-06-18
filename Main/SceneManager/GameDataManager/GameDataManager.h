/*
 * GameDataManager.h
 *
 *  Created on: 2017/06/18
 *      Author: kei
 */

#ifndef GAMEDATAMANAGER_H_
#define GAMEDATAMANAGER_H_
#include <thread>

class GameDataManager {
public:
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


private:
	GameDataManager();
	virtual ~GameDataManager();

	int32_t m_Id;
	int		m_PlayerNum;
};

#endif /* GAMEDATAMANAGER_H_ */
