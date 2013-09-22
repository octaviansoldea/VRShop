#include "vtkActor.h"
#include "vtkAnnotatedCubeActor.h"
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

#include "OrientationWidgets.h"

int main( int argc, char *argv[] )
{
  vtkRenderer* renderer = vtkRenderer::New();
  vtkRenderWindow* renWin = vtkRenderWindow::New();
  renWin->AddRenderer( renderer );
  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
  vtkInteractorStyleTrackballCamera *style = 
		vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);
  iren->SetRenderWindow( renWin );

  vtkCamera* camera = renderer->GetActiveCamera();
  //camera->SetViewUp( 0, 0, 1 );
  //camera->SetFocalPoint( 0, 0, 0 );
  //camera->SetPosition( 4.5, 4.5, 2.5 );
  
  camera->SetViewUp( 0, 0, 1 );
  camera->SetFocalPoint( 0, 0, 0 );
  camera->SetPosition( 2, - 7, 2 );
  renderer->ResetCameraClippingRange();

  OrientationWidgets * pOrientationWidgets = OrientationWidgets::New();
  pOrientationWidgets->SetRenderingPipeline(iren);

  iren->Initialize();
  renWin->Render();
  iren->Start();

  pOrientationWidgets->Delete();

  renderer->Delete();
  renWin->Delete();
  style->Delete();
  iren->Delete();

  return(0);
}


int main_( int argc, char *argv[] )
{
  vtkRenderer* renderer = vtkRenderer::New();
  vtkRenderWindow* renWin = vtkRenderWindow::New();
  renWin->AddRenderer( renderer );
  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
  vtkInteractorStyleTrackballCamera *style = 
		vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);
  iren->SetRenderWindow( renWin );

  vtkAnnotatedCubeActor* cube = vtkAnnotatedCubeActor::New();
  cube->SetFaceTextScale( 0.65 );
  vtkProperty* property = cube->GetCubeProperty();
  property->SetColor( 0.5, 1, 1 );

  property = cube->GetTextEdgesProperty();
  property->SetLineWidth( 1 );
  property->SetDiffuse( 0 );
  property->SetAmbient( 1 );
  property->SetColor( 0.1800, 0.2800, 0.2300 );

  // this static function improves the appearance of the text edges
  // since they are overlaid on a surface rendering of the cube's faces
  //
  vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();

  cube->SetXPlusFaceText ( "L" );
  cube->SetXMinusFaceText( "R" );
  cube->SetYPlusFaceText ( "P" );
  cube->SetYMinusFaceText( "A" );
  cube->SetZPlusFaceText ( "S" );
  cube->SetZFaceTextRotation(+90);
  cube->SetZMinusFaceText( "I" );
  
  property = cube->GetXPlusFaceProperty();
  property->SetColor(0, 0, 1);
  property->SetInterpolationToFlat();
  property = cube->GetXMinusFaceProperty();
  property->SetColor(0, 0, 1);
  property->SetInterpolationToFlat();
  property = cube->GetYPlusFaceProperty();
  property->SetColor(0, 1, 0);
  property->SetInterpolationToFlat();
  property = cube->GetYMinusFaceProperty();
  property->SetColor(0, 1, 0);
  property->SetInterpolationToFlat();
  property = cube->GetZPlusFaceProperty();
  property->SetColor(1, 0, 0);
  property->SetInterpolationToFlat();
  property = cube->GetZMinusFaceProperty();
  property->SetColor(1, 0, 0);
  property->SetInterpolationToFlat();

  vtkAxesActor* axes = vtkAxesActor::New();

  axes->SetShaftTypeToCylinder();
  axes->SetXAxisLabelText( "x" );
  axes->SetYAxisLabelText( "y" );
  axes->SetZAxisLabelText( "z" );

  axes->SetTotalLength( 1.5, 1.5, 1.5 );
  axes->SetCylinderRadius( 0.500 * axes->GetCylinderRadius() );
  axes->SetConeRadius    ( 1.025 * axes->GetConeRadius() );
  axes->SetSphereRadius  ( 1.500 * axes->GetSphereRadius() );

  vtkTextProperty* tprop = axes->GetXAxisCaptionActor2D()->
    GetCaptionTextProperty();
  tprop->ItalicOn();
  tprop->ShadowOn();
  tprop->SetFontFamilyToTimes();

  axes->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  axes->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );

	
  vtkOrientationMarkerWidget* widget = vtkOrientationMarkerWidget::New();
  widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
  widget->SetOrientationMarker( cube );
  widget->SetInteractor( iren );
  widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
  widget->SetEnabled( 1 );
  widget->InteractiveOff();
  widget->InteractiveOn();


  renderer->AddActor(axes);
  iren->Initialize();
  renWin->Render();
  iren->Start();

  cube->Delete();
  axes->Delete();
  widget->Delete();

  renderer->Delete();
  renWin->Delete();
  style->Delete();
  iren->Delete();

  return(0);
}
