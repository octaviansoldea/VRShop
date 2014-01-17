#ifndef VR_VISITOR_H
#define VR_VISITOR_H

#include "VRAbstractUser.h"

/*	
	Visitor is a user of the platform who hasn't signed-in yet. 
	The visitor can use the platform but has to sign-in should he make a purchase.
*/

namespace VR	{
	struct VisitorParams	{
		std::string m_strVisitorIP;
	};

	class Visitor : public AbstractUser {
	public:
		Visitor();

		virtual void trySignIn();
	};
}
#endif //VR_VISITOR_H