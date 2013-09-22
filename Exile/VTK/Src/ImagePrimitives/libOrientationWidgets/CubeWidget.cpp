#include "vtkObjectFactory.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkSmartPointer.h"
#include "vtkMapper.h"
#include "vtkProperty.h"

#include "BasicVTKDefinitions.h"

#include "CubeWidget.h"

CubeWidget::CubeWidget()
{
  //m_pvtkAnnotatedCubeActor = vtkAnnotatedCubeActor::New();
  m_pvtkAnnotatedCubeActor = vtkSmartPointer < vtkAnnotatedCubeActor >::New();
  m_pvtkAnnotatedCubeActor->SetFaceTextScale( 0.65 );
  vtkProperty* pvtkProperty = m_pvtkAnnotatedCubeActor->GetCubeProperty();
  pvtkProperty->SetColor( 0.5, 1, 1 );

  pvtkProperty = m_pvtkAnnotatedCubeActor->GetTextEdgesProperty();
  pvtkProperty->SetLineWidth( 1 );
  pvtkProperty->SetDiffuse( 0 );
  pvtkProperty->SetAmbient( 1 );
  pvtkProperty->SetColor( 0.1800, 0.2800, 0.2300 );

  // this static function improves the appearance of the text edges
  // since they are overlaid on a surface rendering of the cube's faces
  //
  vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();

  m_pvtkAnnotatedCubeActor->SetXPlusFaceText ( "L" );
  m_pvtkAnnotatedCubeActor->SetXMinusFaceText( "R" );
  m_pvtkAnnotatedCubeActor->SetYPlusFaceText ( "P" );
  m_pvtkAnnotatedCubeActor->SetYMinusFaceText( "A" );
  m_pvtkAnnotatedCubeActor->SetZPlusFaceText ( "S" );
  m_pvtkAnnotatedCubeActor->SetZFaceTextRotation(+90);
  m_pvtkAnnotatedCubeActor->SetZMinusFaceText( "I" );
  
  pvtkProperty = m_pvtkAnnotatedCubeActor->GetXPlusFaceProperty();
  pvtkProperty->SetColor(1, 0, 0);
  pvtkProperty->SetInterpolationToFlat();
  pvtkProperty = m_pvtkAnnotatedCubeActor->GetXMinusFaceProperty();
  pvtkProperty->SetColor(1, 0, 0);
  pvtkProperty->SetInterpolationToFlat();
  pvtkProperty = m_pvtkAnnotatedCubeActor->GetYPlusFaceProperty();
  pvtkProperty->SetColor(0, 1, 0);
  pvtkProperty->SetInterpolationToFlat();
  pvtkProperty = m_pvtkAnnotatedCubeActor->GetYMinusFaceProperty();
  pvtkProperty->SetColor(0, 1, 0);
  pvtkProperty->SetInterpolationToFlat();
  pvtkProperty = m_pvtkAnnotatedCubeActor->GetZPlusFaceProperty();
  pvtkProperty->SetColor(0, 0, 1);
  pvtkProperty->SetInterpolationToFlat();
  pvtkProperty = m_pvtkAnnotatedCubeActor->GetZMinusFaceProperty();
  pvtkProperty->SetColor(0, 0, 1);
  pvtkProperty->SetInterpolationToFlat();

  m_pvtkOrientationMarkerWidget = vtkSmartPointer < vtkOrientationMarkerWidget >::New();
  m_pvtkOrientationMarkerWidget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
  m_pvtkOrientationMarkerWidget->SetOrientationMarker( m_pvtkAnnotatedCubeActor );
  m_pvtkOrientationMarkerWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
  //This code is kept here in comments in order to remember it was necessary in a
  //trial phase
  //m_pvtkOrientationMarkerWidget->SetEnabled( 1 );
  //m_pvtkOrientationMarkerWidget->InteractiveOff();
  //m_pvtkOrientationMarkerWidget->InteractiveOn();
}

//void CubeWidget::Delete() {
//  VTK_DELETE_NULL(m_pvtkAnnotatedCubeActor);
//  VTK_DELETE_NULL(m_pvtkOrientationMarkerWidget);
//}

//CubeWidget::~CubeWidget() {
//	Delete();
//}

vtkStandardNewMacro(CubeWidget);

void CubeWidget::VisibilityOn() {
	m_pvtkAnnotatedCubeActor->VisibilityOn();
}

void CubeWidget::VisibilityOff() {
	m_pvtkAnnotatedCubeActor->VisibilityOff();
}

int CubeWidget::GetVisibility() {
	return(m_pvtkAnnotatedCubeActor->GetVisibility());
}

void CubeWidget::SetVisibility(int anVisible) {
	m_pvtkAnnotatedCubeActor->SetVisibility(anVisible);
}

vtkOrientationMarkerWidget * CubeWidget::GetOrientationMarkerWidget() {
	return(m_pvtkOrientationMarkerWidget);
}