#include "VRProductShopClient.h"

#include "VRCashierManagerClient.h"

#include "VRBasketClient.h"

#include "VRVisitor.h"

using namespace VR;
using namespace std;

//==============================================================================

Visitor::Visitor(Avatar * apAvatar) : AbstractUser((Avatar*)apAvatar) {
	m_pCashierManagerClient = new CashierManagerClient;
}

//------------------------------------------------------------------------------

Visitor::~Visitor()	{
	delete m_pCashierManagerClient;
}

//------------------------------------------------------------------------------

const char* Visitor::className() const	{
	return "Visitor";
}

//------------------------------------------------------------------------------

bool Visitor::addProduct2Basket(ProductShopClient * apProduct)	{
	ProductShopClient * pProduct = apProduct;
	m_pBasket->addProduct(pProduct);

	return true;
}

//------------------------------------------------------------------------------

bool Visitor::removeProductFromBasket(ProductShopClient * apProduct)	{
	m_pBasket->removeProduct(apProduct);
	return true;
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

bool Visitor::approachCashier()	{
	return true;
}

//------------------------------------------------------------------------------

void Visitor::payRequest() {
	CashierManagerClient::CashierManagerClientParams cmcp;
	cmcp.m_strVisitorName = getUserIDName();
	cmcp.m_strBasketProdQty = getBasket()->getBasketIDQuantity2String();
	cmcp.m_strProductName = "";

	m_pCashierManagerClient->requestToServer(ServerClientCommands::PURCHASE_REQUEST,&cmcp);
}

//------------------------------------------------------------------------------

bool Visitor::tryPay()	{
	return false;
};