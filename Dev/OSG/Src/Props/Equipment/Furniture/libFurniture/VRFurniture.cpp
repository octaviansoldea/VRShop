#include <iostream>
#include <QVariant>

#include "VRAbstractGeomShape.h"

#include "VRDatabaseMgr.h"
#include "VRCupboard.h"
#include "VRContainer.h"

#include "VRFurniture.h"


using namespace osg;
using namespace std;
using namespace VR;

FurnitureParams::FurnitureParams() : AbstractObjectParams()	{
}

//=======================================================================

Furniture::Furniture(const FurnitureParams & aFurnitureParams) : AbstractObject(aFurnitureParams)	{
	setParams(aFurnitureParams);

	setName("Furniture");
}

//-----------------------------------------------------------------------

Furniture::Furniture(const Furniture& fur,const CopyOp& copyop) : AbstractObject(fur, copyop)	{
	FurnitureParams aFp;
	fur.getParams(aFp);
	setParams(aFp);
}

//-----------------------------------------------------------------------

Furniture::~Furniture()	{
}

//-----------------------------------------------------------------------

const char* Furniture::className() const	{
	return "Furniture";
}

//-----------------------------------------------------------------------

void Furniture::addPart(ref_ptr < AbstractObject > apAbstractObject) {
	addChild(apAbstractObject);

	string & strCommand = apAbstractObject->getSQLCommand();

	m_arrSQLCommandLines.push_back(strCommand);
}

//-----------------------------------------------------------------------

void Furniture::removePart(unsigned int anPartNo)	{
	if (anPartNo >= getNumChildren())
		return;

	ref_ptr<AbstractObject> pFurniturePart = dynamic_cast<AbstractObject*>(getChild(anPartNo));
	removeChild(pFurniturePart);
}

//-----------------------------------------------------------------------

void Furniture::removePart(ref_ptr < AbstractObject > &aAbstractObject)	{
	vector <ref_ptr<Node>>::const_iterator it = _children.begin();
	for (it; it != _children.end(); it++)	{
		if (*it==aAbstractObject)	{
			removeChild(*it);
			return;
		}
	}
}

//-----------------------------------------------------------------------

string Furniture::getSQLCommand() const {
	return string(0);
}

//-----------------------------------------------------------------------

void Furniture::loadAllFurnitures(ref_ptr<Group> apScene, const string & astrDatabase) {
	DatabaseMgr & database = DatabaseMgr::Create(astrDatabase.c_str(), DatabaseMgr::QSQLITE);

	QString qstrFurniture = "SELECT EquipmentItemName FROM EquipmentItem JOIN Equipment ON EquipmentName = 'Furniture'";
	QSqlQuery qQuery(qstrFurniture);

	vector<string> arrstrEquipmentItems;
	while (qQuery.next())	{
		arrstrEquipmentItems.push_back(qQuery.value(0).toString().toStdString());
	}

	vector<string>::iterator it;
	ref_ptr<Furniture> pFurniture;
	for(it = arrstrEquipmentItems.begin(); it != arrstrEquipmentItems.end(); it++) {
		pFurniture = static_cast<Furniture*>(Furniture::createInstance(*it).get());
		
		string strSQLQuery = "SELECT * FROM EquipmentItem WHERE EquipmentItemName = '" + *it + "'";
		string strSQLData = database.readFromDB(strSQLQuery);
		pFurniture->initFromSQLData(strSQLData);

		apScene->addChild(pFurniture);
	}
}

//-----------------------------------------------------------------------

void Furniture::addChild2DB(vector<string> &avecItems)	{
	Furniture * pFurniture = dynamic_cast<Furniture*>(this);

	vector<string> * pvecItems = &avecItems;

	string strClassName = pFurniture->className();
	const string * pstrObjectName = &pFurniture->getName();
	string strItem = (strClassName + ";" + *pstrObjectName + ";" + pFurniture->SQLFieldValues());
	pvecItems->push_back(strItem);

	AbstractObject * pChild = 0;
	NodeList::iterator it;
	for (it = pFurniture->_children.begin(); it != pFurniture->_children.end(); it++)	{
		pChild = dynamic_cast<AbstractObject*>(it->get());

		strClassName = pChild->className();
		pstrObjectName = &pChild->getName();
		strItem = (strClassName + ";" + *pstrObjectName + ";" + pChild->SQLFieldValues());

		pvecItems->push_back("  " + strItem);
	}
}

//-----------------------------------------------------------------------

string Furniture::SQLFieldValues()	{
	FurnitureParams furnitureParams;
	getParams(furnitureParams);

	string strfurnitureParams;
	strfurnitureParams = to_string((long double)furnitureParams.m_flPosX) + "_";
	strfurnitureParams += to_string((long double)furnitureParams.m_flPosY) + "_";
	strfurnitureParams += to_string((long double)furnitureParams.m_flPosZ) + "_";

	strfurnitureParams += to_string((long double)furnitureParams.m_flLenX) + "_";
	strfurnitureParams += to_string((long double)furnitureParams.m_flLenY) + "_";
	strfurnitureParams += to_string((long double)furnitureParams.m_flLenZ) + "_";

	strfurnitureParams += to_string((long double)furnitureParams.m_flAngleYZ) + "_";
	strfurnitureParams += to_string((long double)furnitureParams.m_flAngleXZ) + "_";
	strfurnitureParams += to_string((long double)furnitureParams.m_flAngleXY) + ";";

	return strfurnitureParams;
}