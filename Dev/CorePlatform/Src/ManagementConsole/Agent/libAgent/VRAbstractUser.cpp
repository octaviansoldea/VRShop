#include "VRBasket.h"
#include "VRAvatar.h"

#include <string>

#include "VRAbstractUser.h"

using namespace VR;
using namespace std;


//==============================================================================

AbstractUser::AbstractUser(Avatar *apAvatar) :
m_strUserIDName("")	{
	m_pAvatar = apAvatar;
	m_pBasket = new Basket;
}

//------------------------------------------------------------------------------

AbstractUser::~AbstractUser()	{
	delete m_pBasket;
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
	return m_pBasket;
}

//------------------------------------------------------------------------------

void AbstractUser::userActivity()	{
}

//------------------------------------------------------------------------------

string AbstractUser::getUserIDName() const	{
	return m_strUserIDName;
}

//------------------------------------------------------------------------------

void AbstractUser::setUserIDName(string astrUserIDName)	{
	m_strUserIDName = astrUserIDName;
}
