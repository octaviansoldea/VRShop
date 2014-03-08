#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRScene.h"

#include "VRSceneStructureModel.h"

#include "VRSceneObjectsSearch.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

SceneObjectsSearch::SceneObjectsSearch(const string & astrSearchQuery, const Scene * apScene)	{
	setupSearchData(astrSearchQuery, apScene);
}

//--------------------------------------------------------------------

SceneObjectsSearch::~SceneObjectsSearch()	{
	delete m_pSceneStructureModel;
}

//--------------------------------------------------------------------

SceneStructureModel * SceneObjectsSearch::getModel() const	{
	return m_pSceneStructureModel;
}

//--------------------------------------------------------------------

void SceneObjectsSearch::setupSearchData(const std::string & astrSearchQuery, const Scene * apScene)	{
	string strSearchQuery = astrSearchQuery;
	vector<string> & strvecSearchQueries = splitString(strSearchQuery,",; ");

	QList<QString> data;

	int nI;	
	for (nI=0;nI<apScene->getNumChildren(); nI++)	{
		string strObjectName = apScene->getChild(nI)->getName();
		if (isInString(strObjectName,astrSearchQuery))
			data.push_back(strObjectName.c_str());
	}

	if (data.isEmpty())	{
		m_pSceneStructureModel = 0;
		return;
	}

	SceneStructureModelParams * sP = new SceneStructureModelParams;
	sP->data = data;

	m_pSceneStructureModel = new SceneStructureModel(*sP);
}