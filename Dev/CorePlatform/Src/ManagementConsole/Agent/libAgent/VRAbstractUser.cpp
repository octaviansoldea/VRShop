#include "VRAvatar.h"

#include <string>

#include "VRAbstractUser.h"

using namespace VR;
using namespace std;


//==============================================================================

AbstractUser::AbstractUser(Avatar *apAvatar) :
m_strUserIDName(""),
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

string AbstractUser::getUserIDName() const	{
	return m_strUserIDName;
}

//------------------------------------------------------------------------------

void AbstractUser::setUserIDName(string astrUserIDName)	{
	m_strUserIDName = astrUserIDName;
	m_bIsUserAuthorized=true;
}

//------------------------------------------------------------------------------

bool AbstractUser::getIsUserAuthorized() const	{
	return m_bIsUserAuthorized;
}