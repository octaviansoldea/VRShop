//Pressing "H": make lateral movement
//Pressing "V": make vertical movement
//Pressing "L": make longitudial movement
//Pressing "R": make rotation
//Pressing "S": make scalling
//Pressing "SHIFT L or R": make movement Up/down-Left/right irrespective of axes

#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>
#include <osg/Group>

#include <iostream>

#include "VRBoundingBox.h"
#include "VRAbstractObject.h"

#include "BasicDefinitions.h"
#include "VRObjectTransformation.h"

#include "VRPickAndDragHandler.h"

using namespace osg;
using namespace osgGA;
using namespace VR;

PickAndDragHandler::PickAndDragHandler() {
	m_dbMouseLastGetXNormalized = 0;
	m_dbMouseLastGetYNormalized = 0;

	m_dbMouseLastGetX = 0;
	m_dbMouseLastGetY = 0;

	m_nTransformSelection = MOVE_ON_XZ;
}

//------------------------------------------------------------------------------

bool PickAndDragHandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa )	{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	m_pScene = dynamic_cast<Group*>(viewer->getSceneData());
	
	switch (ea.getEventType())
	{
	//Keydown sets the type of the transformation to be performed
	case(GUIEventAdapter::KEYDOWN): {
		int nKey = ea.getKey();
		if (nKey == 'h' || nKey == 'H')
			m_nTransformSelection = LATERAL_MOVE;
		else if (nKey == 'v' || nKey == 'V')
			m_nTransformSelection = VERTICAL_MOVE;
		else if (nKey == 'l' || nKey == 'L')
			m_nTransformSelection = LONGITUDINAL_MOVE;
		else if (nKey == 'r' || nKey == 'R')
			m_nTransformSelection = ROTATION;
		else if (nKey == 's' || nKey == 'S')
			m_nTransformSelection = SCALING;
		else if (nKey == GUIEventAdapter::KEY_Shift_L || nKey == GUIEventAdapter::KEY_Shift_R)
			m_nTransformSelection = LATERAL_VERTICAL_TO_MONITOR;
		else 
			m_nTransformSelection = MOVE_ON_XZ;
	}	//Case: Keydown

	case(GUIEventAdapter::PUSH):	{
		int nButton = ea.getButton();
		if(nButton == GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			double dbMargin = 0.01;

			//Do the polytope intersections with the scene graph.
			osgUtil::PolytopeIntersector* picker = new osgUtil::PolytopeIntersector( 
				osgUtil::Intersector::PROJECTION,
				ea.getXnormalized()-dbMargin,
				ea.getYnormalized()-dbMargin,
				ea.getXnormalized()+dbMargin,
				ea.getYnormalized()+dbMargin);

			//InteresectionVisitor is used to testing for intersections with the scene
			osgUtil::IntersectionVisitor iv(picker);
			viewer->getCamera()->accept(iv);

			//Check if any part of the scene was picked
			if (picker->containsIntersections())	{
				m_dbMouseLastGetX = ea.getX();
				m_dbMouseLastGetY = ea.getY();

				m_dbMouseLastGetXNormalized = ea.getXnormalized();
				m_dbMouseLastGetYNormalized = ea.getYnormalized();

				//A vector of Nodes from a root node to a descendant
				NodePath& nodePath = picker->getFirstIntersection().nodePath;

				//Navigate through nodes and pick the "right" one
				int idx;
				for(idx=nodePath.size()-1; idx>=0; idx--) {
					m_pPickedObject = dynamic_cast<AbstractObject*>(nodePath[idx]);
					if(m_pPickedObject != NULL && m_pPickedObject->getIsTargetPick() != false) {
						break;
					}
				}

				//Get the matrix of the picked object and pass it to the drag
				if(idx >= 0)
					m_mtrxPickedObject = m_pPickedObject->getMatrix();
				else
					m_pPickedObject = NULL;
			}
			else	{
				m_pPickedObject = NULL;
			}
			break;
		}	//Case: Push_Left_Mouse_button
		else {
			m_pPickedObject = NULL;
		}
	}	//Case: Push

	
	case(GUIEventAdapter::DRAG): {
		if(m_pPickedObject==NULL) {
			return false;
		}

		//A mouse move 
		float flDiffPosX =	ea.getXnormalized() - m_dbMouseLastGetXNormalized; 
		float flDiffPosY =	ea.getYnormalized() - m_dbMouseLastGetYNormalized;

		if(fabs(flDiffPosX)<0.001 && fabs(flDiffPosY)<0.001) {
			return false;
		}

		Matrixd mat = viewer->getCameraManipulator()->getMatrix();
		Vec3f vec3dLook(mat(2,0),mat(2,1),mat(2,2));
		Vec3f eyeVector(mat(3,0),mat(3,1),mat(3,2));

		//Move factor controls the move for the distance of the object from the camera
		float moveFactor = 0.3F * (vec3dLook - eyeVector).length();

		ObjectTransformation * pObjectTransformation = new ObjectTransformation();
		Matrix mtrx;
		Matrix mtrx1;

		//Does Up/down-left/right dragging respective to the axes
		if(m_nTransformSelection == MOVE_ON_XZ)	{
			mtrx = m_mtrxPickedObject *
				pObjectTransformation->setGetTranslation(moveFactor*(flDiffPosX), 0.0, moveFactor*(flDiffPosY));
		}

		//Does Up/down-left/right dragging irrespective of the axes
		if(m_nTransformSelection == LATERAL_VERTICAL_TO_MONITOR) {
			mtrx = m_mtrxPickedObject *
				pObjectTransformation->setGetTranslation(
				moveFactor*(flDiffPosX)*mat(0,0), 
				moveFactor*(flDiffPosX)*mat(0,1), 
				moveFactor*(flDiffPosY)
			);
		}

		if(m_nTransformSelection == LATERAL_MOVE)	{
			mtrx = m_mtrxPickedObject *
				pObjectTransformation->setGetTranslation(moveFactor*(flDiffPosX), 0.0, 0.0);
		}

		if(m_nTransformSelection == VERTICAL_MOVE)	{
			mtrx = m_mtrxPickedObject *
				pObjectTransformation->setGetTranslation(0.0, 0.0, moveFactor*(flDiffPosY));
		}

		if(m_nTransformSelection == LONGITUDINAL_MOVE)	{
			mtrx = m_mtrxPickedObject *
				pObjectTransformation->setGetTranslation(0.0, moveFactor*(flDiffPosY), 0.0);
		}

		if(m_nTransformSelection == ROTATION)	{
			//Angles should be in radians
			double flRXAngle = 
				flDiffPosY
//				degrees2Radians(1.0)
				;
			double flRYAngle = 
				flDiffPosX
//				degrees2Radians(1.0)
				;
			double flRZAngle = 
				flDiffPosX
//				degrees2Radians(1.0)
				;

			mtrx = pObjectTransformation->setGetRotation(flRZAngle, ROTATION_ON_Z)	*
				 pObjectTransformation->setGetRotation(flRYAngle, ROTATION_ON_Y)	*
				 pObjectTransformation->setGetRotation(flRXAngle, ROTATION_ON_X)	*
				 m_mtrxPickedObject;
			
			//Vec3f flvecObjectCenter(m_pPickedObject->getBound().center());
			//Vec3f flvecRotationDirection(mat(2,0),mat(2,1),mat(2,2));

			//float U(flvecObjectCenter.x());
			//float V(flvecObjectCenter.y());
			//float W(flvecObjectCenter.z());

			//float dist = (flvecRotationDirection-flvecObjectCenter).length();


			//mtrx = Matrix::inverse(pObjectTransformation->setGetTranslation(-U,-V,-W)) *
			//	 pObjectTransformation->setGetRotation(flRYAngle, ROTATION_ON_Y)	*
			//	 pObjectTransformation->setGetRotation(flRXAngle, ROTATION_ON_X)	*
			//	 pObjectTransformation->setGetTranslation(-U,-V,-W) *
			//	 m_mtrxPickedObject;

//			mtrx =
//				Matrix::inverse(pObjectTransformation->setGetTranslation(-flvecObjectCenter.x(),-flvecObjectCenter.y(),-flvecObjectCenter.z())) *
//				pObjectTransformation->setGetRotation(flRZAngle, ROTATION_ON_Z) *
				//pObjectTransformation->setGetRotation(flRYAngle, ROTATION_ON_Y) *
				//pObjectTransformation->setGetRotation(flRXAngle, ROTATION_ON_X) *
//				pObjectTransformation->setGetTranslation(-flvecObjectCenter.x(),-flvecObjectCenter.y(),-flvecObjectCenter.z()) *
//				m_mtrxPickedObject
//				;

				
			//mtrx = m_mtrxPickedObject * X;	ROTATES AROUND THE SCENE'S ORIGIN (PRE-MULTIPLY)
			//mtrx = X * m_mtrxPickedObject;	ROTATES AROUND THE OBJECT'S ORIGIN (POST-MULTIPLY)
		}

		if(m_nTransformSelection == SCALING)	{
			mtrx = pObjectTransformation->setGetScaling(moveFactor*(flDiffPosX), moveFactor*(flDiffPosX), moveFactor*(flDiffPosX)) 
				* m_mtrxPickedObject;
		}

		delete pObjectTransformation;

		m_pPickedObject->setMatrix(mtrx);

		viewer->setSceneData(m_pScene);

		return false;
								 }

	case(GUIEventAdapter::RELEASE):	{
		m_nTransformSelection = MOVE_ON_XZ;

		//Remove bounding box - bounding box is put as a last child
		//if(m_pPickedObject!=NULL)
		//	m_pPickedObject->removeChild(m_pPickedObject->getNumChildren()-1);

		return false;
		break;
										}
	}
	return false;
}

//---------------------------------------------------------------------------------------
