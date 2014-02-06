#include "VRSpline.h"

using namespace VR;

SplineParams::SplineParams() {
}

//-----------------------------------------------------------------------

Spline::Spline()	{
}

//----------------------------------------------------------

Spline::Spline(const SplineParams & aSplineParams)	{
	m_SplineParams = aSplineParams;
}

//----------------------------------------------------------