#include "BasicStringDefinitions.h"

#include <iostream>

#include "VRAbstractObjectFactory.h"
#include "VRAbstractGeomShape.h"

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

void Furniture::removePart(ref_ptr < AbstractObject > aAbstractObject)	{
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
	//DatabaseMgr & database = DatabaseMgr::Create(astrDatabase.c_str(), DatabaseMgr::QSQLITE);

	//QString qstrFurniture = "SELECT EquipmentItemName FROM EquipmentItem JOIN Equipment ON EquipmentName = 'Furniture'";
	//QSqlQuery qQuery(qstrFurniture);

	//vector<string> arrstrEquipmentItems;
	//while (qQuery.next())	{
	//	arrstrEquipmentItems.push_back(qQuery.value(0).toString().toStdString());
	//}

	//vector<string>::iterator it;
	//ref_ptr<Furniture> pFurniture;
	//for(it = arrstrEquipmentItems.begin(); it != arrstrEquipmentItems.end(); it++) {
	//	pFurniture = static_cast<Furniture*>(Furniture::createInstance(*it).get());
	//	
	//	string strSQLQuery = "SELECT * FROM EquipmentItem WHERE EquipmentItemName = '" + *it + "'";
	//	string strSQLData = database.readFromDB(strSQLQuery);
	//	pFurniture->initFromSQLData(strSQLData);

	//	apScene->addChild(pFurniture);
	//}
}

//-----------------------------------------------------------------------

void Furniture::initFromSQLData(vector<string> & avecstrSQLData)	{
//**********************************************
//	HIERARCHY (how you get data inside)
//		OBJECT1				Layer: 0
//			|--PRIMITIVE1	Layer: 1
//			|--PRIMITIVE2	Layer: 1
//*******************************************/

	const int nNoOfElements = avecstrSQLData.size();
	int nPos;	//Position of the indent

	vector<string> vecstrSqlDataLine;
	vector<string>::iterator it = avecstrSQLData.begin();
	for (it; it != avecstrSQLData.end(); it++)	{
		nPos = 0;

		//Find the position of the first character & clear empty spaces
		nPos = it->find_first_not_of(" ");
		const int nFindPos = it->find_first_of(";");	//This one deletes ID number
		it->erase(0,nFindPos+1);

		vecstrSqlDataLine = splitString(*it,";");

		//Layer determines Parent/Child relations
		nPos = nPos/2;	//Divided with 2 because 2 is the layer indent

		string & strClass = vecstrSqlDataLine[0];
		string & strObject = vecstrSqlDataLine[1];

		ref_ptr<AbstractObject> pAOChild = 0;

		if (nPos == 0)	{
			string & strMtrx = vecstrSqlDataLine[2];

			vector <string> arrstrFurnitureParams = splitString(strMtrx,"_");

			FurnitureParams fP;
			fP.m_flPosX = stof(arrstrFurnitureParams[0]);
			fP.m_flPosY = stof(arrstrFurnitureParams[1]);
			fP.m_flPosZ = stof(arrstrFurnitureParams[2]);

			fP.m_flLenX = stof(arrstrFurnitureParams[3]);
			fP.m_flLenY = stof(arrstrFurnitureParams[4]);
			fP.m_flLenZ = stof(arrstrFurnitureParams[5]);

			fP.m_flAngleYZ = stof(arrstrFurnitureParams[6]);
			fP.m_flAngleXZ = stof(arrstrFurnitureParams[7]);
			fP.m_flAngleXY = stof(arrstrFurnitureParams[8]);

			setParams(fP);
			Matrix furnitureMatrix = calculateMatrix();

			setMatrix(furnitureMatrix);
			setName(strObject);
			setIsTargetPick(true);

		} else {
			pAOChild = AbstractObjectFactory::createAbstractObject(strClass);
			pAOChild->initFromSQLData(vecstrSqlDataLine);

			pAOChild->setName(strObject);

			addPart(pAOChild);
		}
	}
}

//-----------------------------------------------------------------------

string Furniture::prepareRowData(const string & astrParentName)	{
	FurnitureParams furnitureParams;
	getParams(furnitureParams);

	string strFurnitureParams;
	strFurnitureParams = to_string((long double)furnitureParams.m_flPosX) + "_";
	strFurnitureParams += to_string((long double)furnitureParams.m_flPosY) + "_";
	strFurnitureParams += to_string((long double)furnitureParams.m_flPosZ) + "_";

	strFurnitureParams += to_string((long double)furnitureParams.m_flLenX) + "_";
	strFurnitureParams += to_string((long double)furnitureParams.m_flLenY) + "_";
	strFurnitureParams += to_string((long double)furnitureParams.m_flLenZ) + "_";

	strFurnitureParams += to_string((long double)furnitureParams.m_flAngleYZ) + "_";
	strFurnitureParams += to_string((long double)furnitureParams.m_flAngleXZ) + "_";
	strFurnitureParams += to_string((long double)furnitureParams.m_flAngleXY) + ";";

	strFurnitureParams += astrParentName;

	return strFurnitureParams;
}

//-----------------------------------------------------------------------

void Furniture::setTexture(const std::string & astrFileName)	{
	int nI;
	ref_ptr<AbstractObject> pAbstractObject = 0;
	for (nI=0; nI<this->getNumChildren();nI++)	{
		pAbstractObject = dynamic_cast<VR::AbstractObject*>(getChild(nI));
		pAbstractObject->setTexture(astrFileName);
	}
}

//-----------------------------------------------------------------------

void Furniture::setColor(const std::vector < float > & aarrflColor)	{
	int nI;
	ref_ptr<AbstractObject> pAbstractObject = 0;
	for (nI=0; nI<this->getNumChildren();nI++)	{
		pAbstractObject = dynamic_cast<VR::AbstractObject*>(getChild(nI));
		pAbstractObject->setColor(aarrflColor);
	}
}

//-----------------------------------------------------------------------

void Furniture::setParams(const AbstractObjectParams & aAbstractObjectParams)	{
	AbstractObject::setParams(aAbstractObjectParams);
}

//-----------------------------------------------------------------------

void Furniture::getParams(FurnitureParams & aFurnitureParams) const	{
	AbstractObject::getParams(aFurnitureParams);
}

//-----------------------------------------------------------------------
