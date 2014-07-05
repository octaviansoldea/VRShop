#ifndef VR_WALL_H
#define VR_WALL_H

#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>

#include <string>

namespace VR	{
	class Wall : public osg::MatrixTransform	{
	public:
		Wall();

		virtual const char* className() const;

		void createWall();

	private:
		osg::ref_ptr<osg::Geometry> createWallGeometry(osg::Vec3Array * apCoords, std::string& astrTextureName);

		struct MatrixTransformParams	{
			osg::Vec3 pos;
			osg::Vec3 scale;
			osg::Vec3 rotate;
			MatrixTransformParams();
		} mTParams;

		osg::Node* createMatrixTransform(osg::Geode* geode, MatrixTransformParams & mTParams);
	};
}
#endif //VR_WALL_H