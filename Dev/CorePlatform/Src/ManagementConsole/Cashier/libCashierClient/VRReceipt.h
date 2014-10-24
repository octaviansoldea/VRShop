#ifndef VR_RECEIPT_H
#define VR_RECEIPT_H

#include <vector>

namespace VR	{
	class Transaction;

	class Receipt	{
	public:
		Receipt(const Transaction * apTransaction);

		void prepareReceipt(const Transaction & aTransaction);
		bool printReceipt(const Receipt & aReceipt) {return(true);}
	};
}
#endif //VR_RECEIPT_H