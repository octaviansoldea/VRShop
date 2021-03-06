#ifndef VR_CUSTOMER_SUPPORT_OFFICER_H
#define VR_CUSTOMER_SUPPORT_OFFICER_H

#include "VRAbstractUser.h"

namespace VR {
	class CustomerSupportOfficer : public AbstractUser {
	public:
		CustomerSupportOfficer(Avatar * apAvatar = 0);
		virtual ~CustomerSupportOfficer();
		virtual const char* className() const;
	};
}
#endif //VR_CUSTOMER_SUPPORT_OFFICER_H