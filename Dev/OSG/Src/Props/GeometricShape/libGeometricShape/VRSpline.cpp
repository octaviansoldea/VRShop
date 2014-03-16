#include <fstream>

#include "VRSpline.h"

using namespace VR;

SplineParams::SplineParams() {
}

//-----------------------------------------------------------------------

Spline::Spline(const SplineParams & aSplineParams)	{
	m_SplineParams = aSplineParams;
}

//----------------------------------------------------------

const char* Spline::className() const	{
	return "Spline";
}
