#ifndef VR_SPLINE_H
#define VR_SPLINE_H

namespace VR {
	struct SplineParams {
		SplineParams();
	};

	class Spline	{
	private:
		SplineParams m_SplineParams;
	public:
		Spline();
		Spline(const SplineParams & aSplineParams);
	};
}
#endif //VR_SPLINE_H
