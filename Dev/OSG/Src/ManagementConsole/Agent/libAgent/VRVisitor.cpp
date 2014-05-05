#include "VRAvatar.h"

#include "VRVisitor.h"

using namespace VR;
using namespace std;

//==============================================================================

Visitor::Visitor()	{
}

//------------------------------------------------------------------------------

const char* Visitor::className() const	{
	return "Visitor";
}

vector<Product> Visitor::getBasket() const	{
	return m_Basket;
}
