//Pressing "H": make lateral movement
//Pressing "V": make vertical movement
//Pressing "L": make longitudial movement
//Pressing "R": make rotation
//Pressing "S": make scalling
//Pressing "1": make 45oC camera!! rotation
//Pressing "SHIFT L or R": make movement Up/down-Left/right irrespective of axes

#include <osgUtil/PolytopeIntersector>
#include <osg/PolygonMode>
#include <osg/ComputeBoundsVisitor>

#include <iostream>

#include "BaseModel.h"
#include "OSGPicker.h"

using namespace VR;

PickAndDragHandler::PickAndDragHandler()	{
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

	pScene = dynamic_cast<osg::Group*>(viewer->getSceneData());
	
	switch (ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN): {
		switch(ea.getKey())
		{
		case 'h': case 'H':
			m_nTransformSelection = enumObjectTransform(LateralMove);
			std::cout << "H" << std::endl;
			break;

		case 'v': case 'V':
			m_nTransformSelection = enumObjectTransform(VerticalMove);
			break;

		case 'l': case 'L':
			m_nTransformSelection = enumObjectTransform(LongitudinalMove);
			break;

		case 'r': case 'R':
			m_nTransformSelection = enumObjectTransform(Rotation);
			break;

		case 's': case 'S':
			m_nTransformSelection = enumObjectTransform(Scaling);
			break;

		case osgGA::GUIEventAdapter::KEY_Shift_L:
		case osgGA::GUIEventAdapter::KEY_Shift_R:
			m_nTransformSelection = enumObjectTransform(LateralVerticalToMonitor);
			break;


		default:
			m_nTransformSelection = enumObjectTransform(Default);
			break;
		}
	}	//Case: Keydown

	case(osgGA::GUIEventAdapter::PUSH):	{
		int nButton = ea.getButton();
		if(nButton == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
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

				int idx;
				for(idx=nodePath.size()-1; idx>=0; idx--) {
					BaseModel *pModel = dynamic_cast<BaseModel*>(nodePath[idx]);
					if(pModel != NULL && pModel->getIsTargetPick() != false) {
						break;
					}
				}

				if(idx >= 0)	{
					osg::Node *node = dynamic_cast<osg::Node*>(nodePath[idx]);
					
					m_mtrxOriginalPosition = osg::computeLocalToWorld(nodePath);
					pPickedObject = new osg::MatrixTransform;
					pPickedObject->setMatrix(m_mtrxOriginalPosition);

					pPickedObject->addChild(node);
					pPickedObject->addChild(createBoundingBox(*node));

					int nI;
					for(nI = 0; nI < node->getNumParents();nI++)	{
						pScene->removeChild(node->getParent(nI));
					}
					pScene->removeChild(node);

					pScene->addChild(pPickedObject);

					return false;
					break;
				}
				else	{
					pPickedObject = new osg::MatrixTransform;
					pPickedObject = NULL;
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
			break;
		}	//Case: Push_Left_Mouse_button
		else {
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

		osg::Matrixd mat = viewer->getCameraManipulator()->getMatrix();

		osg::Matrix mtrx;
		//Does Up/down-left/right dragging respective to the axes
		if(m_nTransformSelection == enumObjectTransform(Default))
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.1*(dPositionX), 0.0, 0.1*(dPositionY));

		//Does Up/down-left/right dragging irrespective of the axes
		if(m_nTransformSelection == enumObjectTransform(LateralVerticalToMonitor))
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.1*(dPositionX)*mat(0,0), 0.1*(dPositionX)*mat(0,1), 0.1*(dPositionY));

		if(m_nTransformSelection == enumObjectTransform(LateralMove))
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.1*(dPositionX),
				0.0,
				0.0);

		if(m_nTransformSelection == enumObjectTransform(VerticalMove))
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.0,
				0.0,
				0.1*(dPositionY));

		if(m_nTransformSelection == enumObjectTransform(LongitudinalMove))
			mtrx = m_mtrxOriginalPosition * osg::Matrix::translate(
				0.0,
				0.1*(dPositionY),
				0.0);

		if(m_nTransformSelection == enumObjectTransform(Rotation))
			mtrx = osg::Matrix::rotate(dPositionX*0.01, osg::Z_AXIS) * m_mtrxOriginalPosition;

		if(m_nTransformSelection == enumObjectTransform(Scaling))	{
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

		return false;
		break;
										}

	case(osgGA::GUIEventAdapter::RELEASE):	{
		m_nTransformSelection = enumObjectTransform(Default);

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

osg::ref_ptr<osg::Node> PickAndDragHandler::createBoundingBox(osg::Node & aNode)	{

	osg::ref_ptr<osg::ComputeBoundsVisitor> cbv = new osg::ComputeBoundsVisitor();
	aNode.accept(*cbv);

	osg::BoundingBox boundingBox = cbv->getBoundingBox();

	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array(10);
	(*points)[0].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMin());
	(*points)[1].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMax());
	(*points)[2].set(boundingBox.xMax(), boundingBox.yMin(), boundingBox.zMin());
	(*points)[3].set(boundingBox.xMax(), boundingBox.yMin(), boundingBox.zMax());
	(*points)[4].set(boundingBox.xMax(), boundingBox.yMax(), boundingBox.zMin());
	(*points)[5].set(boundingBox.xMax(), boundingBox.yMax(), boundingBox.zMax());
	(*points)[6].set(boundingBox.xMin(), boundingBox.yMax(), boundingBox.zMin());
	(*points)[7].set(boundingBox.xMin(), boundingBox.yMax(), boundingBox.zMax());
	(*points)[8].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMin());
	(*points)[9].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMax());

	//Set color of the bounding box
	osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
	color->push_back(osg::Vec4(1,1,1,1));

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(points);
	geom->setColorArray(color.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, 10));	

	//Send geometry to Geode and set StateSet
	osg::ref_ptr<osg::Geode> bbGeode = new osg::Geode;
	bbGeode->addDrawable(geom.get());
	osg::StateSet* ss = bbGeode->getOrCreateStateSet();
	ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));

	return bbGeode;
}