#include "VRAbstractObject.h"

using namespace VR;
using namespace std;

string AbstractObject::m_strSQLFormat = "";

//==============================================================

AbstractObject::~AbstractObject() {
}

string AbstractObject::getSQLFormat() const {
	return(m_strSQLFormat);
}

