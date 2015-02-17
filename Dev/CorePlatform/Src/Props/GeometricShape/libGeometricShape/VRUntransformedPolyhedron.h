#ifndef VR_UNTRANSFORMED_POLYHEDRON_H
#define VR_UNTRANSFORMED_POLYHEDRON_H

#include <osg/Group>

namespace VR {
	struct UntransformedPolyhedronParams	{
		float m_flRadius;
		float m_flHeight;
		int m_nResolution;

		UntransformedPolyhedronParams();
	};

	class UntransformedPolyhedron : public osg::Group {
	private:
		UntransformedPolyhedronParams m_UntransformedPolyhedronParams;

	public:
		UntransformedPolyhedron();
		UntransformedPolyhedron(const UntransformedPolyhedronParams & aUntransformedPolyhedronParams);

		enum PolyhedronSide {BOTTOM=0,UP,BELT,ALL};

		void setColor(const std::vector<float> & aarrflColor, const PolyhedronSide & aPolyhedronSide=PolyhedronSide::ALL);
		void setTexture(const std::string & astrFileName, const PolyhedronSide & aPolyhedronSide=PolyhedronSide::ALL);

		void setResolution(int anResolution);
		int getResolution() const;
		void init(const UntransformedPolyhedronParams & aUntransformedPolyhedronParams);
	};
}
#endif //VR_UNTRANSFORMED_POLYHEDRON_H