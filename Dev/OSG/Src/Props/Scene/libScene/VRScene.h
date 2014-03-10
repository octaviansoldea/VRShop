#ifndef VR_SCENE_H
#define VR_SCENE_H

#include <osg/Group>

namespace VR	{

	class AbstractObject;

	class Scene : public osg::Group	{
	public:
		Scene();
		~Scene();

		Node * getChild(const std::string & astrChildName);
        /** Return child node at position i. */
        inline Node* getChild( unsigned  int i ) { return _children[i].get(); }

        /** Return child node at position i. */
        inline const Node* getChild( unsigned  int i ) const { return _children[i].get(); }

		void addElement(osg::ref_ptr<osg::Node> apElement);
		void removeElement(osg::ref_ptr<osg::Node> apElement);
		void clearScene();

		void print();
		static int m_nIteration;
	};
}
#endif //VR_SCENE_H