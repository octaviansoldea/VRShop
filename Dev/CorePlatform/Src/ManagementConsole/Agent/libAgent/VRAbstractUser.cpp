#include "VRAvatar.h"

#include <string>

#include "VRAbstractUser.h"

using namespace VR;
using namespace std;


//==============================================================================

AbstractUser::AbstractUser(Avatar *apAvatar) :
m_strUserIDName(apAvatar->getName()),
m_bIsUserAuthorized(false)	{
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
	return m_pAvatar.get();
}

//------------------------------------------------------------------------------

void AbstractUser::userActivity()	{
}

//------------------------------------------------------------------------------

void AbstractUser::findProductInShop(const ProductShopClient & aProduct) const	{
}

//------------------------------------------------------------------------------

string AbstractUser::getUserIDName() const	{
	return m_strUserIDName;
}

//------------------------------------------------------------------------------

void AbstractUser::userSignedIn()	{
	m_bIsUserAuthorized=true;
}

//------------------------------------------------------------------------------

void AbstractUser::setUserIDName(string astrUserIDName)	{
	m_strUserIDName = astrUserIDName;
}

//------------------------------------------------------------------------------

bool AbstractUser::getIsUserAuthorized() const	{
	return m_bIsUserAuthorized;
}

//------------------------------------------------------------------------------

void AbstractUser::userSignedOut()	{
	m_bIsUserAuthorized = false;
}
