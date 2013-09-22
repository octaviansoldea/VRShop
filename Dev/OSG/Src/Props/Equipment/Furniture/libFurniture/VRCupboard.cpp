#include <string>
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

string Cupboard::getSQLPrintCommand() const {
	return(string(""));
}
