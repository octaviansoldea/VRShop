#include "VRProductShopClient.h"

#include "VRBasketClient.h"

#include "VRVisitor.h"

using namespace VR;
using namespace std;

//==============================================================================

Visitor::Visitor(Avatar * apAvatar) : AbstractUser((Avatar*)apAvatar) {
	m_pBasket = new BasketClient;
}

//------------------------------------------------------------------------------

Visitor::~Visitor()	{
	delete m_pBasket;
}

//------------------------------------------------------------------------------

const char* Visitor::className() const	{
	return "Visitor";
}

//------------------------------------------------------------------------------

bool Visitor::addProduct2Basket(ProductShopClient * apProduct)	{
	int nSize = m_pBasket->count();

	ProductShopClient * pProduct = apProduct;
	m_pBasket->addProduct(pProduct);

	bool bRes = (m_pBasket->count() == nSize+1) ? true : false;
	
	return bRes;
}

//------------------------------------------------------------------------------

bool Visitor::removeProductFromBasket(ProductShopClient * apProduct)	{
	m_pBasket->removeProduct(apProduct);
	return true;
}

//------------------------------------------------------------------------------

BasketClient * Visitor::getBasket()	{
	return m_pBasket;
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
	//CashierManagerClient::CashierManagerClientParams cmcp;
	//cmcp.m_strVisitorName = getUserIDName();
	//cmcp.m_strBasketProdQty = getBasket()->getBasketIDQuantity2String();
	//cmcp.m_strProductName = "";

	//m_pCashierManagerClient->requestToServer(ServerClientCommands::PURCHASE_REQUEST,&cmcp);
}

//------------------------------------------------------------------------------

bool Visitor::tryPay()	{
	return false;
};