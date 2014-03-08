#ifndef VR_SCENE_OBJECTS_SEARCH_SHOP_EDITOR_H
#define VR_SCENE_OBJECTS_SEARCH_SHOP_EDITOR_H

#include "VRSceneObjectsSearch.h"

namespace VR	{
	class SceneObjectsSearchShopEditor : SceneObjectsSearch	{

	public:
		SceneObjectsSearchShopEditor(const std::string & astrSearchQuery, const Scene * apScene);

		~SceneObjectsSearchShopEditor();

		virtual SceneStructureModel * getModel() const;

//		void 
	};
}
#endif //VR_SCENE_OBJECTS_SEARCH_SHOP_EDITOR_H