#ifndef VR_OBJECT_TRANSFORMATION_H
#define VR_OBJECT_TRANSFORMATION_H

#include <osg/Matrix>

namespace VR {
	typedef enum {
		ROTATION_ON_X = 0,
		ROTATION_ON_Y,
		ROTATION_ON_Z} ROTATION_TYPE;
	
	struct ObjectTransformationParams : public osg::Matrix {
		ObjectTransformationParams();
	};

	class ObjectTransformation {
		public:
			ObjectTransformation();

			osg::Matrix setTranslationGetMatrix(float aflX, float aflY, float aflZ);
			osg::Matrix setRotationGetMatrix(float aflAngle, ROTATION_TYPE aENUMRotationm);
			osg::Matrix setScalingGetMatrix(float aflX, float aflY, float aflZ);

		private:
			void init(const ObjectTransformationParams & aObjectTransformationParams);
			osg::Matrix getMatrix() const;

			ObjectTransformationParams m_ObjectTransformationParams;
	};
}
#endif //VR_OBJECT_TRANSFORMATION_H