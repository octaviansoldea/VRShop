#ifndef VR_ABSTRACT_OBJECT_FACTORY_H
#define VR_ABSTRACT_OBJECT_FACTORY_H

#include <string>
#include <osg/ref_ptr>

namespace VR	{
	class AbstractObject;
	
	class AbstractObjectFactory	{
	public:
		AbstractObjectFactory();
		~AbstractObjectFactory();

		static osg::ref_ptr<AbstractObject> createAbstractObject(const std::string & astrClassName);
	};
}
#endif //VR_ABSTRACT_OBJECT_FACTORY_H