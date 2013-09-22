#include <osgUtil/PolytopeIntersector>
#include <osg/Camera>

#include <iostream>

#include "OSGPicker.h"

using namespace VR;

PickHandler::PickHandler()	{
}

//------------------------------------------------------------------------------

bool PickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )	{
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error" << std::endl;
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

				osg::NodePath& nodePath = picker->getFirstIntersection().nodePath;

				unsigned int idx=nodePath.size();   
		        while(idx--)	{
					pPickedObject = dynamic_cast<osg::Node*>(nodePath[idx]);
					if(pPickedObject == NULL)
						continue;

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
			std::cout << "Error" << std::endl;
			return true;
			break;
		}

		double dPositionX =	ea.getX() - m_dbMouseLastGetX;
		double dPositionY =	ea.getY() - m_dbMouseLastGetY;

		if(dPositionX==0 && dPositionY==0)
			break;

		osg::Matrixd matInv = viewer->getCamera()->getInverseViewMatrix();

		osg::MatrixTransform* mtrxT = new osg::MatrixTransform;
		osg::Matrix mtrx = osg::Matrix::translate(dPositionX*0.1,0.0,dPositionY*0.1);

		pPickedObject->dirtyBound();

		mtrxT->setMatrix(mtrx);
		mtrxT->addChild(pPickedObject);

		osg::Node::ParentList parentList=pPickedObject->getParents();
		int nI;
		for(nI = 0; nI < pPickedObject->getNumParents();nI++)	{
			pScene->removeChild(pPickedObject->getParent(nI));
		}
		pScene->addChild(mtrxT);
		viewer->setSceneData(pScene);

		return true;
		break;
										}

	case(osgGA::GUIEventAdapter::RELEASE):	{
		m_dbMouseLastGetX = 0;
		m_dbMouseLastGetY = 0;

		return false;
		break;
											}
	}
	return false;
}

//---------------------------------------------------------------------------------------
