#include "VRProduct.h"
#include "VRAvatar.h"

#include <string>

#include "VRAbstractUser.h"

using namespace VR;
using namespace std;


//==============================================================================

AbstractUser::AbstractUser()	{
}

//------------------------------------------------------------------------------

AbstractUser::~AbstractUser()	{
}

//------------------------------------------------------------------------------

const char* AbstractUser::className() const	{
	return "AbstractUser";
}

//------------------------------------------------------------------------------
