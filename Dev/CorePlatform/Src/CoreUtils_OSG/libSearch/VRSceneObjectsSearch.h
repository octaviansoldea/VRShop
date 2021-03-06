#ifndef VR_SCENE_OBJECTS_SEARCH_H
#define VR_SCENE_OBJECTS_SEARCH_H

#include <QString>
#include <osg/ref_ptr>

namespace VR	{
	class DataStructureModel;
	class Scene;

	class SceneObjectsSearch	{

	public:
		SceneObjectsSearch();
		SceneObjectsSearch(const QString & aqstrSearchQuery, Scene * apScene);
		virtual ~SceneObjectsSearch();

		virtual DataStructureModel * getModel() const;

	protected:
		DataStructureModel * m_pDataStructureModel;
		osg::ref_ptr<Scene> m_pScene;

	private:
		void setupSearchData(const QString & aqstrSearchQuery);
	};
}
#endif //VR_SCENE_OBJECTS_SEARCH_H