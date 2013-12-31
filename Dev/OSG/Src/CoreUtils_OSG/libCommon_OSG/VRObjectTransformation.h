#ifndef VR_OBJECT_TRANSFORMATION_H
#define VR_OBJECT_TRANSFORMATION_H

#include <osg/Matrix>

namespace VR {
	struct ObjectTransformationParams	{
		float	m_flMatrix00, m_flMatrix01, m_flMatrix02, m_flMatrix03,
				m_flMatrix10, m_flMatrix11, m_flMatrix12, m_flMatrix13,
				m_flMatrix20, m_flMatrix21, m_flMatrix22, m_flMatrix23,
				m_flMatrix30, m_flMatrix31, m_flMatrix32, m_flMatrix33;

		enum m_enumRotation {DEFAULT = 0, ROTATION_ON_X, ROTATION_ON_Y, ROTATION_ON_Z};

		ObjectTransformationParams();
	};

	class ObjectTransformation	{
		public:
			ObjectTransformation();
			ObjectTransformation(const ObjectTransformationParams & aObjectTransformationParams);

			osg::Matrix translation(float aflTranslateX, float aflTranslateY, float aflTranslateZ);
			osg::Matrix rotation(float aflAngle, ObjectTransformationParams::m_enumRotation aenumRotationm);
			osg::Matrix scaling(float aflScaleX, float aflScaleY, float aflScaleZ);

		private:
			void init(const ObjectTransformationParams & aObjectTransformationParams);
			osg::Matrix getMatrix() const;

			ObjectTransformationParams m_ObjectTransformationParams;
	};
}
#endif //VR_OBJECT_TRANSFORMATION_H