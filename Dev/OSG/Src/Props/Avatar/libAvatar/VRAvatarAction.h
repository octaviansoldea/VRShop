#ifndef VR_AVATAR_ACTION_H
#define VR_AVATAR_ACTION_H

#include <osg/Node>
#include <osg/NodeVisitor>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/AnimationManagerBase>

namespace VR {
	//struct AnimationManager : public osg::NodeVisitor	{
	//	AnimationManager();

	//	virtual void apply(osg::Node& node);

	//	osg::ref_ptr<osgAnimation::BasicAnimationManager> m_AnimationManager;
	//};


	class AvatarAction	{
	public:
		AvatarAction();

		enum ActionType {};
	};
}
#endif //VR_AVATAR_ACTION_H