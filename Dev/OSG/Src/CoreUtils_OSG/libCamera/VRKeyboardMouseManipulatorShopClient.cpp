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
				emit signalCameraPositionOrHeadingDirectionChanged();
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

osg::Matrixd KeyboardMouseManipulatorShopClient::getCameraObjectModifier() const	{
	if (m_bFirstPerson)	{
		return getMatrix();
	}

	Matrix 	mtrxCamera, mtrxTemp;
	Vec3d vecDistance;

	//Coordinates of the camera
	Vec3d vecEye, vecCenter, vecUp;
	getTransformation(vecEye, vecCenter, vecUp);

	vecDistance = vecCenter - vecEye;
	vecDistance.normalize();
	 
	cout << endl;
	cout << "KeyboardMouseManipulatorShopClient::getCameraObjectModifier()" << endl;
	cout << vecEye[0] << " "  << vecEye[1] << " " << vecEye[2] << endl;
	cout << vecCenter[0] << " "  << vecCenter[1] << " " << vecCenter[2] << endl;
	cout << vecUp[0] << " "  << vecUp[1] << " " << vecUp[2] << endl;

	mtrxTemp = getMatrix() * Matrix::translate(vecDistance * 8);

	return mtrxTemp;

//=========================

	//mtrxCamera = 
	//	mtrxTemp *
	//	Matrix::translate(
	//		Vec3d(
	//			0.0,
	//			0.0,
	//			-1.35
	//		)
	//	);

	//return mtrxCamera;
}

//-------------------------------------------------------------------------------

void KeyboardMouseManipulatorShopClient::setCameraPosition2Object(osg::Node * apNode)	{
	//Get BB of the avatar and position camera accordingly
	ComputeBoundsVisitor cbv;
	apNode->accept(cbv);
	osg::BoundingBox & bB = cbv.getBoundingBox();

	float flCenterX = (bB.xMax()+bB.xMin())/2;

	//1. person view
	Vec3d vec3dPerson1Eye = Vec3d(flCenterX,bB.yMax(),bB.zMax());
	Vec3d vec3dPerson1Center = Vec3d(vec3dPerson1Eye.x(),vec3dPerson1Eye.y()+5,0.0);
	Vec3d vec3dPerson1Up = Vec3d(0,0,1);

	Matrixd mtrx1Person = setMatrixTransform(vec3dPerson1Eye, vec3dPerson1Center, vec3dPerson1Up);
	m_lstPredefinedViews.push_back(mtrx1Person);


	//3. person view
	Vec3d vec3dPerson3Eye = Vec3d(flCenterX,4*bB.yMin()-3*bB.yMax(),1.3*bB.zMax());
	Vec3d vec3dPerson3Center = Vec3d(vec3dPerson3Eye.x(),vec3dPerson3Eye.y()+5,0.0);
	//Vec3d vec3dPerson3Center = Vec3d(0.0,0.0,0.0);
	Vec3d vec3dDiff = vec3dPerson3Center - vec3dPerson3Eye;
	Vec3d vecPerp = Vec3d(0,0,1)^vec3dDiff;

	Vec3d vec3dPerson3Up = vec3dDiff^vecPerp;
	vec3dPerson3Up.normalize();

	Matrixd mtrx3Person = setMatrixTransform(vec3dPerson3Eye, vec3dPerson3Center, vec3dPerson3Up);
	m_lstPredefinedViews.push_back(mtrx3Person);


	//Also set the camera
	list<Matrixd>::iterator it = m_lstPredefinedViews.begin();
	Matrixd vecMatrix;
	if (m_bFirstPerson)	{	//First person
		vecMatrix = *it;
	} else {	//Third person
		std::advance(it,1);
		vecMatrix = *it;
	}

	//Set current view
	setTransformation(vec3dPerson3Eye, vec3dPerson3Center, vec3dPerson3Up);
	emit signalCameraPositionOrHeadingDirectionChanged();
}

//-------------------------------------------------------------------------------

void KeyboardMouseManipulatorShopClient::setViewPerspective(bool abFirstPerson) {
	m_bFirstPerson = abFirstPerson;

	//Previous coordinates of the camera
	Vec3d vecPrevEye, vecPrevCenter, vecPrevUp;
	getTransformation(vecPrevEye, vecPrevCenter, vecPrevUp);

	osg::Matrixd mtrxNewCamera;
	list<Matrixd>::iterator it = m_lstPredefinedViews.begin();
	if (m_bFirstPerson)	{	//First person
		mtrxNewCamera = *it;
	} else {	//Third person
		std::advance(it,1);
		mtrxNewCamera = *it;
	}

	setByMatrix(mtrxNewCamera);

	//Emitting the signal will provoke matrix re-calculation
	emit signalCameraPositionOrHeadingDirectionChanged();
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