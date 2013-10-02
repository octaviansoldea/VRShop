#ifndef HANDLE_WIDGET_H
#define HANDLE_WIDGET_H

#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkHandleWidget.h>
#include <vtkHandleRepresentation.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

class HandleWidget : public vtkCommand	{	//WORKS
public:
	static HandleWidget *New()	{
		return new HandleWidget;
	}

	virtual void Execute(vtkObject *caller, unsigned long, void*)	{
		vtkHandleWidget *handle = reinterpret_cast< vtkHandleWidget *>(caller);
		if (!handle)	{
			return;
		}

		vtkHandleRepresentation* handleRepresentation = 
			reinterpret_cast<vtkHandleRepresentation*>(handle->GetRepresentation());
	}
};

#endif	//HANDLE_WIDGET_H