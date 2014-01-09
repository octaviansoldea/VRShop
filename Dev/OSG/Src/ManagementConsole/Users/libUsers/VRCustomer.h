#ifndef VR_CUSTOMER_H
#define VR_CUSTOMER_H

#include "VRPlatformUserBase.h"

namespace VR	{
	struct CustomerParams : public PlatformUserBaseParams	{
		CustomerParams();
	};

	class Customer : public PlatformUserBase	{
	public:
		Customer();

	private:
		int m_nNumberOfCustomers;
	};
}
#endif //VR_CUSTOMER_H