#ifndef VR_SERVER_CLIENT_COMMANDS_H
#define VR_SERVER_CLIENT_COMMANDS_H

namespace VR	{
	class ServerClientCommands	{
	public:

		enum OperationType	{
			NEW_USER_REQUEST = 0,
			AVATAR_REGISTER,
			AVATAR_UPDATE,
			OTHER_AVATARS_REQUEST,
			CLEAN_AVATARS_REQUEST,
			SIGN_IN_REQUEST,
			SIGN_UP_REQUEST,
			SIGN_OUT_REQUEST,
			MODIFY_USER_ACCOUNT_REQUEST,
			PRODUCT_REQUEST,
			PRODUCT_TO_BASKET_REQUEST,
			REMOVE_PRODUCT_REQUEST,
			REMOVE_FROM_CASHIER_REQUEST,
			MODIFY_PRODUCT_REQUEST,
			PRODUCT_INFO_REQUEST,
			PURCHASE_REQUEST,
			USER_CONFIRMS_PURCHASE
		};

		enum OperationResult	{
			FAILED = 0,
			PASSED,
			AUTHENTICATION_FAILED
		};
	};
}
#endif //VR_SERVER_CLIENT_COMMANDS_H