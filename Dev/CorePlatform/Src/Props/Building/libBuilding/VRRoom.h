#ifndef VR_ROOM_H
#define VR_ROOM_H

#include <osg/MatrixTransform>

namespace VR	{
	class Wall;
	class Floor;

	class Room : public osg::MatrixTransform	{
	public:
		Room();

		virtual const char* className() const;
	
		osg::ref_ptr<osg::Node> createRoom();
	};
}

#endif //VR_ROOM_H