#include "VRCustomer.h"
#include "VRBasket.h"

#include "VRCashier.h"

using namespace VR;
using namespace std;

Cashier::Cashier() : m_pBasket(0), m_pCashierScreen(0)	{
}

//------------------------------------------------------------------------------

Cashier::~Cashier()	{
	if (m_pCashierScreen != 0)
		delete m_pCashierScreen;
}

//=============================================================================

void Cashier::init(Basket * apBasket)	{
	m_pBasket = apBasket;

	m_pCashierScreen = new CashierScreen(m_pBasket);
	m_pCashierScreen->setCashierScreen(true);
}

//------------------------------------------------------------------------------