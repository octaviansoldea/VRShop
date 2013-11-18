#include <string>
#include <iostream>

#include "VRAbstractGeomShape.h"

#include "VRCupboard.h"

using namespace std;
using namespace osg;
using namespace VR;

CupboardParams::CupboardParams() :
m_flPosX(0.0), m_flPosY(0.0), m_flPosZ(0.0) {
}

//-----------------------------------------------------------------------

Cupboard::Cupboard()	{
}

//-----------------------------------------------------------------------

void Cupboard::init(const CupboardParams & aCupboardParams)	{

	Matrix matrix;
	matrix.set(1,							0,							0,							0,
			   0,							1,							0,							0,
			   0,							0,							1,							0,
			   aCupboardParams.m_flPosX,	aCupboardParams.m_flPosY,	aCupboardParams.m_flPosZ,	1);

	setMatrix(matrix);

}

//-----------------------------------------------------------------------

void Cupboard::addPart(ref_ptr < Node > apNode) {
	addChild(apNode);

	AbstractGeomShape * aAbstractGeomShape = dynamic_cast<AbstractGeomShape*>(apNode.get());
	string strCommand = aAbstractGeomShape->getSQLCommand();

	m_arrSQLCommandLines.push_back(strCommand);
}

//-----------------------------------------------------------------------

void Cupboard::removePart(ref_ptr < Node > apNode) {
	removeChild(apNode);
}

//-----------------------------------------------------------------------

string Cupboard::getSQLPrintCommand() {
	string strSQLCommand = "INSERT INTO EquipmentItem (EquipmentItemName, EquipmentID) "
		"VALUES ('Cupboard', (SELECT EquipmentID FROM Equipment WHERE EquipmentName = 'Furniture'))_";
	int nNumParts = m_arrSQLCommandLines.size();

	int nI;
	for (nI=0;nI<nNumParts-1;nI++)	{
		strSQLCommand += m_arrSQLCommandLines[nI] + "_";
	}
	strSQLCommand += m_arrSQLCommandLines[nNumParts-1];

	return(strSQLCommand);
}
