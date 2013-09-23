#ifndef OSG_PICKER_AND_DRAG_HANDLER_H
#define OSG_PICKER_AND_DRAG_HANDLER_H

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

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;

		osg::Matrixd m_mtrxOriginalPosition;

		//Bools
		//Pressing "H": make lateral movement
		//Pressing "V": make vertical movement
		//Pressing "L": make longitudial movement
		bool m_bLateralMove;
		bool m_bLongitudinalMove;
		bool m_bVerticalMove;
		bool m_bRotate;
	};
}
#endif //OSG_PICKER_AND_DRAG_HANDLER_H