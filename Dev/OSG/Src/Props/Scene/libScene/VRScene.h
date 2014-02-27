#ifndef VR_SCENE_H
#define VR_SCENE_H

#include <osg/Group>

namespace VR	{
	class Scene : public osg::Group	{
	public:
		Scene();
		~Scene();

		void addElement(osg::ref_ptr<osg::Node> apElement);
		void removeElement(osg::ref_ptr<osg::Node> apElement);
		void clearScene();
	};
}
#endif //VR_SCENE_H