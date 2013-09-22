#include "vtkRenderWindow.h"
#include "QVTKWidget.h"
#include <string>

#include "BasicVTKDefinitions.h"
#include "BaseEditor.h"

//--------------------------------------------------------------------------------

BaseEditor::BaseEditor() {
	FunctorPathResource f;

	pDatabaseMgr = &DatabaseMgr::Create(f("Databases/Products.db").c_str(), DatabaseMgr::QSQLITE);
	m_pOrientationWidgets = vtkSmartPointer < OrientationWidgets > ::New();
}

//--------------------------------------------------------------------------------

BaseEditor::~BaseEditor() {
	delete pDatabaseMgr;
}

//--------------------------------------------------------------------------------

void  BaseEditor::setQVTKWidgets(QVTKWidget * apQVTKWidget) {
	m_pQVTKWidget = apQVTKWidget;

	m_pQVTKWidget->SetRenderWindow(renWin.m_pRenWin3D);
	renWin.m_pIren3D = m_pQVTKWidget->GetInteractor();

	m_pOrientationWidgets->SetRenderingPipeline(renWin.m_pIren3D);
}

//--------------------------------------------------------------------------------
