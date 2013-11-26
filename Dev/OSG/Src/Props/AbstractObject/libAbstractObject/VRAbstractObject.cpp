#include "VRAbstractObject.h"

using namespace VR;
using namespace std;

string AbstractObject::m_strSQLFormat = "";

//==============================================================

string VR::AbstractObject::getSQLFormat() const {
	return(m_strSQLFormat);
}
