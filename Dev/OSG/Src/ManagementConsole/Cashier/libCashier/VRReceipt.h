#ifndef VR_RECEIPT_H
#define VR_RECEIPT_H

#include <vector>

#include "VRProduct.h"

class Purchase;

namespace VR	{
	class Receipt	{
	public:
		Receipt();

		void prepareReceipt(const Purchase & aPurchase);
		bool printReceipt(const Receipt & aReceipt) {return(true);}
	protected:
		std::vector <Product*> m_pvecProducts;
	};
}
#endif //VR_RECEIPT_H