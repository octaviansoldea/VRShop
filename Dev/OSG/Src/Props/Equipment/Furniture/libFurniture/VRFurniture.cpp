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

Furniture::Furniture()	{
	setName("Furniture");
}

//-----------------------------------------------------------------------

Furniture::Furniture(const FurnitureParams & aFurnitureParams) : AbstractObject(aFurnitureParams)	{
	m_FurnitureParams = aFurnitureParams;
	setName("Furniture");
}

//-----------------------------------------------------------------------

Furniture::~Furniture()	{
}

//-----------------------------------------------------------------------

void Furniture::addPart(ref_ptr < AbstractObject > apAbstractObject) {
	addChild(apAbstractObject);

	string strCommand = apAbstractObject->getSQLCommand();

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

//void Furniture::removePart(ref_ptr < AbstractObject > apAbstractObject)	{
//	unsigned int nPartNo;
//
//	vector <ref_ptr<Node>>::const_iterator it = _children.begin();
//	for (it; it != _children.end(); it++)	{
//		if (*it==apAbstractObject)	{
//			nPartNo == it - _children.begin();
//			removePart(nPartNo);
//		} else {
//			return;
//		}
//	}
//}

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

vector< osg::ref_ptr<AbstractObject>> Furniture::splitObject2Children()	{
	vector< ref_ptr<AbstractObject>> aarrpChildren;

	int nI;
	ref_ptr<AbstractObject> pAbstractObject;
	for (nI=0;nI<this->getNumChildren();nI++)	{
		pAbstractObject = dynamic_cast<AbstractObject *>(getChild(nI));
		pAbstractObject->setIsTargetPick(true);
		aarrpChildren.push_back(pAbstractObject);
	}
	return aarrpChildren;
}