#ifndef VR_LIGHTING_H
#define VR_LIGHTING_H

#include <QObject>
#include <osg/NodeCallback>
#include <osg/LightSource>
#include <osg/ref_ptr>

namespace VR	{
	class Lighting : public QObject {
		Q_OBJECT

	public:
		Lighting(QObject * apQObject = 0);

		static osg::ref_ptr<osg::LightSource> createLights();
	};


	class LightFollowsNodeCallback : public osg::NodeCallback	{
	public:
		LightFollowsNodeCallback(osg::Node * apNode);

		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

	private:
		osg::Node * m_pNode;
	};

}
#endif //VR_LIGHTING_H