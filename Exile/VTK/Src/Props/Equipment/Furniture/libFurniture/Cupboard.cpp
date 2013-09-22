#include <string>

#include "vtkSmartPointer.h"
#include "vtkTransform.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"

#include "Cupboard.h"

using namespace std;

vtkStandardNewMacro(Cupboard);

Cupboard::~Cupboard()	{
}

//-----------------------------------------------------------

Cupboard::Cupboard()	{
}

//-----------------------------------------------------------

string Cupboard::getSQLPrintCommand() const {
	return(string(""));
}

//----------------------------------------------------------

void Cupboard::initCupboard()	{
//	double dbarrTranslate[3][3]={{0,0,0},{0,2,0},{0,4,0}};

	int nI, nJ;
	for (nJ=0;nJ<50;nJ++)	{
	for (nI=0;nI<2;nI++)	{
		m_arrpShelf = Shelf::New();
		m_arrpShelf->setSizes(10,0.1,2);

		vtkTransform *pTransform = vtkTransform::New();
//		pTransform->Translate(dbarrTranslate[nI]);
		double y = 2*nJ;
		double x = 2*nI;
		pTransform->Translate(y,0.0,x);
		m_arrpShelf->SetUserTransform(pTransform);
		this->AddPart(m_arrpShelf);
		m_arrShelf.push_back(m_arrpShelf);
		m_arrpShelf->Delete();
		pTransform->Delete();
	}}
}

//-----------------------------------------------------------------------

void Cupboard::AddShelf(Shelf * aShelf)	{
	aShelf = Shelf::New();

	vtkTransform *pTransform = vtkTransform::New();
//		pTransform->Translate(dbarrTranslate[nI]);
	aShelf->SetUserTransform(pTransform);
	this->AddPart(aShelf);
	m_arrShelf.push_back(aShelf);
	pTransform->Delete();
	aShelf->Delete();
}