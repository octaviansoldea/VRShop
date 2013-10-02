#ifndef SPLINE_WIDGET_H
#define SPLINE_WIDGET_H

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include "vtkImagePlaneWidget.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkKochanekSpline.h"
#include "vtkParametricSpline.h"
#include "vtkPlaneSource.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSplineWidget.h"
#include "vtkTextProperty.h"
#include "vtkSmartPointer.h"
#include "vtkSplineRepresentation.h"

#include <MyVTKCallback.h>
// Callback for the spline widget interaction
class vtkSplineWidgetCallback : public vtkCommand
{
public:
  static vtkSplineWidgetCallback *New()
    { return new vtkSplineWidgetCallback; }

  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkSplineWidget *spline = reinterpret_cast<vtkSplineWidget*>(caller);
      spline->GetPolyData(Poly);
    }
  vtkSplineWidgetCallback():Poly(0){};	// Initializes Poly
  vtkPolyData* Poly;
};


#endif	//SPLINE_WIDGET_H