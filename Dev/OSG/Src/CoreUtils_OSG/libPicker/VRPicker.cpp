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

PickAndDragHandler::PickAndDragHandler()	{
	m_dbMouseLastGetXNormalized = 0;
	m_dbMouseLastGetYNormalized = 0;

	m_dbMouseLastGetX = 0;
	m_dbMouseLastGetY = 0;

	m_nTransformSelection = 0;
}

//------------------------------------------------------------------------------

bool PickAndDragHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )	{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	enum enumObjectTransform {Default = 0, LateralMove, VerticalMove, LongitudinalMove, Rotation, Scaling,
								LateralVerticalToMonitor};

	m_pScene = dynamic_cast<Group*>(viewer->getSceneData());

	switch (ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN): {
		switch(ea.getKey())
		{
		case 'h': case 'H':
			m_nTransformSelection = enumObjectTransform(LateralMove);
			return false;
			break;

		case 'v': case 'V':
			m_nTransformSelection = enumObjectTransform(VerticalMove);
			return false;
			break;

		case 'l': case 'L':
			m_nTransformSelection = enumObjectTransform(LongitudinalMove);
			return false;
			break;

		case 'r': case 'R':
			m_nTransformSelection = enumObjectTransform(Rotation);
			return false;
			break;

		case 's': case 'S':
			m_nTransformSelection = enumObjectTransform(Scaling);
			return false;
			break;

		case osgGA::GUIEventAdapter::KEY_Shift_L:
		case osgGA::GUIEventAdapter::KEY_Shift_R:
			m_nTransformSelection = enumObjectTransform(LateralVerticalToMonitor);
			return false;
			break;

		default:
			m_nTransformSelection = enumObjectTransform(Default);
			return false;
			break;
		}
	}	//Case: Keydown

	case(osgGA::GUIEventAdapter::PUSH):	{
		int nButton = ea.getButton();
		if(nButton == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
//		if(nButton == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT)	{
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

	
	case(osgGA::GUIEventAdapter::DRAG):	{
		if(m_pPickedObject==NULL)	{
			return false;
			break;
		}

		float dPositionX =	ea.getXnormalized() - m_dbMouseLastGetXNormalized; 
		float dPositionY =	ea.getYnormalized() - m_dbMouseLastGetYNormalized;

		if(fabs(dPositionX)<0.001 && fabs(dPositionY)<0.001)
			return false;

		osg::Matrixd mat = viewer->getCameraManipulator()->getMatrix();
		osg::Vec3d lookVector(mat(2,0),mat(2,1),mat(2,2));
	    osg::Vec3d eyeVector(mat(3,0),mat(3,1),mat(3,2));
		float moveFactor = 0.3 * (lookVector - eyeVector).length();

		ObjectTransformation * pObjectTransformation;
		osg::Matrix mtrx;

		//Does Up/down-left/right dragging respective to the axes
		if(m_nTransformSelection == enumObjectTransform(Default))	{
//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(Default))
			pObjectTransformation = new ObjectTransformation();
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(moveFactor*(dPositionX), 0.0, moveFactor*(dPositionY));
		}

		//Does Up/down-left/right dragging irrespective of the axes
//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(LateralVerticalToMonitor))
		if(m_nTransformSelection == enumObjectTransform(LateralVerticalToMonitor))	{
			pObjectTransformation = new ObjectTransformation();
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(	moveFactor*(dPositionX)*mat(0,0), 
													moveFactor*(dPositionX)*mat(0,1), 
													moveFactor*(dPositionY)
			);
		}

//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(LateralMove))
		if(m_nTransformSelection == enumObjectTransform(LateralMove))	{
			pObjectTransformation = new ObjectTransformation();
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(moveFactor*(dPositionX), 0.0, 0.0);
		}

//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(VerticalMove))
		if(m_nTransformSelection == enumObjectTransform(VerticalMove))	{
			pObjectTransformation = new ObjectTransformation();
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(0.0, 0.0, moveFactor*(dPositionY));
		}

//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(LongitudinalMove))
		if(m_nTransformSelection == enumObjectTransform(LongitudinalMove))	{
			pObjectTransformation = new ObjectTransformation();
			mtrx = m_mtrxOriginalPosition *
				pObjectTransformation->translation(0.0, moveFactor*(dPositionY), 0.0);
		}


//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(Rotation))
		if(m_nTransformSelection == enumObjectTransform(Rotation))	{
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

			pObjectTransformation = new ObjectTransformation();
			mtrx = pObjectTransformation->rotation(flRZAngle,ObjectTransformationParams::enumRotation::RotationOnZ)
				//* pObjectTransformation->rotation(flRYAngle,ObjectTransformationParams::enumRotation::RotationOnY)
				//* pObjectTransformation->rotation(flRXAngle,ObjectTransformationParams::enumRotation::RotationOnX)
				* m_mtrxOriginalPosition;

			//mtrx = m_mtrxOriginalPosition * X;	ROTATES AROUND THE SCENE'S ORIGIN (PRE-MULTIPLY)
			//mtrx = X * m_mtrxOriginalPosition;	ROTATES AROUND THE OBJECT'S ORIGIN (POST-MULTIPLY)
		}

//		if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT && m_nTransformSelection == enumObjectTransform(Scaling))	{
		if(m_nTransformSelection == enumObjectTransform(Scaling))	{
			pObjectTransformation = new ObjectTransformation();

			mtrx = pObjectTransformation->scaling(moveFactor*(dPositionX), moveFactor*(dPositionX), moveFactor*(dPositionX)) 
				* m_mtrxOriginalPosition;
		}

		delete pObjectTransformation;

		m_pPickedObject->setMatrix(mtrx);
		
		viewer->setSceneData(m_pScene);

		return false;
		break;
										}

	case(osgGA::GUIEventAdapter::RELEASE):	{
		m_nTransformSelection = enumObjectTransform(Default);

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
