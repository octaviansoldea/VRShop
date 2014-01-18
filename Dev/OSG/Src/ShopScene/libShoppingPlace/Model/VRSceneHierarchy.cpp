#include <iostream>

#include "StringManipulation.h"

#include "VRAbstractObject.h"

#include "VRSceneHierarchy.h"

using namespace VR;
using namespace osg;
using namespace std;

SceneHierarchyItem::SceneHierarchyItem(const ref_ptr<Node> apNode)	{
	m_pParent = static_cast<SceneHierarchyItem*>(apNode.get());
	
	int nI;
	for (nI=0; nI < m_pParent->asGroup()->getNumChildren(); nI++)	{
		m_pvecChildren.push_back(m_pParent->getChild(nI));
	}
}

//--------------------------------------------------------------------

SceneHierarchyItem * SceneHierarchyItem::getParent()	{
	return m_pParent;
}

//--------------------------------------------------------------------

SceneHierarchyItem * SceneHierarchyItem::getChild(int anChildNumber)	{
	return m_pvecChildren[anChildNumber];
}

//--------------------------------------------------------------------

vector <ref_ptr<SceneHierarchyItem> > SceneHierarchyItem::getChildren() const	{
	return m_pvecChildren;
}

//--------------------------------------------------------------------

int SceneHierarchyItem::sizeParent() const	{
	return m_pvecChildren.size();
}

//====================================================================

SceneHierarchy::SceneHierarchy(const ref_ptr<Group> apScene) : m_strIndent("")	{

	m_lstqstrSceneHierarchy.push_back("Agents");
	m_lstqstrSceneHierarchy.push_back("Furniture");
	m_lstqstrSceneHierarchy.push_back("Products");

	m_pSceneHierarchyItem = new SceneHierarchyItem(apScene);
	setSceneHierarchy(m_pSceneHierarchyItem->getChildren());
}

//--------------------------------------------------------------------

void SceneHierarchy::setSceneHierarchy(const vector < ref_ptr<SceneHierarchyItem> > apSceneItems)	{
	if (!apSceneItems.size())	
		return;

	string strSceneObjectData;
	vector < string > strvecData;

	for (auto it = apSceneItems.begin(); it != apSceneItems.end(); it++)	{
		string strData = it->get()->getName().c_str();

		//strData: Furniture:Container
		strvecData = splitString(strData, ":");

		int nPosition = m_lstqstrSceneHierarchy.indexOf(strvecData[0].c_str());

		if (nPosition < 0)
			nPosition = 0;

		setIndent(strvecData.size()-1);
		strSceneObjectData = (getIndent() + strvecData[strvecData.size()-1]).c_str();

		m_lstqstrSceneHierarchy.insert(nPosition+1, strSceneObjectData.c_str());
	}
}

//--------------------------------------------------------------------

QList < QString > SceneHierarchy::getSceneHierarchy() const	{
	
	return m_lstqstrSceneHierarchy;
}

//--------------------------------------------------------------------

void SceneHierarchy::setIndent(int anLevel)	{
	m_strIndent = string(anLevel*2,' ');
}

//--------------------------------------------------------------------

string SceneHierarchy::getIndent() const	{
	return m_strIndent;
}