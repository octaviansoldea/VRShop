/*

FURNITURE
	CUPBOARD
	CONTAINER
GEOMETRIC SHAPE
AGENTS

*/
#ifndef VR_SCENE_HIERARCHY_H
#define VR_SCENE_HIERARCHY_H

#include <osg/Node>
#include <osg/Group>

#include <QString>
#include <QList>
#include <vector>

namespace VR	{
	class SceneHierarchyItem : public osg::Node	{
	public:
		SceneHierarchyItem(const osg::ref_ptr<osg::Node> apNode);

		SceneHierarchyItem * getParent();
		SceneHierarchyItem * getChild(int anChildNumber);

		std::vector < osg::ref_ptr<SceneHierarchyItem> > getChildren() const;

		int sizeParent() const;

	private:
		std::vector < osg::ref_ptr<SceneHierarchyItem> > m_pvecChildren;
		osg::ref_ptr<SceneHierarchyItem> m_pParent;
	};


	class SceneHierarchy	{
	public:
		SceneHierarchy(const osg::ref_ptr<osg::Group> apScene);

		void setSceneHierarchy(const std::vector < osg::ref_ptr<SceneHierarchyItem> > apSceneItems);
		QList < QString > getSceneHierarchy() const;

	private:
		QList < QString > m_lstqstrSceneHierarchy;
		SceneHierarchyItem * m_pSceneHierarchyItem;

		std::string m_strIndent;
		void setIndent(int anLevel);
		std::string getIndent() const;	
	};
}
#endif //VR_SCENE_HIERARCHY_H
