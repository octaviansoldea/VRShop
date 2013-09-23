#include <osgUtil/PolytopeIntersector>

#include <iostream>

#include "OSGPicker.h"

using namespace VR;

PickAndDragHandler::PickAndDragHandler()	{
	m_dbMouseLastGetX = 0;
	m_dbMouseLastGetY = 0;

	m_bLateralMove = false;
	m_bLongitudinalMove = false;
	m_bVerticalMove = false;
	m_bRotate = false;
}

//------------------------------------------------------------------------------

bool PickAndDragHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )	{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	pScene = dynamic_cast<osg::Group*>(viewer->getSceneData());

	switch (ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):	{
		switch(ea.getKey())
		{
		case 'h':
			m_bLateralMove = true;
			break;

		case 'v':
			m_bVerticalMove = true;
			break;

		case 'l':
			m_bLongitudinalMove = true;
			break;

		case 'r':
			m_bRotate = true;
			break;

		default:
			break;
		}
											}	//Case: Keydown

	case(osgGA::GUIEventAdapter::PUSH):	{
		switch(ea.getButton())
		{
		case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON :	{
			double margin = 0.01;

			osgUtil::PolytopeIntersector* picker = new osgUtil::PolytopeIntersector( 
				osgUtil::Intersector::PROJECTION, ea.getXnormalized()-margin, ea.getYnormalized()-margin, 
				ea.getXnormalized()+margin, ea.getYnormalized()+margin );

			osgUtil::IntersectionVisitor iv(picker);
			viewer->getCamera()->accept(iv);

			if (picker->containsIntersections())	{

				m_dbMouseLastGetX = ea.getX();
				m_dbMouseLastGetY = ea.getY();

				osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;

				unsigned int idx=nodePath.size();
				while(idx--)	{
					osg::Node *node = dynamic_cast<osg::Node*>(nodePath[idx]);
					if(node == NULL)
						continue;
				
					m_mtrxOriginalPosition = osg::computeLocalToWorld(nodePath);

					pPickedObject = new osg::MatrixTransform;
					pPickedObject->setMatrix(m_mtrxOriginalPosition);

					pPickedObject->addChild(node);

					int nI;
					for(nI = 0; nI < node->getNumParents();nI++)	{
						pScene->removeChild(node->getParent(nI));
					}

					pScene->addChild(pPickedObject);

					return false;
					break;
				}
			}
															}	//Case: Push_Left_Mouse_button
		default :
			return false;
		}
										}	//Case: Push

	
	case(osgGA::GUIEventAdapter::DRAG):	{
		if(pPickedObject==NULL)	{
			std::cout << "Error Drag" << std::endl;
			return true;
			break;
		}

		double dPositionX =	ea.getX() - m_dbMouseLastGetX; 
		double dPositionY =	ea.getY() - m_dbMouseLastGetY;

		if(fabs(dPositionX)<0.01 && fabs(dPositionY)<0.01)
			return false;

		osg::Matrix mtrx;
		if (!m_bLateralMove && !m_bLongitudinalMove && !m_bVerticalMove)
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.1*(dPositionX),
				0.0,
				0.1*(dPositionY));

		if (m_bLateralMove)
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.1*(dPositionX),
				0.0,
				0.0);

		if (m_bVerticalMove)
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.0,
				0.0,
				0.1*(dPositionY));

		if (m_bLongitudinalMove)
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.0,
				0.1*(dPositionY),
				0.0);

		if (m_bRotate)
			mtrx = osg::Matrix::rotate(dPositionX*0.01, osg::Z_AXIS) * m_mtrxOriginalPosition;

		pPickedObject->setMatrix(mtrx);
		
		viewer->setSceneData(pScene);
		viewer->updateTraversal();

		return false;
		break;
										}

	case(osgGA::GUIEventAdapter::RELEASE):	{
		m_bLateralMove = false;
		m_bLongitudinalMove = false;
		m_bVerticalMove = false;
		m_bRotate = false;

		return false;
		break;	
										}
	}
	return false;
}

//---------------------------------------------------------------------------------------

