/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkArrowSource.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkArrowSource - Appends a cylinder to a cone to form an arrow.
// .SECTION Description
// vtkArrowSource was intended to be used as the source for a glyph.
// The shaft base is always at (0,0,0). The arrow tip is always at (1,0,0). If
// "Invert" is true, then the ends are flipped i.e. tip is at (0,0,0) while
// base is at (1, 0, 0).
// The resolution of the cone and shaft can be set and default to 6.
// The radius of the cone and shaft can be set and default to 0.03 and 0.1.
// The length of the tip can also be set, and defaults to 0.35.


#ifndef ARROW_SOURCE_START_END
#define ARROW_SOURCE_START_END

#include "vtkTransformPolyDataFilter.h"

#include "vtkArrowSource.h"

//===========================================================================
/*!
    \file   ArrowSourceStartEnd.h
	\class	ArrowSourceStartEnd
	\brief	The class creates a arrow to be used in the window created at the initial step
*/
//===========================================================================


class VTK_GRAPHICS_EXPORT ArrowSourceStartEnd : public vtkArrowSource
{
public:
  // Description

  static ArrowSourceStartEnd *New();

  vtkTypeMacro(ArrowSourceStartEnd, vtkArrowSource);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  vtkPolyData* GetOutput_Specific_NonVirtual();
  vtkAlgorithmOutput* GetOutputPort_Specific_NonVirtual();

  vtkSetVectorMacro(PointStart,double,3);

  void SetPointStart(double aarrdbX, double aarrdbY, double aarrdbZ) {
	  double arrdbXYZ[3] = {aarrdbX, aarrdbY, aarrdbZ};
	  SetPointStart(arrdbXYZ);
  }

  vtkGetVectorMacro(PointStart,double,3);
  vtkSetVectorMacro(PointEnd,double,3);
   void SetPointEnd(double aarrdbX, double aarrdbY, double aarrdbZ) {
	  double arrdbXYZ[3] = {aarrdbX, aarrdbY, aarrdbZ};
	  SetPointEnd(arrdbXYZ);
  }
  vtkGetVectorMacro(PointEnd,double,3);

  virtual void Update();

protected:
  ArrowSourceStartEnd();
  ~ArrowSourceStartEnd();


private:
  ArrowSourceStartEnd(const vtkArrowSource&); // Not implemented.
  void operator=(const ArrowSourceStartEnd&); // Not implemented.

  double PointStart[3];
  double PointEnd[3];

  vtkSmartPointer<vtkTransform> m_pTransform;
  vtkSmartPointer<vtkTransformPolyDataFilter> transformPD;
};

#endif //ARROW_SOURCE_START_END


