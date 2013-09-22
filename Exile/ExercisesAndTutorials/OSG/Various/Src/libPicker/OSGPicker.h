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

		osg::MatrixTransform * pPickedObject;

		double m_dbMouseLastGetX;
		double m_dbMouseLastGetY;

		double m_dbMouseLastClickGetX;
		double m_dbMouseLastClickGetY;

		double m_dbMouseLastReleaseGetX;
		double m_dbMouseLastReleaseGetY;

		osg::ref_ptr<osg::Node> createBoundingBox(osg::BoundingBox aBoundingBox);
	};
}
#endif //OSG_PICKER_H