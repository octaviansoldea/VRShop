#include "VRProductShopClient.h"

#include "VRVisitor.h"

using namespace VR;
using namespace std;

//==============================================================================

Visitor::Visitor(Avatar * apAvatar) : AbstractUser((Avatar*)apAvatar) {
}

//------------------------------------------------------------------------------

Visitor::~Visitor()	{
}

//------------------------------------------------------------------------------

const char* Visitor::className() const	{
	return "Visitor";
}

//------------------------------------------------------------------------------

bool Visitor::addProduct2Basket(const ProductShopClient & aProduct) const	{
	return false;
}

//------------------------------------------------------------------------------

bool Visitor::removeProductFromBasket(const ProductShopClient & aProduct) const	{
	return false;
}

//------------------------------------------------------------------------------

void Visitor::listProductsInBasket() const	{
}

//------------------------------------------------------------------------------

void Visitor::inspectProduct(const ProductShopClient & aProduct) const	{
}

//------------------------------------------------------------------------------

void Visitor::listProductComplements(std::list < ProductShopClient > & alstProducts, const ProductShopClient * apProduct)	{
}

//------------------------------------------------------------------------------

void Visitor::listProductSubstitutes(std::list < ProductShopClient > & alstProducts, const ProductShopClient * apProduct)	{
}

//------------------------------------------------------------------------------

void Visitor::requestHelp()	{
}

//------------------------------------------------------------------------------

void Visitor::pay() {
}

//------------------------------------------------------------------------------

bool Visitor::tryPay()	{
	return false;
};