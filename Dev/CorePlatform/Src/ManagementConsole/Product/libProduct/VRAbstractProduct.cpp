#include "VRAbstractProduct.h"

using namespace VR;

AbstractProductParams::AbstractProductParams()	{
}

//==============================================================================

AbstractProduct::AbstractProduct()	{
}

//------------------------------------------------------------------------------

AbstractProduct::~AbstractProduct()	{
}

//------------------------------------------------------------------------------

const char* AbstractProduct::className() const	{
	return "Product";
}

//-----------------------------------------------------------------------