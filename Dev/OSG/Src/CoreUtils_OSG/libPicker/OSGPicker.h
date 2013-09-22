#ifndef OSG_PICKER_H
#define OSG_PICKER_H

#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/NodeCallback>

#include <osgGA/GUIEventHandler>

namespace VR	{
	class PickHandler : public osgGA::GUIEventHandler	{
	public:
		PickHandler();
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

	private:
		osg::Group * pScene;

		osg::Node * pPickedObject;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;
	};
}
#endif //OSG_PICKER_H