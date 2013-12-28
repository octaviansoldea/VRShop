#ifndef OSG_PICK_AND_DRAG_HANDLER_H
#define OSG_PICK_AND_DRAG_HANDLER_H

#include <osg/MatrixTransform>
#include <osg/Group>
#include <osgViewer/Viewer>

#include <osgUtil/PolytopeIntersector>

#include <osgGA/GUIEventHandler>

namespace VR	{
	class PickAndDragHandler : public osgGA::GUIEventHandler	{
	public:
		PickAndDragHandler();
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

	private:
		osg::ref_ptr<osg::Group> pScene;
		osg::ref_ptr<osg::MatrixTransform> pPickedObject;

		osg::Matrixd m_mtrxOriginalPosition;
		osg::Matrixd m_mtrxMatrix;

		int m_nTransformSelection;

		double m_dbMouseLastGetXNormalized;
		double m_dbMouseLastGetYNormalized;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;
	};
}
#endif //OSG_PICK_AND_DRAG_HANDLER_H