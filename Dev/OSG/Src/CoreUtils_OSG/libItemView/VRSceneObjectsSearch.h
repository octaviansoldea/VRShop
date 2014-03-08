#ifndef VR_SCENE_OBJECTS_SEARCH_H
#define VR_SCENE_OBJECTS_SEARCH_H

#include <string>
#include <QList>

namespace VR	{
	class SceneStructureModel;
	class Scene;

	class SceneObjectsSearch	{

	public:
		SceneObjectsSearch(const std::string & astrSearchQuery, const Scene * apScene);
		~SceneObjectsSearch();

		virtual SceneStructureModel * getModel() const;

	protected:
		SceneStructureModel * m_pSceneStructureModel;

	private:
		void setupSearchData(const std::string & astrSearchQuery, const Scene * apScene);
	};
}
#endif //VR_SCENE_OBJECTS_SEARCH_H