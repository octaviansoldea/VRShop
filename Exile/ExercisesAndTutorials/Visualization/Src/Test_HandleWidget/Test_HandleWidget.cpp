#include "HandleWidget.h"

#include <iostream>

using namespace std;

int main()	{
    vtkSmartPointer<vtkRenderer> m_pRen =
        vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> m_pRenWin =
        vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_pIren =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    // Create a handle widget
    vtkSmartPointer<vtkHandleWidget> handle = vtkSmartPointer<vtkHandleWidget>::New();
    handle->SetInteractor(m_pIren);
    handle->ManagesCursorOff();

    vtkHandleRepresentation* handleRepresentation =
        reinterpret_cast<vtkHandleRepresentation*>(handle->GetHandleRepresentation());

    // Create a callback interaction
    vtkSmartPointer<HandleWidget> widgetInteraction =
        vtkSmartPointer<HandleWidget>::New();
    handle->AddObserver( vtkCommand::InteractionEvent, widgetInteraction );

    m_pRenWin->AddRenderer(m_pRen);

    m_pRen->Render();
    m_pIren->SetRenderWindow(m_pRenWin);

    //render image
    m_pIren->Initialize();
    m_pRenWin->Render();
    handle->On();

    // Begin mouse interaction
    m_pIren->Start();

    return(0);
}
