#ifndef VR_SCENE_OBJECTS_SEARCH_H
#define VR_SCENE_OBJECTS_SEARCH_H

#include <QString>

namespace VR	{
	class SceneStructureModel;
	class Scene;

	class SceneObjectsSearch	{

	public:
		SceneObjectsSearch();
		SceneObjectsSearch(const QString & aqstrSearchQuery, Scene * apScene);
		virtual ~SceneObjectsSearch();

		virtual SceneStructureModel * getModel() const;

	protected:
		SceneStructureModel * m_pSceneStructureModel;
		Scene * m_pScene;

	private:
		void setupSearchData(const QString & aqstrSearchQuery);
	};
}
#endif //VR_SCENE_OBJECTS_SEARCH_H