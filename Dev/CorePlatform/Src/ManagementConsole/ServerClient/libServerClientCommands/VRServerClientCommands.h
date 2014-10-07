#ifndef VR_SERVER_CLIENT_COMMANDS_H
#define VR_SERVER_CLIENT_COMMANDS_H

namespace VR	{
	class ServerClientCommands	{
	public:

		enum OPERATION_TYPE	{
			NEW_USER_REQUEST = 0,
			AVATAR_REGISTER,
			AVATAR_UPDATE,
			SIGN_IN_REQUEST,
			SIGN_UP_REQUEST,
			OTHER_AVATARS_REQUEST,
			PRODUCT_REQUEST
		};

		static char getOperationType(const enum OPERATION_TYPE & aenumOperationType);

	};		
}
#endif //VR_SERVER_CLIENT_COMMANDS_H