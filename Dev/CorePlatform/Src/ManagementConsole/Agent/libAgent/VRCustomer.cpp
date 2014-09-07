#include "VRAvatar.h"

#include "VRCustomer.h"

using namespace VR;
using namespace osg;

//==============================================================================

Customer::Customer(ref_ptr<Avatar> apAvatar) : Visitor(apAvatar)	{

}

//------------------------------------------------------------------------------

Customer::~Customer()	{
}

//------------------------------------------------------------------------------

const char* Customer::className() const	{
	return "Customer";
}
