#include "SphereWidget.h"

#include "ui_SelectTwoPointsGUI.h"
#include "SelectTwoPointsGUI.h"


extern SelectTwoPointsGUI * pSelectTwoPointsGUI;

using namespace std;

void vtkSphereCallback::Execute(vtkObject *caller, unsigned long, void*)
    {
    vtkSphereWidget2 *sphereWidget = 
      reinterpret_cast<vtkSphereWidget2*>(caller);
 
    double center[3], handlePosition[3];
    vtkSphereRepresentation* sphereRepresentation = 
      vtkSphereRepresentation::SafeDownCast( sphereWidget->GetRepresentation() );
    sphereRepresentation->GetHandlePosition( handlePosition );
    sphereRepresentation->GetSphere( this->Sphere );
 
    this->Sphere->GetCenter( center );
	double dbRadius = this->Sphere->GetRadius();
 
   
    std::cout << "SphereCenter: "
			  << center[0] << ", "
			  << center[1] << ", "
			  << center[2] << " "
              << std::endl;
		
	double dbRadiuses = pSelectTwoPointsGUI->m_pDoubleSpinBoxRadiuses->value();

 //   ///////////////////////////

	vtkSphereRepresentation* sphereRepresentation1 =  pSelectTwoPointsGUI->m_SelectTwoPoints.m_pSphereRepresentation1;
	vtkSphereRepresentation* sphereRepresentation2 =  pSelectTwoPointsGUI->m_SelectTwoPoints.m_pSphereRepresentation2;

	if(sphereRepresentation == sphereRepresentation1){
		
		pSelectTwoPointsGUI->m_pDoubleSpinBoxP1X->setValue(center[0]);
		pSelectTwoPointsGUI->m_pDoubleSpinBoxP1Y->setValue(center[1]);
		pSelectTwoPointsGUI->m_pDoubleSpinBoxP1Z->setValue(center[2]);
		pSelectTwoPointsGUI->m_pDoubleSpinBoxRadiuses->setValue(dbRadius);
		sphereRepresentation->SetRadius(dbRadiuses);
	}

	if(sphereRepresentation == sphereRepresentation2){
		
		pSelectTwoPointsGUI->m_pDoubleSpinBoxP2X->setValue(center[0]);
		pSelectTwoPointsGUI->m_pDoubleSpinBoxP2Y->setValue(center[1]);
		pSelectTwoPointsGUI->m_pDoubleSpinBoxP2Z->setValue(center[2]);
		pSelectTwoPointsGUI->m_pDoubleSpinBoxRadiuses->setValue(dbRadius);
		sphereRepresentation->SetRadius(dbRadiuses);
	}


	pSelectTwoPointsGUI->slotUpdatePts(0.0);


   }
 
vtkSphereCallback::vtkSphereCallback(){ this->Sphere = vtkSphere::New(); }
vtkSphereCallback::~vtkSphereCallback(){ this->Sphere->Delete(); }
 

