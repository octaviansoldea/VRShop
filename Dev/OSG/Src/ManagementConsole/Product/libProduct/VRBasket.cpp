#include "VRProductShopClient.h"

#include "VRBasket.h"

using namespace VR;
using namespace std;

#define DEBUG_PURPOSES

Basket::Basket() {
#ifdef DEBUG_PURPOSES
	int nI;
	for (nI=0;nI<10;nI++) {
		ProductShopClient * pProduct = new ProductShopClient;
		pProduct->setQuantity(nI);
		m_lstBasket.push_back(pProduct);
	}
#endif
}

//------------------------------------------------------------------------------

Basket::~Basket() {
	m_lstBasket.clear();
}

//==============================================================================

const char* Basket::className() const {
	return "Basket";
}

//------------------------------------------------------------------------------

int Basket::count() const	{
	return m_lstBasket.size();
}

//------------------------------------------------------------------------------

ProductShopClient * Basket::getProduct(int anProductNumber)	{
	list<VR::ProductShopClient*>::iterator it = m_lstBasket.begin();
	advance(it,anProductNumber);

	return (*it);
}

//------------------------------------------------------------------------------

void Basket::addProduct(ProductShopClient * apProduct)	{
	m_lstBasket.push_back(apProduct);

	emit signalBasketChanged(count()-1,true);
}

//------------------------------------------------------------------------------

void Basket::removeProduct(ProductShopClient * apProduct)	{
	list<VR::ProductShopClient*>::iterator it = m_lstBasket.begin();
	int nI=0;
	for (it; it != m_lstBasket.end();it++,nI++)	{
		if (apProduct == *it)	{
			m_lstBasket.erase(it);
			emit signalBasketChanged(nI,false);
			return;
		}
	}
}

//------------------------------------------------------------------------------

void Basket::modifyQuantity(ProductShopClient * apProduct)	{
}