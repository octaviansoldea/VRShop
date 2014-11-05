/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
*
* This library is open source and may be redistributed and/or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* OpenSceneGraph Public License for more details.
*/

/* Modified by Matej Steinbacher and Octavian Soldea */

#include <iostream>
#include "BasicDefinitions.h"

#include <osgGA/GUIEventAdapter>
#include <osg/ComputeBoundsVisitor>
#include <osg/MatrixTransform>

#include "VRKeyboardMouseManipulatorShopClient.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


KeyboardMouseManipulatorShopClient::KeyboardMouseManipulatorShopClient(int flags) :
KeyboardMouseManipulator(flags) {
	m_bFirstPerson = false;
}

//-------------------------------------------------------------------------------

KeyboardMouseManipulatorShopClient::KeyboardMouseManipulatorShopClient
	(const KeyboardMouseManipulatorShopClient& cm, const CopyOp& copyOp) :
KeyboardMouseManipulator(cm, copyOp) {
	m_bFirstPerson = false;
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulatorShopClient::keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)	{
	bool bRes = true;

	int nResKey = ea.getKey();
	if ((nResKey == osgGA::GUIEventAdapter::KEY_Control_L) ||
		(nResKey == osgGA::GUIEventAdapter::KEY_Control_R))	{
		m_bCtrl = true;
	}

	if ((nResKey == osgGA::GUIEventAdapter::KEY_Shift_L) ||
		(nResKey == osgGA::GUIEventAdapter::KEY_Shift_R))	{
		m_bShift = true;
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Up)	{
		if (m_bCtrl)	{ //Move forward
			m_dbForwardFactor = 0.5 * (m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);

			Vec3d prevCenter, prevEye, prevUp;
			getTransformation(prevEye, prevCenter, prevUp);
			Vec3d dbvecDirection = prevCenter - prevEye;

			float flvecStep = fabs(dbvecDirection.x()) + fabs(dbvecDirection.y());
			float deltaStepX = m_dbForwardFactor*(dbvecDirection.x() / flvecStep);
			float deltaStepY = m_dbForwardFactor*(dbvecDirection.y() / flvecStep);

			Vec3d newEye = prevEye + Vec3d(deltaStepX, deltaStepY, 0.0);
			Vec3d newCenter = prevCenter + Vec3d(deltaStepX, deltaStepY, 0.0);

			setTransformation(newEye, newCenter, prevUp);

		}
		else { //Rotate view (but not direction of travel) up.
			m_dbTranslationFactorX = m_cdbRotationFactor *
				(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);
			panModel(0.0, m_dbTranslationFactorX);
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Down)	{
		if (m_bCtrl)	{ //Move backwards
			m_dbForwardFactor = 0.5 * (m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);

			Vec3d prevCenter, prevEye, prevUp;
			getTransformation(prevEye, prevCenter, prevUp);
			Vec3d dbvecDirection = prevCenter - prevEye;

			float flvecStep = fabs(dbvecDirection.x()) + fabs(dbvecDirection.y());
			float deltaStepX = m_dbForwardFactor*(dbvecDirection.x() / flvecStep);
			float deltaStepY = m_dbForwardFactor*(dbvecDirection.y() / flvecStep);

			Vec3d newEye = prevEye - Vec3d(deltaStepX, deltaStepY, 0.0);
			Vec3d newCenter = prevCenter - Vec3d(deltaStepX, deltaStepY, 0.0);

			setTransformation(newEye, newCenter, prevUp);

		}
		else { //Rotate view (but not direction of travel) down.
			m_dbTranslationFactorX = -m_cdbRotationFactor *
				(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);
			panModel(0.0, m_dbTranslationFactorX);
		}
	}

	if ((nResKey == osgGA::GUIEventAdapter::KEY_Right) ||
		((nResKey == osgGA::GUIEventAdapter::KEY_Left))) {

		double dbDir = 1.0;
		if (nResKey == osgGA::GUIEventAdapter::KEY_Left) {
			dbDir = -1.0;
		}

		if (m_bCtrl)	{	//Translate camera right
			m_dbTranslationFactorZ = dbDir * m_cdbRotationFactor *
				(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);
			panModel(m_dbTranslationFactorZ, 0.0);
		}
		else {	//Rotate camera to the right
			m_dbDirectionRotationRate = dbDir  * (- m_cdbRotationFactor) *
				(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);

			Vec3d prevCenter, prevEye, prevUp;
			getTransformation(prevEye, prevCenter, prevUp);
			Vec3d vecdbDirection = prevCenter - prevEye;

			if (this->m_bFirstPerson) {
				Vec3d normalized = vecdbDirection * Matrix::rotate(DegreesToRadians(m_dbDirectionRotationRate), prevUp);
				Vec3d newCenter = prevEye + normalized;
				setTransformation(prevEye, newCenter, prevUp);
			} else {
				vecdbDirection.normalize();
				vecdbDirection = vecdbDirection * m_flCameraCorrector * 2;
				Vec3d newCenter = prevEye + vecdbDirection;

				Vec3d vecdbAntiDirection = -vecdbDirection;
				vecdbAntiDirection.normalize();
				Vec3d twisted = vecdbAntiDirection * Matrix::rotate(DegreesToRadians(m_dbDirectionRotationRate), prevUp);
				twisted.normalize();
				twisted *= m_flCameraCorrector * 2;
				Vec3d newEye = newCenter + twisted;
				setTransformation(newEye, newCenter, prevUp);
			}
		}

	}

	if (nResKey == ' ')	{
		home(0);
	} else	{
		bRes = false;
	}

	return(bRes);
}
//-------------------------------------------------------------------------------

bool KeyboardMouseManipulatorShopClient::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa) {
	bool bRes = false;
	Matrixd prevCameraMatrix = getMatrix();

	bRes = KeyboardMouseManipulator::handle(ea, aa);
	if(bRes == false) {
		return(bRes);
	}

	Matrixd currentCameraMatrix = getMatrix();

	float flDiffCumulation=0;
	int iI, iJ;
	for(iI = 0; iI < 4; iI++)	{
		for(iJ = 0; iJ < 4; iJ++)	{
			if (fabs(currentCameraMatrix(iI,iJ) - prevCameraMatrix(iI,iJ)) > EPS)	{
				emit signalCameraPositionOrHeadingDirectionChanged(true);
				return true;
			}
		}
	}

	return(bRes);
}

