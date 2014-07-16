#include <osgDB/ReadFile>
#include <string>
#include "BasicDefinitions.h"

#include "VRKeyboardMouseManipulatorShopClient.h"
#include <osg/ComputeBoundsVisitor>
#include <osg/CoordinateSystemNode>

#include "VRAnimationPath.h"

#include "AnimtkViewer.h"

#include "VRAvatar.h"

using namespace VR;
using namespace osg;
using namespace std;

AvatarParams::AvatarParams() :
	m_strAvatarFile(""),
	m_strAvatarName(""),
	m_pKeyboardMouseManipulatorShopClient(0),
	m_pParent(0)
{
}

//==============================================================================

Avatar::Avatar(std::string & astrAvatarFile, QObject * parent): QObject(parent)	{
	addChild(osgDB::readNodeFile(astrAvatarFile));
	setName("avatar");

	m_pKeyboardMouseManipulatorShopClient = 0;
	m_pAnimationPath = 0;
	m_pAPCallback = 0;
	m_pFinder = 0;

	Group & pGroup = dynamic_cast<Group&>(*getChild(0));
	m_p_LocalCoords_Avatar = dynamic_cast<Group*>(pGroup.getChild(0));
}

//-----------------------------------------------------------------------------

Avatar::Avatar(const AvatarParams * apAvatarParams) : QObject(apAvatarParams->m_pParent)	{

	m_pKeyboardMouseManipulatorShopClient = apAvatarParams->m_pKeyboardMouseManipulatorShopClient;

	ref_ptr<Group> pAvatarFile = dynamic_cast<Group*>(osgDB::readNodeFile(apAvatarParams->m_strAvatarFile));

	addChild(pAvatarFile);
	setName(apAvatarParams->m_strAvatarName);

	connect(m_pKeyboardMouseManipulatorShopClient, 
		SIGNAL(signalCameraPositionOrHeadingDirectionChanged(bool)),
		this,SLOT(slotUpdatePosition(bool)));

	m_pAnimationPath = new VR::AnimationPath();
	m_pAPCallback = new osg::AnimationPathCallback(m_pAnimationPath);
//	m_pAPCallback = new osg::AnimationPathCallback();
	m_pFinder = new AnimationManagerFinder;

	Group & pGroup = dynamic_cast<Group&>(*getChild(0));
	m_p_LocalCoords_Avatar = dynamic_cast<Group*>(pGroup.getChild(0));
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

void Avatar::setAnimation(const Matrixd & amtrxOldMatrix, const Matrixd & amtrxNewMatrix)	{
	// Create animation path
	Vec3d vec3dCurrentPoint = Vec3d(amtrxOldMatrix(3,0),amtrxOldMatrix(3,1),amtrxOldMatrix(3,2));
	Vec3d vec3dNewPoint = Vec3d(amtrxNewMatrix(3,0),amtrxNewMatrix(3,1),amtrxNewMatrix(3,2));

	// Define control points
	osg::AnimationPath::ControlPoint CP0(vec3dCurrentPoint);
	osg::AnimationPath::ControlPoint CP1(vec3dNewPoint);

	// Insert them to the path
	m_pAnimationPath->insert( 0.0f, CP0 ); // time, point
	m_pAnimationPath->insert( 10.0f, CP1 );
	m_pAnimationPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
	m_pAPCallback->setAnimationPath(m_pAnimationPath);

	// Define animation path callback
	setUpdateCallback(m_pAPCallback);

	std::cout << "Animation time: " << m_pAPCallback->getAnimationTime() << endl;

	startAnimation();

	setMatrix(amtrxNewMatrix);
}

//------------------------------------------------------------------------------

void Avatar::startAnimation()	{
	bool bRes = false;

	m_p_LocalCoords_Avatar->accept(*m_pFinder);

	if (!m_pFinder->_am.valid()) {
		std::cout << "No animations available." << std::endl;
		return;
	}

	osgAnimation::BasicAnimationManager* model = m_pFinder->_am.get();
	const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
	const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
	osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);
	anim->computeDuration();
	bRes = model->isPlaying(anim);

	float flDuration = anim->getDuration();
	
	if (bRes)	{
		std::cout << "Animation already playing - go out of the loop." << std::endl;
		return;
	}

	m_p_LocalCoords_Avatar->setDataVariance(DataVariance::DYNAMIC);
	m_p_LocalCoords_Avatar->setUpdateCallback(model);
	anim->setStartTime(0);
	anim->setPlayMode(osgAnimation::Animation::ONCE);
	model->playAnimation(anim);
}

