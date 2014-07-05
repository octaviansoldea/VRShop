#include "VRAdministrator.h"

using namespace VR;

Administrator::Administrator() : AbstractUser()	{
}

//------------------------------------------------------------------------------

const char* Administrator::className() const	{
	return "Administrator";
}
