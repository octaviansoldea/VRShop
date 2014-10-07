#include <iostream>

#include "VRServerClientCommands.h"

using namespace VR;

//=====================================================================

char ServerClientCommands::getOperationType(const enum OPERATION_TYPE & aenumOperationType)	{
	char chRes;

	switch (aenumOperationType)	{
	case NEW_USER_REQUEST:
		chRes = 'S';
		break;

	case AVATAR_REGISTER:
		chRes = 'R';
		break;

	case SIGN_IN_REQUEST:
		chRes = 'I';
		break;

	case SIGN_UP_REQUEST:
		chRes = 'U';
		break;

	case PRODUCT_REQUEST:
		chRes = 'P';
		break;

	case AVATAR_UPDATE:
		chRes = 'A';
		break;

	case OTHER_AVATARS_REQUEST:
		chRes = 'a';
		break;

	default:
		chRes = ' ';
		break;
	}

	return chRes;
}