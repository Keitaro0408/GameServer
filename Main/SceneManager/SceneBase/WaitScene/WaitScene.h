/*
 * WaitScene.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef WAITSCENE_H_
#define WAITSCENE_H_
#include "../SceneBase.h"

class WaitScene : public SceneBase
{
public:
	WaitScene();
	virtual ~WaitScene();

	virtual SceneBase::SceneID Update();

	virtual void Draw();
};

#endif /* WAITSCENE_H_ */
