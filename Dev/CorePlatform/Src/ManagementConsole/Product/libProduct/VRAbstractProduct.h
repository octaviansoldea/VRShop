#ifndef VR_ABSTRACT_PRODUCT_H
#define VR_ABSTRACT_PRODUCT_H

#include <string>

namespace VR	{
	struct AbstractProductParams	{

		AbstractProductParams();
	};

	class AbstractProduct	{
	public:
		AbstractProduct();
		virtual ~AbstractProduct() = 0;

		virtual const char* className() const;
		virtual void initFromSQLData(std::string & astrSQLData) = 0;

	private:
		AbstractProductParams m_AbstractProductParams;
	};
}
#endif //VR_ABSTRACT_PRODUCT_H