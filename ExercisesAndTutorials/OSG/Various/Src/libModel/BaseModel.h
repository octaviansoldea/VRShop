#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include <vector>
#include <osg/Node>

class BaseModel {
public:
	BaseModel();

	virtual void setIsTargetPick(bool abIsTargetPick);
	virtual bool getIsTargetPick() const;

	std::vector < osg::Node *> getNodeList() const;
	bool addNode2List( osg::Node * apNode);
	bool removeNodeFromList( osg::Node * apNode);
	osg::Group groupSelectedNodes(std::vector <osg::Node *> apvecNodeList);

protected:
	bool m_bIsTargetPick;
	std::vector <osg::Node *> m_pvecNodeList;

};
#endif //BASE_MODEL_H