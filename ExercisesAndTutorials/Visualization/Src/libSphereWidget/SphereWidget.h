#ifndef SPHERE_WIDGET_H
#define SPHERE_WIDGET_H

#include <vtkCommand.h>
#include <vtkMath.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSphereRepresentation.h>
#include <vtkSphereWidget2.h>
 
// Callback that displays the sphere widget's spherical handle postion
// in both sphercial (relative to the widget's center) and cartesian global coordinates
class vtkSphereCallback : public vtkCommand
{
public:
  static vtkSphereCallback *New()
    {
    return new vtkSphereCallback;
    }

  // All derived classes of vtkCommand must implement this
  // method. This is the method that actually does the work of the
  // callback. The caller argument is the object invoking the event,
  // the eventId parameter is the id of the event, and callData
  // parameter is data that can be passed into the execute
  // method. (Note: vtkObject::InvokeEvent() takes two parameters: the
  // event id (or name) and call data. Typically call data is NULL,
  // but the user can package data and pass it this
  // way. Alternatively, a derived class of vtkCommand can be used to
  // pass data.) 
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
    vtkSphereWidget2 *sphereWidget = 
      reinterpret_cast<vtkSphereWidget2*>(caller);

    double center[3], handlePosition[3];

	// This class is a concrete representation for the vtkSphereWidget2. It
	// represents a sphere with an optional handle.  Through interaction with the
	// widget, the sphere can be arbitrarily positioned and scaled in 3D space;
	// and the handle can be moved on the surface of the sphere.	
	vtkSphereRepresentation* sphereRepresentation = 
		reinterpret_cast<vtkSphereRepresentation*>(sphereWidget->GetRepresentation());
	sphereRepresentation->HandleVisibilityOn();

	sphereRepresentation->GetHandlePosition( handlePosition );
    sphereRepresentation->GetSphere( this->Sphere );

    this->Sphere->GetCenter( center );
 
    double radius = sqrt( static_cast<double>(vtkMath::Distance2BetweenPoints( center, handlePosition ) ) );
    radius = (radius <= 0.0 ? 1.0 : radius );
    double theta = vtkMath::DegreesFromRadians( atan2( ( handlePosition[1] - center[1] ), ( handlePosition[0] - center[0] ) ) );
    double phi   = vtkMath::DegreesFromRadians( acos( ( handlePosition[2] - center[2] ) / radius ) );
 
    std::cout << "r, theta, phi: ("
              << std::setprecision(3)
              << radius << ", " << theta << ", " << phi << ") "
              << "x, y, z: ("
              << handlePosition[0] << ", "
              << handlePosition[1] << ", " 
              << handlePosition[2] << ") "
              << std::endl;
   }

  vtkSphereCallback(){ this->Sphere = vtkSphere::New(); }
  ~vtkSphereCallback(){ this->Sphere->Delete(); }
 
  vtkSphere* Sphere;

};

#endif //SPHERE_WIDGET_H

