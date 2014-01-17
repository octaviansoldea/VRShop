#ifndef VR_AVATAR_H
#define VR_AVATAR_H

#include <osg/MatrixTransform>

namespace VR {
	class Avatar : public osg::MatrixTransform	{
	public:
		Avatar();

		/*void wearTrousers();
		void wearShirt();
		void wearShoes();
		void wearHat();*/

		void beginMoveOrRun();
		void endMoveOrRun();
		void step();

		/*void sitDown();
		void walkUp();*/

		void animatePick();

	protected:
		typedef enum STATUS {
			SITTING,
			STANDING,
			WALKING,
			RUNNING,
			OTHER
		};

		STATUS m_Status;
		osg::Vec3d m_vec3dLocation;
		osg::Vec3d m_vec3dOrientationBody;
		osg::Vec3d m_vec3dOrientationHead;

		double m_Height;
		bool m_IsFemale;
		bool isChild;
	};
}
#endif //VR_AVATAR_H