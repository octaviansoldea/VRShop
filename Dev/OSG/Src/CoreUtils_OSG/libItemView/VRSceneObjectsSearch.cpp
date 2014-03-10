#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRScene.h"

#include "VRSceneStructureModel.h"

#include "VRSceneObjectsSearch.h"

using namespace VR;
using namespace osg;
using namespace std;

//--------------------------------------------------------------------

SceneObjectsSearch::SceneObjectsSearch()	{
}

//--------------------------------------------------------------------

SceneObjectsSearch::SceneObjectsSearch(const QString & aqstrSearchQuery, Scene * apScene)	{
	m_pScene = apScene;
	setupSearchData(aqstrSearchQuery);
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

void SceneObjectsSearch::setupSearchData(const QString & aqstrSearchQuery)	{
	QString strSearchQuery = aqstrSearchQuery;
//	vector<string> & strvecSearchQueries = splitString(strSearchQuery,",; ");

	QList<QString> data;

	int nI;
	for (nI=0;nI<m_pScene->getNumChildren(); nI++)	{
		QString strObjectName = m_pScene->getChild(nI)->getName().c_str();
		if (strObjectName.contains(strSearchQuery,Qt::CaseInsensitive))
			data.push_back(strObjectName);
	}

	if (data.isEmpty())	{
		m_pSceneStructureModel = 0;
		return;
	}

	SceneStructureModelParams sP;
	sP.data = data;

	m_pSceneStructureModel = new SceneStructureModel(sP);
}