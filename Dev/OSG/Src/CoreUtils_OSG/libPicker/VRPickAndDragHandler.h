#ifndef OSG_PICK_AND_DRAG_HANDLER_H
#define OSG_PICK_AND_DRAG_HANDLER_H

#include <osgGA/GUIEventHandler>
#include "VRAbstractObject.h"


namespace osgViewer { class Viewer; };

class osg::Group;
class ObjectTransformation;

namespace VR {
	class PickAndDragHandler : public osgGA::GUIEventHandler {
	public:
		PickAndDragHandler();

		static void PrintMatrix(const osg::Matrix & aMtrx, const std::string & astrTitle);

		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
		osg::ref_ptr<AbstractObject> m_pPickedObject;

	private:
		typedef struct {
			int m_nButton;
			float m_flXNormalized;
			float m_flYNormalized;
		} MouseSignals;
		static void getMouseSignals(MouseSignals * apMouseSignals, const osgGA::GUIEventAdapter& ea);
		
		
		bool handleKeyDown(int anKey);
		bool handlePush(const MouseSignals & aMouseSignals, osgViewer::Viewer * apViewer);
		bool handleDrag(const MouseSignals & aMouseSignals, osgViewer::Viewer * apViewer);
		
		osg::ref_ptr<osg::Group> m_pScene;

		osg::Matrix m_mtrxPickedObject;

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
	};
}
#endif //OSG_PICK_AND_DRAG_HANDLER_H