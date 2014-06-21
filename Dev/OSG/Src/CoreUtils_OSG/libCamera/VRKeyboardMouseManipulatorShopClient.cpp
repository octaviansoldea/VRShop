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

#include <osgGA/GUIEventAdapter>
#include <osg/ComputeBoundsVisitor>
#include <osg/MatrixTransform>

#include "BasicDefinitions.h"
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

void KeyboardMouseManipulatorShopClient::setCameraPosition2Object(osg::Node * apNode)	{
	//Get BB of the avatar and position camera accordingly
	ComputeBoundsVisitor cbv;
	apNode->accept(cbv);
	m_BoundingBox = cbv.getBoundingBox();

	float flCenterX = (m_BoundingBox.xMax()+m_BoundingBox.xMin())/2;

	//1. person view
	Vec3d vec3dPerson1Eye = Vec3d(flCenterX,m_BoundingBox.yMax(),m_BoundingBox.zMax());
	Vec3d vec3dPerson1Center = Vec3d(vec3dPerson1Eye.x(),vec3dPerson1Eye.y()+5,0.0);
	Vec3d vec3dDiff1 = vec3dPerson1Center - vec3dPerson1Eye;
	Vec3d vec3dPerp1 = Vec3d(0,0,1)^vec3dDiff1;
	Vec3d vec3dPerson1Up = vec3dDiff1^vec3dPerp1;
	vec3dPerson1Up.normalize();

	Matrixd mtrx1Person = setMatrixTransform(vec3dPerson1Eye, vec3dPerson1Center, vec3dPerson1Up);
	m_vecPredefinedViews.push_back(mtrx1Person);


	//3. person view
	Vec3d vec3dPerson3Eye = Vec3d(flCenterX,4*m_BoundingBox.yMin()-3*m_BoundingBox.yMax(),1.3*m_BoundingBox.zMax());
	Vec3d vec3dPerson3Center = Vec3d(vec3dPerson3Eye.x(),vec3dPerson3Eye.y()+5,0.0);
	Vec3d vec3dDiff3 = vec3dPerson3Center - vec3dPerson3Eye;
	Vec3d vec3dPerp3 = Vec3d(0,0,1)^vec3dDiff3;
	Vec3d vec3dPerson3Up = vec3dDiff3^vec3dPerp3;
	vec3dPerson3Up.normalize();

	Matrixd mtrx3Person = setMatrixTransform(vec3dPerson3Eye, vec3dPerson3Center, vec3dPerson3Up);
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