#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkSmartPointer.h"

#include "BasicVTKDefinitions.h"
#include "RenWin.h"

RenWin::RenWin() {
	//Constructor initializes and sets a render window a renderer and an interactor
	m_pRenderer3D = vtkSmartPointer< vtkRenderer >::New();
	m_pRenWin3D = vtkSmartPointer< vtkRenderWindow >::New();
	m_pRenWin3D->AddRenderer(m_pRenderer3D);
	m_pIren3D = 0;

	m_pCamera = m_pRenderer3D->GetActiveCamera();
	double arrdbPosition[3] = {10.0, 2.0, 10.0};
	m_pCamera->SetPosition(arrdbPosition);
	m_pRenderer3D->ResetCameraClippingRange();
	m_pRenWin3D->Render();
}

RenWin::~RenWin() {
}