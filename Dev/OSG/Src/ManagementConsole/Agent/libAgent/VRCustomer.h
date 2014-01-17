#ifndef VR_CUSTOMER_H
#define VR_CUSTOMER_H

#include "VRAbstractUser.h"
#include "VRUserAccount.h"

namespace VR	{

	class Customer : public AbstractUser {
	public:
		Customer();

		virtual void trySignIn();

	protected:
		UserAccount m_UserAccount;
	};
}
#endif //VR_CUSTOMER_H