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

//===========================================================================
/*!
    \file   vtkSphereCallback.h
	\class	vtkSphereCallback
	\brief	vtkSphereCallback 
*/
//===========================================================================

class vtkSphereCallback : public vtkCommand
{
public:
  
  static vtkSphereCallback *New()
    {
    return new vtkSphereCallback;
    };

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
  virtual void Execute(vtkObject *caller, unsigned long, void*);

   vtkSphereCallback();
	~vtkSphereCallback();
   vtkSphere* Sphere;
 
  
};

#endif //SPHERE_WIDGET_H

