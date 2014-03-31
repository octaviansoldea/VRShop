#include <iostream>

#include "VRScene.h"
#include "VRDatabaseManagerShopEditor.h"

#include "VRDatabaseController.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------------------------

DatabaseController::DatabaseController(
const string * apstrScene,
vector<string> * apvecstrData,
DB_OPERATION aenumDBOperation)	:
m_pstrScene(apstrScene),
m_pvecstrData(apvecstrData),
m_nDBOperation(aenumDBOperation)	{

	DatabaseManagerShopEditor * m_pDBMgrShopEditor = new DatabaseManagerShopEditor;

	if (m_nDBOperation == DatabaseController::ADD)	{
		m_pDBMgrShopEditor->insertObject(*m_pstrScene,*m_pvecstrData);
	} else if (m_nDBOperation == DatabaseController::REMOVE)	{
//		m_pDBMgrShopEditor->removeObject(*m_pstrScene,*m_pvecstrData);
	} else if (m_nDBOperation == DatabaseController::UPDATE)	{
//		m_pDBMgrShopEditor->updateObject(*m_pstrScene,*m_pvecstrData);
	} else {
	}

	delete m_pDBMgrShopEditor;
}

//======================================================================================

DatabaseController::~DatabaseController()	{
}

//-------------------------------------------------------------------------------------
