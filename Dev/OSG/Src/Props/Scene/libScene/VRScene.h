#ifndef VR_SCENE_H
#define VR_SCENE_H

#include <osg/Group>

#include <string>

namespace VR	{

	class AbstractObject;

	class Scene : public osg::Group	{
	public:
		Scene();
		~Scene();

		virtual const char* className() const;

		Node * getChild(const std::string & astrChildName);
        inline Node* getChild( unsigned  int i ) { return _children[i].get(); }
        inline const Node* getChild( unsigned  int i ) const { return _children[i].get(); }

		void addElement(osg::ref_ptr<osg::Node> apElement);
		void removeElement(osg::ref_ptr<osg::Node> apElement);
		void clearScene();

		void setSceneHierarchy();
		std::vector<std::string> getSceneHierarchy();

		void print();
		static int m_nIteration;

	private:
		std::vector<std::string> m_vecstrSceneHierarchy;
	};
}
#endif //VR_SCENE_H