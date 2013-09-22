#include <osgUtil/PolytopeIntersector>
#include <osg/Camera>
#include <osg/PolygonMode>
#include <osg/Geode>

#include <iostream>

#include "OSGPicker.h"

using namespace VR;

PickHandler::PickHandler()	{
		m_dbMouseLastGetX = 0;
		m_dbMouseLastGetY = 0;

		m_dbMouseLastClickGetX = 0;
		m_dbMouseLastClickGetY = 0;

		m_dbMouseLastReleaseGetX = 0;
		m_dbMouseLastReleaseGetY = 0;
}

//------------------------------------------------------------------------------

bool PickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )	{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	pScene = dynamic_cast<osg::Group*>(viewer->getSceneData());

	switch (ea.getEventType())
	{
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

				m_dbMouseLastClickGetX = m_dbMouseLastGetX;
				m_dbMouseLastClickGetY = m_dbMouseLastGetY;

				osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;

				unsigned int idx=nodePath.size();
				while(idx--)	{
					osg::Node *node = dynamic_cast<osg::Node*>(nodePath[idx]);
					node->dirtyBound();
					if(node == NULL)
						continue;
				
					pPickedObject = new osg::MatrixTransform;

					{
						//Correction
						double dPositionX =	m_dbMouseLastGetX - m_dbMouseLastClickGetX 
							+ m_dbMouseLastReleaseGetX;
						double dPositionY =	m_dbMouseLastGetY - m_dbMouseLastClickGetY 
							+ m_dbMouseLastReleaseGetY;

						osg::Matrix mtrx = osg::Matrix::translate(dPositionX*0.1,0.0,dPositionY*0.1);
						pPickedObject->setMatrix(mtrx);
					}

					pPickedObject->addChild(node);

					int nI;
					for(nI = 0; nI < node->getNumParents();nI++)	{
						pScene->removeChild(node->getParent(nI));
					}

					pScene->addChild(pPickedObject);

					osg::BoundingBox bb = picker->getFirstIntersection().drawable->getBound();
					//					pScene->addChild(createBoundingBox(bb));

					return false;
					break;
				}
			}
															}
		default :
			return false;
		}
										}

	
	case(osgGA::GUIEventAdapter::DRAG):	{
		if(pPickedObject==NULL)	{
			std::cout << "Error Drag" << std::endl;
			return true;
			break;
		}

		m_dbMouseLastGetX = ea.getX();
		m_dbMouseLastGetY = ea.getY();

		double dPositionX =	m_dbMouseLastGetX - m_dbMouseLastClickGetX 
			+ m_dbMouseLastReleaseGetX;
		double dPositionY =	m_dbMouseLastGetY - m_dbMouseLastClickGetY 
			+ m_dbMouseLastReleaseGetY;
		
		if(fabs(dPositionX)<0.01 && fabs(dPositionY)<0.01)
			return false;

		osg::Matrix mtrx = osg::Matrix::translate(dPositionX*0.1,0.0,dPositionY*0.1);
		pPickedObject->setMatrix(mtrx);
		
		viewer->setSceneData(pScene);
		viewer->updateTraversal();

		return false;
		break;
										}

	case(osgGA::GUIEventAdapter::RELEASE):	{
		m_dbMouseLastGetX = ea.getX();
		m_dbMouseLastGetY = ea.getY();

		m_dbMouseLastReleaseGetX += m_dbMouseLastGetX - m_dbMouseLastClickGetX;
		m_dbMouseLastReleaseGetY += m_dbMouseLastGetY - m_dbMouseLastClickGetY;

		return false;
		break;	
										}
	}
	return false;
}

//---------------------------------------------------------------------------------------

osg::ref_ptr<osg::Node> PickHandler::createBoundingBox(osg::BoundingBox aBoundingBox)	{

	osg::ref_ptr<osg::Vec3Array> m_pPoints = new osg::Vec3Array(10);
	(*m_pPoints)[0].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMin());
	(*m_pPoints)[1].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMax());
	(*m_pPoints)[2].set(aBoundingBox.xMax(), aBoundingBox.yMin(), aBoundingBox.zMin());
	(*m_pPoints)[3].set(aBoundingBox.xMax(), aBoundingBox.yMin(), aBoundingBox.zMax());
	(*m_pPoints)[4].set(aBoundingBox.xMax(), aBoundingBox.yMax(), aBoundingBox.zMin());
	(*m_pPoints)[5].set(aBoundingBox.xMax(), aBoundingBox.yMax(), aBoundingBox.zMax());
	(*m_pPoints)[6].set(aBoundingBox.xMin(), aBoundingBox.yMax(), aBoundingBox.zMin());
	(*m_pPoints)[7].set(aBoundingBox.xMin(), aBoundingBox.yMax(), aBoundingBox.zMax());
	(*m_pPoints)[8].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMin());
	(*m_pPoints)[9].set(aBoundingBox.xMin(), aBoundingBox.yMin(), aBoundingBox.zMax());

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray( m_pPoints.get() );
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, 10));

	//Send geometry to Geode and set StateSet
	osg::ref_ptr<osg::Geode> bbGeode = new osg::Geode;
	bbGeode->addDrawable( geom.get() );
	osg::StateSet* ss = bbGeode->getOrCreateStateSet();
	ss->setAttributeAndModes( new osg::PolygonMode(  osg::PolygonMode::FRONT_AND_BACK,  osg::PolygonMode::LINE ) );
	ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF );  

	return bbGeode;
}