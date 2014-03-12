/*

FURNITURE
	CUPBOARD
		Cup1
		Cup2
		Cup3
	CONTAINER
GEOMETRIC SHAPE
AGENTS

*/
#ifndef VR_SCENE_HIERARCHY_H
#define VR_SCENE_HIERARCHY_H

#include <QString>
#include <QList>

#include "VRScene.h"

namespace VR	{
	class SceneHierarchy : public Scene	{
	public:
		SceneHierarchy();

		void setSceneHierarchy();
		QList < QString > getSceneHierarchy() const;

		void updateHierarchy();

	private:
		QList<QString> m_vecstrSceneHierarchy;
	};
}
#endif //VR_SCENE_HIERARCHY_H
