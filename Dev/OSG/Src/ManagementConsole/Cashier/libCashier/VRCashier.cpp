#include "VRCustomer.h"
#include "VRPurchase.h"

#include "VRCashier.h"

using namespace VR;
using namespace std;

Cashier::Cashier()	{
}

//------------------------------------------------------------------------------

void Cashier::addProductToBasket(const Product * apProduct)	{
}

//------------------------------------------------------------------------------

void Cashier::removeProductFromBasket(const Product * apProduct)	{
}

//------------------------------------------------------------------------------

bool Cashier::authenticateUser(const VR::Customer * apCustomer)	{
	Customer * pCustomer = const_cast<Customer*>(apCustomer);

	bool bRes = false;

	delete pCustomer;
	return bRes;
}