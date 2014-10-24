#include "BasicStringDefinitions.h"

#include "VRProductShopClient.h"

#include "VRBasketClient.h"

using namespace VR;
using namespace std;


BasketClient::BasketClient() {
}

//------------------------------------------------------------------------------

BasketClient::~BasketClient() {
	m_lstProducts.clear();

	list<ProductShopClient*>::iterator it = m_lstProducts.begin();
	for(it; it != m_lstProducts.end(); ++it)	{
		ProductShopClient * pProduct = (ProductShopClient*)(*it);
		delete pProduct;
		pProduct = 0;
	}
}

//==============================================================================

const char* BasketClient::className() const {
	return "BasketClient";
}

//------------------------------------------------------------------------------

int BasketClient::count() const	{
	return m_lstProducts.size();
}

//------------------------------------------------------------------------------

ProductShopClient * BasketClient::getProduct(int anProductNumber)	{
	if (anProductNumber > count()-1 || anProductNumber < 0)	{
		return 0;
	}

	list<VR::ProductShopClient*>::iterator it = m_lstProducts.begin();
	advance(it,anProductNumber);

	return (*it);
}

//------------------------------------------------------------------------------

void BasketClient::addProduct(ProductShopClient * apProduct)	{
	m_lstProducts.push_back(apProduct);

	int nSize = count()-1;

	emit signalBasketChanged(nSize,true);
}

//------------------------------------------------------------------------------

void BasketClient::removeProduct(ProductShopClient * apProduct)	{
	list<VR::ProductShopClient*>::iterator it = m_lstProducts.begin();
	int nI=0;
	for (it; it != m_lstProducts.end();it++,nI++)	{
		if (apProduct == *it)	{
			//delete *it;
			//*it = 0;
			m_lstProducts.erase(it);
			emit signalBasketChanged(nI,false);
			return;
		}
	}
}

//------------------------------------------------------------------------------

void BasketClient::modifyQuantity(ProductShopClient * apProduct)	{
}

//------------------------------------------------------------------------------

float BasketClient::calculateBasketValue()	{
	float flBasketValue=0;

	list<VR::ProductShopClient*>::iterator it = m_lstProducts.begin();
	for(it; it != m_lstProducts.end(); ++it)	{
		ProductShopClient * pProduct = (ProductShopClient*)(*it);
		flBasketValue += (pProduct->getQuantity() * pProduct->getPrice());
	}

	//Round final value to two decimals
	flBasketValue = floor(flBasketValue * 100.0f + 0.5f) / 100.0f;

	return flBasketValue;
}

//------------------------------------------------------------------------------

list<pair<long,float>> BasketClient::getBasketProductsAndQuantities()	{
	list<pair<long,float>> lstpairBasketProductsAndQuantities;

	int nBasketSize = count();
	int nI;
	ProductShopClient * pProduct = 0;
	for (nI=0;nI<nBasketSize;nI++)	{
		pProduct = getProduct(nI);
		lstpairBasketProductsAndQuantities.push_back(make_pair(pProduct->getProductID(),pProduct->getQuantity()));
	}

	return lstpairBasketProductsAndQuantities;
}

//------------------------------------------------------------------------------

string BasketClient::getBasketIDQuantity2String()	{
	string strBasketProductsAndQuantities = "";

	int nBasketSize = count();
	int nI;
	ProductShopClient * pProduct = 0;
	for (nI=0;nI<nBasketSize;nI++)	{
		pProduct = getProduct(nI);
		strBasketProductsAndQuantities += (tostr(pProduct->getProductID()) + ";" + tostr(pProduct->getQuantity()) + ";");
	}
	strBasketProductsAndQuantities.pop_back();

	return strBasketProductsAndQuantities;
}

//------------------------------------------------------------------------------
