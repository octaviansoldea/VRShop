#include "VRBasket.h"
#include "VRAvatar.h"

#include <string>

#include "VRAbstractUser.h"

using namespace VR;
using namespace std;


//==============================================================================

AbstractUser::AbstractUser() :
m_pShoppingPlace_GUI(0)	{

	m_pAvatar = new Avatar();
}

//------------------------------------------------------------------------------

AbstractUser::~AbstractUser()	{
	if (m_pShoppingPlace_GUI)
		delete m_pShoppingPlace_GUI;

	delete m_pAvatar;
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