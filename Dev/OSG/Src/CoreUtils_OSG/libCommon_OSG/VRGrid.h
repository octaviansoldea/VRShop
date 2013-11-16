#ifndef VR_GRID_H
#define VR_GRID_H

#include <osg/Group>
#include <osg/Geode>

namespace VR {
	struct GridParams	{
		int m_nResLat;
		int m_nResLong;
		float m_flSpacing;
		osg::Vec3d m_vec3dStartCenter;

		GridParams();
	};

	class Grid : public osg::Group	{
		public:
			Grid();
			Grid(const GridParams & aGridParams);

		private:
			void init(const GridParams & aGridParams);
			
	};
}
#endif //VR_GRID_H