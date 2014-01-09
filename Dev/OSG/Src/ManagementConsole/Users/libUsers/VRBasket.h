#ifndef VR_BASKET_H
#define VR_BASKET_H

#include <vector>

#include "VRProduct.h"

namespace VR	{
	class Basket	{
	public:
		Basket();

	protected:
		std::vector <Product*> m_pvecProducts;
	};
}
#endif //VR_BASKET_H