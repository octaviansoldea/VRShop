#include <osgUtil/PolytopeIntersector>
#include <osg/PolygonMode>

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
	m_bScale = false;
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
		case 'h': case 'H':
			m_bLateralMove = true;
			break;

		case 'v': case 'V':
			m_bVerticalMove = true;
			break;

		case 'l': case 'L':
			m_bLongitudinalMove = true;
			break;

		case 'r': case 'R':
			m_bRotate = true;
			break;

		case 's': case 'S':
			m_bScale = true;
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
					pPickedObject->addChild(createBoundingBox(picker->getFirstIntersection().drawable->getBound()));

					int nI;
					for(nI = 0; nI < node->getNumParents();nI++)	{
						pScene->removeChild(node->getParent(nI));
					}

					pScene->addChild(pPickedObject);

					return false;
					break;
				}
			}
			else	{
				pPickedObject = new osg::MatrixTransform;
				pPickedObject = NULL;
				return false;
				break;
			}
															}	//Case: Push_Left_Mouse_button
		default :
			return false;
		}
										}	//Case: Push

	
	case(osgGA::GUIEventAdapter::DRAG):	{
		if(pPickedObject==NULL)	{
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

		if (m_bScale)	{
			osg::Matrixd scale;
			scale = osg::Matrix::scale(
				(1.0 + 0.01*(dPositionX))>0 ? 1.0 + 0.01*(dPositionX) : 0.001,
				(1.0 + 0.01*(dPositionX))>0 ? 1.0 + 0.01*(dPositionX) : 0.001,
				(1.0 + 0.01*(dPositionX))>0 ? 1.0 + 0.01*(dPositionX) : 0.001);
			mtrx = scale
				* m_mtrxOriginalPosition;
		}

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
		m_bScale = false;

		//Remove bounding box - bounding box is put as a last child
		if(pPickedObject!=NULL)
			pPickedObject->removeChild(pPickedObject->getNumChildren()-1);

		return false;
		break;
										}
	}
	return false;
}

//---------------------------------------------------------------------------------------

osg::ref_ptr<osg::Node> PickAndDragHandler::createBoundingBox(osg::BoundingBox aBoundingBox)	{

	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array(10);
	(*points)[0].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMin());
	(*points)[1].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMax());
	(*points)[2].set(aBoundingBox.xMax(), aBoundingBox.yMin(), aBoundingBox.zMin());
	(*points)[3].set(aBoundingBox.xMax(), aBoundingBox.yMin(), aBoundingBox.zMax());
	(*points)[4].set(aBoundingBox.xMax(), aBoundingBox.yMax(), aBoundingBox.zMin());
	(*points)[5].set(aBoundingBox.xMax(), aBoundingBox.yMax(), aBoundingBox.zMax());
	(*points)[6].set(aBoundingBox.xMin(), aBoundingBox.yMax(), aBoundingBox.zMin());
	(*points)[7].set(aBoundingBox.xMin(), aBoundingBox.yMax(), aBoundingBox.zMax());
	(*points)[8].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMin());
	(*points)[9].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMax());

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray( points );
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, 10));

	//Send geometry to Geode and set StateSet
	osg::ref_ptr<osg::Geode> bbGeode = new osg::Geode;
	bbGeode->addDrawable( geom.get() );
	osg::StateSet* ss = bbGeode->getOrCreateStateSet();
	ss->setAttributeAndModes( new osg::PolygonMode(  osg::PolygonMode::FRONT_AND_BACK,  osg::PolygonMode::LINE ) );
	ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF );  

	return bbGeode;
}