#include "VRProductShopClient.h"

#include "VRBasket.h"

using namespace VR;
using namespace std;


Basket::Basket() {
}

//------------------------------------------------------------------------------

Basket::~Basket() {
	m_lstProducts.clear();

	//list<ProductShopClient*>::iterator it = m_lstProducts.begin();
	//for(it; it != m_lstProducts.end(); ++it)	{
	//	ProductShopClient * pProduct = (ProductShopClient*)(*it);
	//	delete pProduct;
	//	pProduct = 0;
	//}
}

//==============================================================================

const char* Basket::className() const {
	return "Basket";
}

//------------------------------------------------------------------------------

int Basket::count() const	{
	return m_lstProducts.size();
}

//------------------------------------------------------------------------------

ProductShopClient * Basket::getProduct(int anProductNumber)	{
	list<VR::ProductShopClient*>::iterator it = m_lstProducts.begin();
	advance(it,anProductNumber);

	return (*it);
}

//------------------------------------------------------------------------------

void Basket::addProduct(ProductShopClient * apProduct)	{
	m_lstProducts.push_back(apProduct);

	emit signalBasketChanged(count()-1,true);
}

//------------------------------------------------------------------------------

void Basket::removeProduct(ProductShopClient * apProduct)	{
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

void Basket::modifyQuantity(ProductShopClient * apProduct)	{
}

//------------------------------------------------------------------------------

float Basket::calculateBasketValue()	{
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