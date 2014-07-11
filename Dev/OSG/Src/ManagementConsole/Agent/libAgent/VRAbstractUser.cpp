#include "VRBasket.h"
#include "VRAvatar.h"

#include <string>

#include "VRAbstractUser.h"

using namespace VR;
using namespace std;


//==============================================================================

AbstractUser::AbstractUser(Avatar *apAvatar)	{
	m_pAvatar = apAvatar;
}

//------------------------------------------------------------------------------

AbstractUser::~AbstractUser()	{

}

//------------------------------------------------------------------------------

const char* AbstractUser::className() const	{
	return "AbstractUser";
}

//------------------------------------------------------------------------------

Avatar * AbstractUser::getAvatar()	{
	return m_pAvatar;
}

//------------------------------------------------------------------------------

Basket * AbstractUser::getBasket()	{
	return &m_Basket;
}

//------------------------------------------------------------------------------

void AbstractUser::userActivity()	{
}