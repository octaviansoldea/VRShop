#ifndef VR_CUSTOMER_H
#define VR_CUSTOMER_H

#include "VRClient.h"
#include "VRUserAccount.h"

namespace VR	{

	class Customer : public Client {
	public:
		Customer();

		virtual void trySignIn();

	protected:
		UserAccount m_UserAccount;
	};
}
#endif //VR_CUSTOMER_H