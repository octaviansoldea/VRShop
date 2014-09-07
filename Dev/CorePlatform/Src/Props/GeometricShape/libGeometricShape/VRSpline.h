#ifndef VR_SPLINE_H
#define VR_SPLINE_H

namespace VR {
	struct SplineParams {
		SplineParams();
	};

	class Spline 	{
	private:
		SplineParams m_SplineParams;
	public:
		Spline(const SplineParams & aSplineParams);

		const char* className() const;
	};
}
#endif //VR_SPLINE_H
