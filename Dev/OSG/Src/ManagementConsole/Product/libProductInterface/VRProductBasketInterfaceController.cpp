#include "VRProductShopClient.h"
#include "VRBasket.h"

#include "VRProductBasketInterfaceController.h"

using namespace VR;

//----------------------------------------------------------------------

ProductBasketInterfaceController::ProductBasketInterfaceController(Basket * apBasket)	{
	m_pBasket = dynamic_cast<VR::Basket*>(apBasket);
}

//----------------------------------------------------------------------

ProductBasketInterfaceController::~ProductBasketInterfaceController()	{
}

//======================================================================

void ProductBasketInterfaceController::removeProduct(ProductShopClient * apProductShopClient)	{
	m_pBasket->removeProduct(apProductShopClient);
}

//----------------------------------------------------------------------

void ProductBasketInterfaceController::setQuantity(float aflQuantity)	{
	
}