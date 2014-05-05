#ifndef VR_SCENE_H
#define VR_SCENE_H

#include <osg/Group>

#include <string>

namespace VR	{

	class AbstractObject;

	class Scene : public osg::Group	{
	public:
		Scene();
		Scene(const std::string & astrDBFileName);
		~Scene();

		virtual const char* className() const;

		Node * getChild(const std::string & astrChildName);
        inline Node* getChild( unsigned  int i ) { return _children[i].get(); }
        inline const Node* getChild( unsigned  int i ) const { return _children[i].get(); }

		virtual bool addChild(Node *child);
		virtual bool removeChild(Node *child);
		void clearScene();

		std::string SQLFieldValues(const std::string & astrParentName="");
		virtual void print();

		//NOT YET IN USE - POTENTIALLY USEFUL IN NODE SEARCHES
		Node * findNamedNode(const std::string& searchName, osg::Node* currNode);

	private:
		int m_nIteration;
		std::string m_strDBFileName;
	};
}
#endif //VR_SCENE_H