//-------------------------------------------------------------------------------

osg::Matrixd KeyboardMouseManipulatorShopClient::setMatrixTransform(Vec3d &avec3dEye,Vec3d &avec3dCenter,Vec3d &avec3dUp)	{
    Vec3d lv(avec3dCenter - avec3dEye);

    Vec3d f( lv );
    f.normalize();
    Vec3d s( f^avec3dUp );
    s.normalize();
    Vec3d u( s^f );
    u.normalize();

    osg::Matrixd rotation_matrix( s[0], u[0], -f[0], 0.0f,
                            s[1], u[1], -f[1], 0.0f,
                            s[2], u[2], -f[2], 0.0f,
                            0.0f, 0.0f,  0.0f, 1.0f );

	osg::Quat mtrxRot = rotation_matrix.getRotate().inverse();

	return Matrixd::rotate(mtrxRot) * Matrixd::translate( avec3dEye );
}

//-------------------------------------------------------------------------------

Vec3d KeyboardMouseManipulatorShopClient::cameraPerspectiveCorrector() const	{
	//Repositions the camera and reports the change to the avatar to do its repositioning
	const Matrixd & mtrxCamera1Person = m_vecPredefinedViews[0];
	const Matrixd & mtrxCamera3Person = m_vecPredefinedViews[1];

	Vec3d vec3dCameraPerspectiveDiff;

	//Calculate diff between both cameras eyes
	vec3dCameraPerspectiveDiff = Vec3d(
		mtrxCamera3Person(3,0) - mtrxCamera1Person(3,0),
		mtrxCamera3Person(3,1) - mtrxCamera1Person(3,1),
		mtrxCamera3Person(3,2) - mtrxCamera1Person(3,2)
	);

	return vec3dCameraPerspectiveDiff;
}

//-------------------------------------------------------------------------------

osg::Matrixd KeyboardMouseManipulatorShopClient::getAvatar2CameraMatrix() {
	Matrix matrixRot(Matrix::identity());

	Matrix mtrxLocalOrientation =
		matrixRot.rotate(
		degrees2Radians((float)90), osg::X_AXIS,//90
		degrees2Radians((float)0), osg::Y_AXIS,
		degrees2Radians((float)180), osg::Z_AXIS);//180

	Matrix mtrxLocalTranslation;
	Matrix matrixPos(Matrix::identity());

	if (m_bFirstPerson)	{
		mtrxLocalTranslation = matrixPos.translate(0, 10, -1.3*m_BoundingBox.zMax());
	}
	else {
		mtrxLocalTranslation = matrixPos.translate(0, 4 * m_BoundingBox.yMin() - 3 * m_BoundingBox.yMax(), -1.0);
	}

	//float flCameraCorrector;
	//if (getViewPerspective())	{
	//	//First person
	//	flCameraCorrector = -bB.yMax();
	//}
	//else {
	//	//Third person
	//	flCameraCorrector = -(4 * bB.yMin() - 3 * bB.yMax());
	//}

	//Coordinates of the camera
	Vec3d vecEye, vecCenter, vecUp;
	getTransformation(vecEye, vecCenter, vecUp);

	Vec3d vecDistance = vecCenter - vecEye;
	vecDistance.normalize();

	Matrix mtrxCamera = getMatrix() * Matrix::translate(vecDistance * m_flCameraCorrector);

	//Avatar rotated so its look is OK
	Matrixd mtrxTransform =
		mtrxLocalTranslation *
		mtrxLocalOrientation *

		mtrxCamera;

	return mtrxTransform;
}

