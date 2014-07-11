#include "VRVisitor.h"

using namespace VR;
using namespace std;

//==============================================================================

Visitor::Visitor(Avatar * apAvatar) : AbstractUser(apAvatar) {
}

//------------------------------------------------------------------------------

Visitor::~Visitor()	{
}

//------------------------------------------------------------------------------

const char* Visitor::className() const	{
	return "Visitor";
}

//------------------------------------------------------------------------------

bool Visitor::trySignIn()	{
	return true;
}

//------------------------------------------------------------------------------

bool Visitor::openAccount()	{
	return false;
}

//------------------------------------------------------------------------------

bool Visitor::addProduct2Basket(const Product & aProduct) const	{
	return false;
}

//------------------------------------------------------------------------------

bool Visitor::removeProductFromBasket(const Product & aProduct) const	{
	return false;
}

//------------------------------------------------------------------------------

void Visitor::listProductsInBasket() const	{
}

//------------------------------------------------------------------------------

void Visitor::inspectProduct(const Product & aProduct) const	{
}

//------------------------------------------------------------------------------

void Visitor::listProductComplements(std::list < Product > & alstProducts, const Product * apProduct)	{
}

//------------------------------------------------------------------------------

void Visitor::listProductSubstitutes(std::list < Product > & alstProducts, const Product * apProduct)	{
}

//------------------------------------------------------------------------------

void Visitor::requestHelp()	{
}
