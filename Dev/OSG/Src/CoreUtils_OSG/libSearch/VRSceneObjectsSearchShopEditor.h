#ifndef VR_SCENE_OBJECTS_SEARCH_SHOP_EDITOR_H
#define VR_SCENE_OBJECTS_SEARCH_SHOP_EDITOR_H

#include "VRSceneObjectsSearch.h"

#include <QObject>

namespace VR	{
	class AbstractObject;

	class SceneObjectsSearchShopEditor : public QObject, public SceneObjectsSearch	{
		Q_OBJECT

	public:
		SceneObjectsSearchShopEditor();
		SceneObjectsSearchShopEditor(const QString & aqstrSearchQuery, Scene * apScene);

		~SceneObjectsSearchShopEditor();

		virtual DataStructureModel * getModel() const;

	public slots:
		void slotChangeName(const QModelIndex & anIndex);
	};
}
#endif //VR_SCENE_OBJECTS_SEARCH_SHOP_EDITOR_H