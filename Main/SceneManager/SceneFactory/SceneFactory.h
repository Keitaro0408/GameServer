/*
 * SceneFactory.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef SCENEFACTORY_H_
#define SCENEFACTORY_H_
#include "../SceneBase/SceneBase.h"

class SceneFactory {
public:
	static SceneBase* CreateScene(SceneBase::SceneID _sceneID);


private:
	SceneFactory();
	virtual ~SceneFactory();
};

#endif /* SCENEFACTORY_H_ */
