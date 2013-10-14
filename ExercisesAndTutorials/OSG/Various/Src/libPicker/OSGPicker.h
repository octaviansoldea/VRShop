#ifndef OSG_PICK_AND_DRAG_HANDLER_H
#define OSG_PICK_AND_DRAG_HANDLER_H

#include <osg/MatrixTransform>
#include <osg/Group>
#include <osgViewer/Viewer>

#include <osgGA/GUIEventHandler>

namespace VR	{
	class PickAndDragHandler : public osgGA::GUIEventHandler	{
	public:
		PickAndDragHandler();
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

	private:
		osg::Group * pScene;

		osg::MatrixTransform * pPickedObject;
		osg::Matrixd m_mtrxOriginalPosition;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;

		int m_nTransformSelection;
	};
}
#endif //OSG_PICK_AND_DRAG_HANDLER_H