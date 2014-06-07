#include "VRAvatar.h"

#include "VRAnimatedAvatar.h"

using namespace VR;

//==============================================================================

AnimatedAvatar::AnimatedAvatar(QObject * parent): Avatar(parent)	{
}

//------------------------------------------------------------------------------

AnimatedAvatar::~AnimatedAvatar()	{
}

//==============================================================================

const char* AnimatedAvatar::className() const	{
	return "AnimatedAvatar";
}