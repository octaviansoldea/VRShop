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

void Cupboard::setPos(const CupboardParams & aCupboardParams) {

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
}

//-----------------------------------------------------------------------

//void Cupboard::removePart(osg::Object * apObject) {
//}

//-----------------------------------------------------------------------

QString Cupboard::getSQLPrintCommand() {
	QString strSQLCommand;

	int nNumChildren = getNumChildren();
	std::cout << nNumChildren << std::endl;

	int nI;
	for (nI=0;nI<nNumChildren;nI++)	{
		AbstractGeomShape * pAbstractGeomShape = dynamic_cast<AbstractGeomShape*>(this->getChild(nI));
		strSQLCommand += QString(pAbstractGeomShape->getSQLCommand().c_str());
	}



	return(strSQLCommand);
}
