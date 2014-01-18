#include <string>

#include "VRClient.h"

using namespace VR;
using namespace std;

Client::Client()	{
}

list<Product> Client::getBasket() const	{
	return m_Basket;
}
