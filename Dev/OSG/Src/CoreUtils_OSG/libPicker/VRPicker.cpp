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

#include "VRPicker.h"

using namespace VR;
using namespace osg;
using namespace osgGA;

PickAndDragHandler::PickAndDragHandler()	{
	m_dbMouseLastGetXNormalized = 0;
	m_dbMouseLastGetYNormalized = 0;

	m_dbMouseLastGetX = 0;
	m_dbMouseLastGetY = 0;

	m_nTransformSelection = 0;
}

//------------------------------------------------------------------------------

bool PickAndDragHandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa )	{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	enum enumObjectTransform {DEFAULT = 0, LATERAL_MOVE, VERTICAL_MOVE, LONGITUDINAL_MOVE, ROTATION, SCALING,
								LATERAL_VERTICAL_TO_MONITOR};

	m_pScene = dynamic_cast<Group*>(viewer->getSceneData());

	switch (ea.getEventType())
	{
	case(GUIEventAdapter::KEYDOWN): {
		switch(ea.getKey())
		{
		case 'h': case 'H':
			m_nTransformSelection = enumObjectTransform(LATERAL_MOVE);
			return false;
			break;

		case 'v': case 'V':
			m_nTransformSelection = enumObjectTransform(VERTICAL_MOVE);
			return false;
			break;

		case 'l': case 'L':
			m_nTransformSelection = enumObjectTransform(LONGITUDINAL_MOVE);
			return false;
			break;

		case 'r': case 'R':
			m_nTransformSelection = enumObjectTransform(ROTATION);
			return false;
			break;

		case 's': case 'S':
			m_nTransformSelection = enumObjectTransform(SCALING);
			return false;
			break;

		case GUIEventAdapter::KEY_Shift_L:
		case GUIEventAdapter::KEY_Shift_R:
			m_nTransformSelection = enumObjectTransform(LATERAL_VERTICAL_TO_MONITOR);
			return false;
			break;

		default:
			m_nTransformSelection = enumObjectTransform(DEFAULT);
			return false;
			break;
		}
	}	//Case: Keydown

	case(GUIEventAdapter::PUSH):	{
		int nButton = ea.getButton();
		if(nButton == GUIEventAdapter::LEFT_MOUSE_BUTTON) {
//		if(nButton == GUIEventAdapter::LEFT_MOUSE_BUTTON && ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT)	{
			double margin = 0.01;

			osgUtil::PolytopeIntersector* picker = new osgUtil::PolytopeIntersector( 
				osgUtil::Intersector::PROJECTION,
				ea.getXnormalized()-margin,
				ea.getYnormalized()-margin,
				ea.getXnormalized()+margin,
				ea.getYnormalized()+margin);

			osgUtil::IntersectionVisitor iv(picker);
			viewer->getCamera()->accept(iv);

			if (picker->containsIntersections())	{
				m_dbMouseLastGetX = ea.getX();
				m_dbMouseLastGetY = ea.getY();

				m_dbMouseLastGetXNormalized = ea.getXnormalized();
				m_dbMouseLastGetYNormalized = ea.getYnormalized();

				osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;

				int idx;
				for(idx=nodePath.size()-1; idx>=0; idx--) {
					m_pPickedObject = dynamic_cast<AbstractObject*>(nodePath[idx]);
					if(m_pPickedObject != NULL && m_pPickedObject->getIsTargetPick() != false) {
						break;
					}
				}

				if(idx >= 0)
					m_mtrxOriginalPosition = m_pPickedObject->getMatrix();
				else
					m_pPickedObject = NULL;

				return false;
				break;
			}
			else	{
				m_pPickedObject = NULL;

				return false;
				break;
			}
			break;
		}	//Case: Push_Left_Mouse_button
		else {
			m_pPickedObject = NULL;

			return false;
		}
	}	//Case: Push

	
	case(GUIEventAdapter::DRAG):	{
		if(m_pPickedObject==NULL)	{
			return false;
			break;
		}

		float dPositionX =	ea.getXnormalized() - m_dbMouseLastGetXNormalized; 
		float dPositionY =	ea.getYnormalized() - m_dbMouseLastGetYNormalized;

		if(fabs(dPositionX)<0.001 && fabs(dPositionY)<0.001)
			return false;

		Matrixd mat = viewer->getCameraManipulator()->getMatrix();
		Vec3d lookVector(mat(2,0),mat(2,1),mat(2,2));
	    Vec3d eyeVector(mat(3,0),mat(3,1),mat(3,2));
		float moveFactor = 0.3 * (lookVector - eyeVector).length();

		ObjectTransformation * pObjectTransformation = new ObjectTransformation();
		Matrix mtrx;

		//Does Up/down-left/right dragging respective to the axes
		if(m_nTransformSelection == enumObjectTransform(DEFAULT))	{
//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(DEFAULT))
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(moveFactor*(dPositionX), 0.0, moveFactor*(dPositionY));
		}

		//Does Up/down-left/right dragging irrespective of the axes
//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(LATERAL_VERTICAL_TO_MONITOR))
		if(m_nTransformSelection == enumObjectTransform(LATERAL_VERTICAL_TO_MONITOR))	{
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(	moveFactor*(dPositionX)*mat(0,0), 
													moveFactor*(dPositionX)*mat(0,1), 
													moveFactor*(dPositionY)
			);
		}

//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(LATERAL_MOVE))
		if(m_nTransformSelection == enumObjectTransform(LATERAL_MOVE))	{
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(moveFactor*(dPositionX), 0.0, 0.0);
		}

//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(VERTICAL_MOVE))
		if(m_nTransformSelection == enumObjectTransform(VERTICAL_MOVE))	{
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(0.0, 0.0, moveFactor*(dPositionY));
		}

//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(LONGITUDINAL_MOVE))
		if(m_nTransformSelection == enumObjectTransform(LONGITUDINAL_MOVE))	{
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(0.0, moveFactor*(dPositionY), 0.0);
		}


//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(ROTATION))
		if(m_nTransformSelection == enumObjectTransform(ROTATION))	{
			//Angles should be in radians
			double flRXAngle = 
				dPositionY
				//degrees2Radians(0.0)
				;
			double flRYAngle = 
				dPositionX
				//degrees2Radians(0.0)
				;
			double flRZAngle = 
				dPositionX
				//degrees2Radians(0.0)
				;

			mtrx = pObjectTransformation->rotation(flRZAngle,ObjectTransformationParams::m_enumRotation::ROTATION_ON_Z)
				//* pObjectTransformation->rotation(flRYAngle,ObjectTransformationParams::m_enumRotation::ROTATION_ON_Y)
				//* pObjectTransformation->rotation(flRXAngle,ObjectTransformationParams::m_enumRotation::ROTATION_ON_X)
				* m_mtrxOriginalPosition;

			//mtrx = m_mtrxOriginalPosition * X;	ROTATES AROUND THE SCENE'S ORIGIN (PRE-MULTIPLY)
			//mtrx = X * m_mtrxOriginalPosition;	ROTATES AROUND THE OBJECT'S ORIGIN (POST-MULTIPLY)
		}

//		if(ea.getModKeyMask()&GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(SCALING))	{
		if(m_nTransformSelection == enumObjectTransform(SCALING))	{
			mtrx = pObjectTransformation->scaling(moveFactor*(dPositionX), moveFactor*(dPositionX), moveFactor*(dPositionX)) 
				* m_mtrxOriginalPosition;
		}

		delete pObjectTransformation;

		m_pPickedObject->setMatrix(mtrx);
		
		viewer->setSceneData(m_pScene);

		return false;
		break;
										}

	case(GUIEventAdapter::RELEASE):	{
		m_nTransformSelection = enumObjectTransform(DEFAULT);

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
