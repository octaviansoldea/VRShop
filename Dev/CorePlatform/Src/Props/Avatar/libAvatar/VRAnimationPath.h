#ifndef VR_ANIMATION_PATH_H
#define VR_ANIMATION_PATH_H

#include <osg/AnimationPath>
#include <osg/Matrix>

namespace VR {
	class AnimationPath : public osg::AnimationPath	{
	public:
		AnimationPath();
		AnimationPath(const AnimationPath& ap, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		VR::AnimationPath * createAnimationPath(const osg::Matrix & amtrxOldAvatar, const osg::Matrix & amtrxNewAvatar);

		enum Animationtype {LINEAR, POLINOMIAL};

		void startAnimation(const osg::Vec3d & avec3dStartingPoint, const osg::Vec3d & avec3dEndPoint);
		void stopAnimation();

		void setAnimationType();
	};
}
#endif //VR_ANIMATION_PATH_H