#ifndef VR_OBJECT_TRANSFORMATION_H
#define VR_OBJECT_TRANSFORMATION_H

#include <osg/Matrix>

namespace VR {
	typedef enum {
		X_AXIS = 0,
		Y_AXIS,
		Z_AXIS} ROTATION_AXIS;
	
	class ObjectTransformation : public osg::Matrix	{
		public:
			ObjectTransformation();
			ObjectTransformation(const ObjectTransformation & aObjectTransformation);

			static osg::Matrix setTranslationGetMatrix(float aflX, float aflY, float aflZ);
			static osg::Matrix setRotationGetMatrix(float aflAngle, ROTATION_AXIS aAxis);
			static osg::Matrix setScalingGetMatrix(float aflX, float aflY, float aflZ);

			const osg::Matrix& getMatrix() const;
	};
}
#endif //VR_OBJECT_TRANSFORMATION_H