/*
 * WaitScene.cpp
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#include "WaitScene.h"

WaitScene::WaitScene():
SceneBase(SceneBase::SCENE_WAIT)
{

}

WaitScene::~WaitScene()
{
}

SceneBase::SceneID WaitScene::Update()
{
	return m_SceneID;
}

void WaitScene::Draw()
{
}
