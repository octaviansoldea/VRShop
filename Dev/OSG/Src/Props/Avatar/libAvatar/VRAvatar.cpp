#include <osgDB/ReadFile>

#include "VRAvatar.h"

using namespace VR;
using namespace osg;

//==============================================================================

Avatar::Avatar(QObject * parent): QObject(parent)	{
	ref_ptr<Node> pAvatar = dynamic_cast<Group*>(osgDB::readNodeFile("C:/Matej/test_1.osg"));

	addChild(pAvatar);
}

//------------------------------------------------------------------------------

Avatar::~Avatar()	{
}

//==============================================================================

const char* Avatar::className() const	{
	return "Avatar";
}