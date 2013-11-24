#include "VRAbstractObject.h"

using namespace VR;
using namespace std;

string AbstractObject::m_strSQLFormat = "";

//==============================================================

AbstractObjectParams::AbstractObjectParams()	{
}

//==============================================================

string VR::AbstractObject::getSQLFormat() const {
	return(m_strSQLFormat);
}
