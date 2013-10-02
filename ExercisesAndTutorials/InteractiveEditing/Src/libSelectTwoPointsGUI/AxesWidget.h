#ifndef AXES_WIDGET_H
#define AXES_WIDGET_H

#include "vtkObject.h"
#include "vtkAxesActor.h"
#include "vtkSmartPointer.h"

//===========================================================================
/*!
    \file   AxesWidget.h
	\class	AxesWidget
	\brief	The class implements a set of axes to be show in the window that appears 
			at the initialization step.
*/
//===========================================================================

class AxesWidget : public vtkObject {

protected:

	vtkSmartPointer < vtkAxesActor > m_pvtkAxesActor;  /**< The variable keeps the actor axes*/

private:

	AxesWidget(); /**< Constructor of the AxesWidget class */
	~AxesWidget(); /**< Destructor of the AxesWidget class */

public:
	virtual void VisibilityOn(); /**< Set the axes visible */
	virtual void VisibilityOff(); /**< Set the axes invisible */
	virtual int GetVisibility(); /**< Get the variable m_pvtkAxesActor */
	virtual void SetVisibility(int anVisible);  /**< Set the variable m_pvtkAxesActor */

	static AxesWidget * New();
	
	void SetLengths(double adbLength); /**< Set the length of the axes */

	vtkSmartPointer < vtkAxesActor > GetAxesActor();  /**< Get the axes actor*/

	void SetLabels(const char * apchX, const char * apchY, const char * apchZ); /**< Set the labels of the axes */


};

#endif //AXES_WIDGET_H