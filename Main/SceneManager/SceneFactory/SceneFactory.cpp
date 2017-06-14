/*
 * SceneFactory.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "SceneFactory.h"
#include "../SceneBase/WaitScene/WaitScene.h"
#include "../SceneBase/GameScene/GameScene.h"

SceneFactory::SceneFactory()
{
	// TODO 自動生成されたコンストラクター・スタブ

}

SceneFactory::~SceneFactory()
{
	// TODO Auto-generated destructor stub
}

SceneBase* SceneFactory::CreateScene(SceneBase::SceneID _sceneID)
{
	SceneBase* pScene = nullptr;

	switch(_sceneID)
	{
	case SceneBase::SCENE_WAIT:
		pScene = new WaitScene();
		break;
	case SceneBase::SCENE_GAME:
		pScene = new GameScene();
		break;
	case SceneBase::FIN:
		break;
	}

	return pScene;
}

