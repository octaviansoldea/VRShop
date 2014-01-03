#ifndef OSG_PICK_AND_DRAG_HANDLER_H
#define OSG_PICK_AND_DRAG_HANDLER_H

#include <osgGA/GUIEventHandler>

class osg::Group;
class AbstractObject;
class ObjectTransformation;

namespace VR	{
	class PickAndDragHandler : public osgGA::GUIEventHandler	{
	public:
		PickAndDragHandler();

		static void PrintMatrix(const osg::Matrix & aMtrx, const std::string & astrTitle);

	private:
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

		void handleTranslate();
		void handleRotate();
		void handleScale();

		osg::ref_ptr<osg::Group> m_pScene;
		osg::ref_ptr<AbstractObject> m_pPickedObject;

		osg::Matrix mtrxPickedObject;

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

		double m_dbMouseLastGetXNormalized;
		double m_dbMouseLastGetYNormalized;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;
	};
}
#endif //OSG_PICK_AND_DRAG_HANDLER_H