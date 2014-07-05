#ifndef VR_FLOOR_H
#define VR_FLOOR_H

#include <osg/Geode>
#include <osg/Geometry>

namespace VR	{
		struct FloorParams	{
			osg::Vec3d m_vec3dBottomLeft;
			osg::Vec3d m_vec3dUpRight;
			std::string m_strTextureName;

			FloorParams();
		};

	class Floor	{
	public:
		Floor();
		Floor(const FloorParams & aFloorParams);

		virtual const char* className() const;

		osg::Node * createFloor();

	private:
		FloorParams m_FloorParams;

		osg::ref_ptr<osg::Geometry> setGeometry();
	};
}
#endif //VR_FLOOR_H