#include "VRAdministrator.h"

using namespace VR;

Administrator::Administrator(Avatar * apAvatar) : AbstractUser(apAvatar)	{
}

//------------------------------------------------------------------------------

const char* Administrator::className() const	{
	return "Administrator";
}

//------------------------------------------------------------------------------

Administrator::~Administrator() {
}
