#ifndef VR_CLIENT_H
#define VR_CLIENT_H

#include "VRAbstractUser.h"

namespace VR {
	class Client : public AbstractUser {
	public:
		Client();

		void pay();
	};
}
#endif //VR_CLIENT_H