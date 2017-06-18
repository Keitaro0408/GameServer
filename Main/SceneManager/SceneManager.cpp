/*
 * SceneManager.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "SceneManager.h"


SceneManager::SceneManager() :
m_pScene(nullptr),
m_State(SCENE_CREATE),
m_NextSceneID(SceneBase::SCENE_WAIT),
m_IsGameEnd(false)
{
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool SceneManager::Run()
{
	Update();
	return m_IsGameEnd;
}

void SceneManager::Update()
{
	SceneBase::SceneID CurrentSceneID;

	switch (m_State)
	{
	case SCENE_CREATE:
		if (m_NextSceneID == SceneBase::FIN)
		{
			m_IsGameEnd = true;
			return;
		}
		else
		{
			m_pScene = SceneFactory::CreateScene(m_NextSceneID);
			m_State = SCENE_PROC;
		}
		break;
	case SCENE_PROC:
		CurrentSceneID = m_pScene->GetSceneID();
		m_NextSceneID = m_pScene->Update();

		if (m_NextSceneID != CurrentSceneID)
		{
			m_State = SCENE_RELEASE;
		}
		break;
	case SCENE_RELEASE:
		delete m_pScene;
		m_pScene = nullptr;

		m_State = SCENE_CREATE;
		break;
	}
}
