#include <QString>
#include <QVariant>

#include "VRAbstractGeomShape.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRPrism.h"
#include "VRUntransformedSphere.h"


#include "VRDatabaseMgr.h"
#include "VRCupboard.h"
#include "VRContainer.h"

#include "VRFurniture.h"


using namespace osg;
using namespace std;
using namespace VR;

//=======================================================================

ref_ptr<Furniture> Furniture::getInstance(const std::string & astrClassName)	{
	Furniture * pFurniture;
	if (astrClassName == "Cupboard")
		return (new Cupboard);
	if (astrClassName == "Container")
		return (new Container);
}

//=======================================================================

FurnitureParams::FurnitureParams() : AbstractObjectParams()	{
}

//=======================================================================

Furniture::Furniture()	{
	setParentName("Furniture");
}

//-----------------------------------------------------------------------

Furniture::Furniture(const FurnitureParams & aFurnitureParams) : AbstractObject(aFurnitureParams)	{
	m_FurnitureParams = aFurnitureParams;
	setParentName("Furniture");
}

//-----------------------------------------------------------------------

void Furniture::addPart(ref_ptr < Node > apNode) {
	addChild(apNode);

	AbstractGeomShape * aAbstractGeomShape = dynamic_cast<AbstractGeomShape*>(apNode.get());
	string strCommand = aAbstractGeomShape->getSQLCommand();

	m_arrSQLCommandLines.push_back(strCommand);
}

//-----------------------------------------------------------------------

void Furniture::removePart(ref_ptr < Node > apNode) {
	removeChild(apNode);
}

//-----------------------------------------------------------------------

void Furniture::loadAllFurnitures(ref_ptr<Group> apScene, const string & astrDatabase) {
	DatabaseMgr & database = DatabaseMgr::Create(astrDatabase.c_str(), DatabaseMgr::QSQLITE);

	// get the number of equipment to be added to the scene
	QString qstrCupboardsNr = "SELECT COUNT(EquipmentItemID) FROM EquipmentItem";
	QSqlQuery qQuery(qstrCupboardsNr);

	int nCupboardsNr;
	while (qQuery.next())	{
		nCupboardsNr = qQuery.value(0).toInt();
	}

	for(int nI = 1; nI <= nCupboardsNr; nI++) {
		ref_ptr <Cupboard> cupboard = new Cupboard;
		
		QString strSQLQuery = QString("SELECT * FROM EquipmentItem WHERE EquipmentItemID = %1").arg(nI);
		string strSQLData = database.readFromDB(strSQLQuery.toStdString());
		cupboard->initFromSQLData(strSQLData);

		apScene->addChild(cupboard);
	}
}

//-----------------------------------------------------------------------

