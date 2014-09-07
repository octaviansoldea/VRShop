#include "VRCustomerSupportOfficer.h"

using namespace VR;
using namespace osg;

CustomerSupportOfficer::CustomerSupportOfficer(Avatar * apAvatar) : AbstractUser(apAvatar)	{
}

//------------------------------------------------------------------------------

const char* CustomerSupportOfficer::className() const	{
	return "CustomerSupportOfficer";
}

//------------------------------------------------------------------------------

CustomerSupportOfficer::~CustomerSupportOfficer() {
}