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

		typedef enum  {
			MOVE_ON_XZ = 0,
			LATERAL_MOVE,
			VERTICAL_MOVE,
			LONGITUDINAL_MOVE,
			ROTATION,
			SCALING,
			LATERAL_VERTICAL_TO_MONITOR} ENUM_OBJECT_TRANSFORM;

		ENUM_OBJECT_TRANSFORM m_nTransformSelection;

		double m_dbMouseLastGetXNormalized;
		double m_dbMouseLastGetYNormalized;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;
	};
}
#endif //OSG_PICK_AND_DRAG_HANDLER_H