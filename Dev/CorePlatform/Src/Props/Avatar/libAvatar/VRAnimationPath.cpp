#include <iostream>

#include "VRAnimationPath.h"

using namespace VR;
using namespace osg;

//==============================================================================

VR::AnimationPath::AnimationPath() : osg::AnimationPath()	{
}

//------------------------------------------------------------------------------

VR::AnimationPath::AnimationPath(const AnimationPath& ap, const CopyOp& copyop) :
osg::AnimationPath(ap,copyop)	{
}

//==============================================================================

VR::AnimationPath * VR::AnimationPath::createAnimationPath(const Matrix & amtrxOldAvatar, const Matrix & amtrxNewAvatar)	{
	// Create animation path
	Vec3d vec3dCurrentPoint = Vec3d(amtrxOldAvatar(3,0),amtrxOldAvatar(3,1),amtrxOldAvatar(3,2));
	Vec3d vec3dNewPoint = Vec3d(amtrxNewAvatar(3,0),amtrxNewAvatar(3,1),amtrxNewAvatar(3,2));

	// Define control points
	VR::AnimationPath::ControlPoint CP0(vec3dCurrentPoint);
	VR::AnimationPath::ControlPoint CP1(vec3dNewPoint);

	insert( 0.f, CP0 ); // time, point
	insert( 10.f, CP1 );

	setLoopMode(VR::AnimationPath::LoopMode::NO_LOOPING);

	return this;
}

//------------------------------------------------------------------------------
