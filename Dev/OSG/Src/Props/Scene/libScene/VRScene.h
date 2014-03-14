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

		virtual bool addChild(Node *child);
		virtual bool removeChild(Node *child);
		void clearScene();

		void setSceneHierarchy();
		void updateSceneHierarchy() {};
		std::vector<std::string> getSceneHierarchy();

		virtual void print();
private:
		int m_nIteration;
		std::vector<std::string> m_vecstrSceneHierarchy;
	};
}
#endif //VR_SCENE_H