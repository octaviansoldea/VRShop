#include <osgDB/ReadFile>
#include <string>
#include <cmath>
#include "BasicDefinitions.h"

#include "VRKeyboardMouseManipulatorShopClient.h"
#include <osg/ComputeBoundsVisitor>
#include <osg/CoordinateSystemNode>

#include "AnimtkViewer.h"

#include "VRAvatar.h"

using namespace VR;
using namespace osg;
using namespace std;

//==============================================================================

Avatar::Avatar(std::string & astrAvatarFile, QObject * parent): QObject(parent)	{
	ref_ptr<Node> pAvatar = dynamic_cast<Group*>(osgDB::readNodeFile(astrAvatarFile));

	addChild(pAvatar);
	m_pKeyboardMouseManipulatorShopClient = 0;
}

//-----------------------------------------------------------------------------

Avatar::Avatar(std::string & astrAvatarFile, 
	KeyboardMouseManipulatorShopClient * apKeyboardMouseManipulatorShopClient, 
	QObject * parent) 
: QObject(parent)	{

	m_pKeyboardMouseManipulatorShopClient = apKeyboardMouseManipulatorShopClient;
	m_pAvatar = dynamic_cast<Group*>(osgDB::readNodeFile(astrAvatarFile));
	addChild(m_pAvatar);

	connect(m_pKeyboardMouseManipulatorShopClient, 
		SIGNAL(signalCameraPositionOrHeadingDirectionChanged()),
		this,SLOT(slotUpdatePosition()));

	m_pAnimationPath = new osg::AnimationPath();
	m_pAnimationPath->setLoopMode(osg::AnimationPath::LoopMode::LOOP);
	osg::AnimationPath::ControlPoint CPFirst(Vec3d(0,0,0));
	m_pAnimationPath->insert(0,CPFirst);
	
	m_pFinder = new AnimationManagerFinder;
	m_pAvatar->accept(*m_pFinder);
}

//------------------------------------------------------------------------------

Avatar::~Avatar()	{
	delete m_pFinder;
}

//==============================================================================

const char* Avatar::className() const	{
	return "Avatar";
}

//------------------------------------------------------------------------------

void Avatar::startAnimation()	{
	bool bRes = false;

    if (!m_pFinder->_am.valid()) {
        std::cout << "No animations available." << std::endl;
		return;
	}
	
	osgAnimation::BasicAnimationManager* model = m_pFinder->_am.get();
	const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
	const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
	osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);
	bRes = model->isPlaying(anim);

	if (bRes)	{
		std::cout << "Animation already playing - go out of the loop." << std::endl;
		return;
	}

	setUpdateCallback(m_pFinder->_am.get());
	anim->setStartTime(0);
	anim->setPlayMode(osgAnimation::Animation::ONCE);
	model->playAnimation(anim);
	//anim->setDuration(0.1);	//Sets the speed of animation
}

//------------------------------------------------------------------------------

void Avatar::stopAnimation()	{
	osgAnimation::BasicAnimationManager* model = m_pFinder->_am.get();
	model->stopAll();
}

//------------------------------------------------------------------------------

void Avatar::setPosition(const osg::Vec3d & aVec3d)	{
}

//------------------------------------------------------------------------------

void Avatar::setOrientation(const osg::Vec3d & aVec3d)	{
}

//------------------------------------------------------------------------------

void Avatar::addAnimationPath(osg::AnimationPath & aAnimationPath)	{
	m_plstAnimationPaths.push_back(&aAnimationPath);
}

//------------------------------------------------------------------------------

osg::AnimationPath * Avatar::getAnimationPath()	{
	return m_pAnimationPath;
}

//------------------------------------------------------------------------------

void Avatar::slotUpdatePosition()	{

	Matrix matrix1(Matrix::identity());

	Matrix mtrxLocalOrientation =
		matrix1.rotate(
			degrees2Radians((float)90), osg::X_AXIS,
			degrees2Radians((float)0), osg::Y_AXIS,
			degrees2Radians((float)180), osg::Z_AXIS);

	ComputeBoundsVisitor cbv;
	accept(cbv);
	osg::BoundingBox & bB = cbv.getBoundingBox();
	
	Matrix matrix2(Matrix::identity());
	Matrix mtrxLocalTranslation = matrix2.translate(0, -(bB.yMax() - bB.yMin()) * 0.9, 0);
		
	//Avatar put to the center of the camera
	Matrixd & mtrxTransform = m_pKeyboardMouseManipulatorShopClient->getCameraObjectModifier();

	//Avatar rotated so it's look is OK
	mtrxTransform = 
		mtrxLocalOrientation * 
		mtrxLocalTranslation * 
		mtrxTransform;

	setMatrix(mtrxTransform);

	startAnimation();
}
