/*
 * SceneManager.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include "SceneFactory/SceneFactory.h"
#include "SceneBase/SceneBase.h"


class SceneManager {
public:
	SceneManager();
	virtual ~SceneManager();

	/**
	 * ゲームの制御関数
	 * @return ゲームが終了したらtrue
	 */
	bool Run();

private:
	/**
	 * SceneManagerの状態
	 */
	enum State
	{
		SCENE_CREATE,	//!< シーンの生成状態
		SCENE_PROC,		//!< シーンの処理状態
		SCENE_RELEASE	//!< シーンの解放状態
	};

	/**
	 * 更新関数
	 */
	void Update();

	SceneBase*			m_pScene;
	State				m_State;
	SceneBase::SceneID	m_NextSceneID;
	bool				m_IsGameEnd;


};

#endif /* SCENEMANAGER_H_ */