//-------------------------------------------------------------------------------

void KeyboardMouseManipulatorShopClient::setCameraPosition2Object(osg::Node * apNode)	{
	//Get BB of the avatar and position camera accordingly
	ComputeBoundsVisitor cbv;
	apNode->accept(cbv);
	m_BoundingBox = cbv.getBoundingBox();

	if (m_bFirstPerson)	{
		//First person
		m_flCameraCorrector = -m_BoundingBox.yMax();
	}
	else {
		//Third person
		m_flCameraCorrector = -(4 * m_BoundingBox.yMin() - 3 * m_BoundingBox.yMax());
	}


	float flCenterX = (m_BoundingBox.xMax()+m_BoundingBox.xMin())/2;

	//1. person view
	Vec3d vec3dPerson1Eye = Vec3d(flCenterX,m_BoundingBox.yMax(),m_BoundingBox.zMax());
	Vec3d vec3dPerson1Center = Vec3d(vec3dPerson1Eye.x(),vec3dPerson1Eye.y()+5,0.0);
	Vec3d vec3dDiff1 = vec3dPerson1Center - vec3dPerson1Eye;
	Vec3d vec3dPerp1 = Vec3d(0,0,1)^vec3dDiff1;
	Vec3d vec3dPerson1Up = vec3dDiff1^vec3dPerp1;
	vec3dPerson1Up.normalize();

	Matrixd mtrx1Person = Matrix::inverse(Matrix::lookAt(vec3dPerson1Eye, vec3dPerson1Center, vec3dPerson1Up));
	m_vecPredefinedViews.push_back(mtrx1Person);


	//3. person view
	Vec3d vec3dPerson3Eye = Vec3d(flCenterX,4*m_BoundingBox.yMin()-3*m_BoundingBox.yMax(),1.3*m_BoundingBox.zMax());
	Vec3d vec3dPerson3Center = Vec3d(vec3dPerson3Eye.x(),vec3dPerson3Eye.y()+5,0.0);
	Vec3d vec3dDiff3 = vec3dPerson3Center - vec3dPerson3Eye;
	Vec3d vec3dPerp3 = Vec3d(0,0,1)^vec3dDiff3;
	Vec3d vec3dPerson3Up = vec3dDiff3^vec3dPerp3;
	vec3dPerson3Up.normalize();

	Matrixd mtrx3Person = Matrix::inverse(Matrix::lookAt(vec3dPerson3Eye, vec3dPerson3Center, vec3dPerson3Up));
	m_vecPredefinedViews.push_back(mtrx3Person);

	//Also set the camera
	if (m_bFirstPerson)	{	//First person
		setTransformation(vec3dPerson1Eye, vec3dPerson1Center, vec3dPerson1Up);
	} else {	//Third person
		setTransformation(vec3dPerson3Eye, vec3dPerson3Center, vec3dPerson3Up);
	}
}

//-------------------------------------------------------------------------------

void KeyboardMouseManipulatorShopClient::setViewPerspective(bool abFirstPerson) {
	m_bFirstPerson = abFirstPerson;

	Matrixd mtrxCamera = getMatrix();

	Vec3d vec3dCameraPerspectiveDiff = cameraPerspectiveCorrector();

	//Set camera according to the view perspective
	if (m_bFirstPerson)	{	//First person
		mtrxCamera = mtrxCamera *
			Matrix::translate(Vec3d(
				vec3dCameraPerspectiveDiff[0],
				-vec3dCameraPerspectiveDiff[1],
				-vec3dCameraPerspectiveDiff[2]));
	} else {	//Third person
		mtrxCamera = mtrxCamera *
			Matrix::translate(Vec3d(
				vec3dCameraPerspectiveDiff[0],
				vec3dCameraPerspectiveDiff[1],
				vec3dCameraPerspectiveDiff[2]));
	}

	if (m_bFirstPerson)	{
		//First person
		m_flCameraCorrector = -m_BoundingBox.yMax();
	}
	else {
		//Third person
		m_flCameraCorrector = -(4 * m_BoundingBox.yMin() - 3 * m_BoundingBox.yMax());
	}

	setByMatrix(mtrxCamera);

	//Emitting the signal will provoke matrix re-calculation
	emit signalCameraPositionOrHeadingDirectionChanged(false);
}

//-------------------------------------------------------------------------------

osg::BoundingBox VR::KeyboardMouseManipulatorShopClient::getBoundingBox() const	{
	return m_BoundingBox;
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulatorShopClient::getViewPerspective() const	{
	return m_bFirstPerson;
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulatorShopClient::checkObstructionInFront(float aflDistance)	{
	bool bRes = true;

	return bRes;
}