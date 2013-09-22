#include "vtkObjectFactory.h"
#include "vtkActor.h"
#include "vtkAxesActor.h"
#include "vtkCamera.h"
#include "vtkCaptionActor2D.h"
#include "vtkCellArray.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkMath.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPropAssembly.h"
#include "vtkPropCollection.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkRendererCollection.h"

#include "OrientationWidgets.h"

vtkStandardNewMacro(OrientationWidgets);

OrientationWidgets::OrientationWidgets() {
	m_pCube = vtkSmartPointer < CubeWidget >::New();
	m_pAxes = vtkSmartPointer < AxesWidget >::New();
}

void OrientationWidgets::SetRenderingPipeline(vtkRenderWindowInteractor * apvtkRenderWindowInteractor)
{

	m_pCube->GetOrientationMarkerWidget()->SetInteractor( apvtkRenderWindowInteractor );
	m_pCube->GetOrientationMarkerWidget()->SetEnabled( 1 );
	m_pCube->GetOrientationMarkerWidget()->InteractiveOff();
    m_pCube->GetOrientationMarkerWidget()->InteractiveOn();
	vtkRenderer * pvtkRenderer = apvtkRenderWindowInteractor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
	pvtkRenderer->AddActor(m_pAxes->GetAxesActor());

}

vtkSmartPointer < vtkAxesActor > OrientationWidgets::GetAxesActor() {
	return(m_pAxes->GetAxesActor());
}

void OrientationWidgets::SetAxesVisibility(int anVisibility) {
	m_pAxes->SetVisibility(anVisibility);
}

void OrientationWidgets::SetAxesLength(double adbVal) {
	m_pAxes->SetLengths(adbVal);
}