#ifndef VR_PRODUCT_BASE_H
#define VR_PRODUCT_BASE_H

#include <string>
#include "VRAbstractObject.h"

namespace VR	{
	struct AbstractProductParams	{

		AbstractProductParams();
	};

	class AbstractProduct	{
	public:
		AbstractProduct();
		virtual ~AbstractProduct() = 0;

		const char* className() const;
		virtual void initFromSQLData(std::string & astrSQLData) = 0;

	private:
		AbstractProductParams m_AbstractProductParams;
	};
}
#endif //VR_PRODUCT_BASE_H