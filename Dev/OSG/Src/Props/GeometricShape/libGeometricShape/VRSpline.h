#ifndef VR_SPLINE_H
#define VR_SPLINE_H

class ostream;

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
		virtual const char* className() const;

		virtual void print(std::ostream & os) const;
	};
}
#endif //VR_SPLINE_H
