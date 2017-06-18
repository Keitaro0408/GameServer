/*
 * SceneBase.h
 *
 *  Created on: 2017/06/14
 *      Author: kei
 */

#ifndef SCENEBASE_H_
#define SCENEBASE_H_
#include <sys/types.h>

class SceneBase {
public:
	enum SceneID
	{
		SCENE_WAIT,
		SCENE_GAME,
		FIN
	};

	SceneBase(SceneID _sceneID)
	{
		m_SceneID = _sceneID;
	}

	virtual ~SceneBase(){};

	virtual SceneID Update() = 0;

	inline SceneID GetSceneID() const
	{
		return m_SceneID;
	}

protected:
	SceneID m_SceneID;
};


#endif /* SCENEBASE_H_ */
