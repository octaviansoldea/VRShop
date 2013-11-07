#include <osg/Group>

#include "BaseModel.h"

using namespace osg;

BaseModel::BaseModel() : 
m_bIsTargetPick(false),
m_pvecNodeList(0)
{
}

//--------------------------------------------------------------------------

void BaseModel::setIsTargetPick(bool abIsTargetPick)	{
	m_bIsTargetPick = abIsTargetPick;
}

//--------------------------------------------------------------------------

bool BaseModel::getIsTargetPick() const	{
	return m_bIsTargetPick;
}

//--------------------------------------------------------------------------

std::vector < Node *> BaseModel::getNodeList() const	{
	return m_pvecNodeList;
}

//--------------------------------------------------------------------------

bool BaseModel::addNode2List( Node * apNode)	{
	if (apNode)	{
		std::vector <Node*> vecList = getNodeList();
		vecList.push_back(apNode);

		int nI;
		for (nI=0;nI<vecList.size();nI++)	{
			m_pvecNodeList.push_back(vecList.at(nI));
		}
		return true;
	}
	else 
		return false;
}

//--------------------------------------------------------------------------

bool BaseModel::removeNodeFromList( osg::Node * apNode)	{
	std::vector<Node *> nodeList = getNodeList();
	return true;
}

//--------------------------------------------------------------------------

Group BaseModel::groupSelectedNodes(std::vector <osg::Node *> apvecNodeList)	{
	if(apvecNodeList.size()>0)	{
		ref_ptr<Group> grp = new Group;
		int nI;
		for (nI=0;nI<apvecNodeList.size();nI++)	{
			ref_ptr<osg::Node> node = apvecNodeList.at(nI);
//			node->setIsTargetPick(false);
			grp->addChild(node);
		}
		return *grp;
	}
}