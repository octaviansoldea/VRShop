#ifndef ORIENTATION_WIDGETS_H
#define ORIENTATION_WIDGETS_H

#include "vtkObject.h"
#include "vtkRenderWindowInteractor.h"

#include "CubeWidget.h"
#include "AxesWidget.h"

class OrientationWidgets  : public vtkObject {

	vtkSmartPointer < CubeWidget > m_pCube;
	vtkSmartPointer < AxesWidget > m_pAxes;

	OrientationWidgets();
public:
	static OrientationWidgets *New();

	void SetRenderingPipeline(vtkRenderWindowInteractor * apvtkRenderWindowInteractor);

	vtkSmartPointer < vtkAxesActor > GetAxesActor();
	void SetAxesVisibility(int anVisibility);
	void SetAxesLength(double adbVal);
};

#endif //ORIENTATION_WIDGETS_H