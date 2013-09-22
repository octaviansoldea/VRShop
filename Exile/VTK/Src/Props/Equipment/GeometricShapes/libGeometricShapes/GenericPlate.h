#ifndef GENERIC_PLATE_H
#define GENERIC_PLATE_H

#include <string>

#include "vtkSmartPointer.h"
#include "vtkPolyData.h"

class GenericPlate {
public:
	GenericPlate();
	vtkSmartPointer < vtkPolyData > getPoly();

private:
	vtkSmartPointer < vtkPolyData > m_PolyData;
};

#endif //GENERIC_PLATE_H