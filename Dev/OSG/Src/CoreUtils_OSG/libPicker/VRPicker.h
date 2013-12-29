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