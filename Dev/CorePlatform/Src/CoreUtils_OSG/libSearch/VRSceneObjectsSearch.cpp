#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRScene.h"

#include "VRDataStructureModel.h"

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
	delete m_pDataStructureModel;
}

//--------------------------------------------------------------------

DataStructureModel * SceneObjectsSearch::getModel() const	{
	return m_pDataStructureModel;
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
		m_pDataStructureModel = 0;
		return;
	}

	DataStructureModelParams sP;
	sP.data = data;

	m_pDataStructureModel = new DataStructureModel(sP);
}