#ifndef VR_CUSTOMER_H
#define VR_CUSTOMER_H

#include "VRVisitor.h"
#include "VRUserAccount.h"

namespace VR	{
	class Avatar;

	class Customer : public Visitor {
	public:
		Customer();
		~Customer();

		virtual const char* className() const;

		virtual bool trySignIn();

	protected:
		UserAccount m_UserAccount;
	};
}
#endif //VR_CUSTOMER_H