//------------------------------------------------------------------------------

void Avatar::stopAnimation()	{
	osgAnimation::BasicAnimationManager* model = m_pFinder->_am.get();
	model->stopAll();
	
	const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
	const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
	osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);
	model->stopAnimation(anim);
	anim->setStartTime(0);
}

//------------------------------------------------------------------------------

void Avatar::setPosition(const osg::Vec3d & aVec3d)	{
}

//------------------------------------------------------------------------------

void Avatar::setOrientation(const osg::Vec3d & aVec3d)	{
}

//------------------------------------------------------------------------------

void Avatar::addAnimationPath(VR::AnimationPath * apAnimationPath)	{
//	m_plstAnimationPaths.push_back(&aAnimationPath);
	m_pAnimationPath = apAnimationPath;

	m_pAPCallback->setDataVariance(osg::Object::DYNAMIC);
	m_pAPCallback->setAnimationPath(m_pAnimationPath);
	setUpdateCallback(m_pAPCallback);

	std::cout << "Animation time: " << m_pAPCallback->getAnimationTime() << endl;
}

//------------------------------------------------------------------------------

VR::AnimationPath * Avatar::getAnimationPath()	{
	return m_pAnimationPath;
}

//------------------------------------------------------------------------------

void Avatar::slotUpdatePosition(bool abAnimation)	{
	Matrix matrixRot(Matrix::identity());

	Matrix mtrxLocalOrientation =
		matrixRot.rotate(
			degrees2Radians((float)90), osg::X_AXIS,//90
			degrees2Radians((float)0), osg::Y_AXIS,
			degrees2Radians((float)180), osg::Z_AXIS);//180

	Matrix mtrxLocalTranslation;
	Matrix matrixPos(Matrix::identity());
	bool bView = m_pKeyboardMouseManipulatorShopClient->getViewPerspective();

	osg::BoundingBox & bB = m_pKeyboardMouseManipulatorShopClient->getBoundingBox();

	if (bView)	{
		mtrxLocalTranslation = matrixPos.translate(0, 10, -1.3*bB.zMax());
	} else {
		mtrxLocalTranslation = matrixPos.translate(0, 4*bB.yMin()-3*bB.yMax(), -1.0);
//		mtrxLocalTranslation = matrixPos.translate(0, 0, -1.0);
	}
	
	//Avatar put to the center of the camera
	Matrixd & mtrxTransform = setAvatar2Camera();

	//Avatar rotated so its look is OK
	mtrxTransform = 
		mtrxLocalTranslation * 
		mtrxLocalOrientation * 
		
		mtrxTransform;

	setMatrix(mtrxTransform);

	if(abAnimation)
		startAnimation();
	else
		stopAnimation();
}

//------------------------------------------------------------------------------

osg::Matrixd Avatar::setAvatar2Camera()	{
	//Get BB of the avatar and position camera accordingly
	osg::BoundingBox & bB = m_pKeyboardMouseManipulatorShopClient->getBoundingBox();

	Matrix mtrxCamera;
	Vec3d vecDistance;

	float flCameraCorrector;
	if (m_pKeyboardMouseManipulatorShopClient->getViewPerspective())	{
		flCameraCorrector = -bB.yMax();
	} else {
		flCameraCorrector = -(4*bB.yMin()-3*bB.yMax());
	}

	//Coordinates of the camera
	Vec3d vecEye, vecCenter, vecUp;
	m_pKeyboardMouseManipulatorShopClient->getTransformation(vecEye, vecCenter, vecUp);

	vecDistance = vecCenter - vecEye;
	vecDistance.normalize();

	mtrxCamera = m_pKeyboardMouseManipulatorShopClient->getMatrix() * 
		Matrix::translate(vecDistance * flCameraCorrector);

	return mtrxCamera;
}
