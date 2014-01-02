#ifndef OSG_PICK_AND_DRAG_HANDLER_H
#define OSG_PICK_AND_DRAG_HANDLER_H

#include <osgGA/GUIEventHandler>

class osg::Group;
class AbstractObject;

namespace VR	{
	class PickAndDragHandler : public osgGA::GUIEventHandler	{
	public:
		PickAndDragHandler();

	private:
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

		osg::ref_ptr<osg::Group> m_pScene;
		osg::ref_ptr<AbstractObject> m_pPickedObject;

		osg::Matrixd m_mtrxPickedObject;

		typedef enum {
			TRANSLATE = 0, //t
			ROTATE, //r
			SCALE //s
		} BASIC_TRANSFORM;
		BASIC_TRANSFORM m_nCurrentBasicTransform;

		typedef enum {
			DISPLAY_PLANE = 0,
			VIEW_DIRECTION, 
			X_AXIS, //x
			Y_AXIS, //y
			Z_AXIS  //z
		} MODALITY_TRANSFORM;
		MODALITY_TRANSFORM m_nCurrentModalityTransform;

		//ENUM_OBJECT_TRANSFORM m_nTransformSelection;

		double m_dbMouseLastGetXNormalized;
		double m_dbMouseLastGetYNormalized;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;
	};
}
#endif //OSG_PICK_AND_DRAG_HANDLER_H