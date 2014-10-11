#include "VRCustomerSupportOfficer.h"

using namespace VR;

CustomerSupportOfficer::CustomerSupportOfficer(Avatar * apAvatar) : AbstractUser(apAvatar)	{
}

//------------------------------------------------------------------------------

const char* CustomerSupportOfficer::className() const	{
	return "CustomerSupportOfficer";
}

//------------------------------------------------------------------------------

CustomerSupportOfficer::~CustomerSupportOfficer() {
}