#include <string>

#include <QMenu>
#include <qstring.h>
#include <QFileDialog>
#include <QWheelEvent>

#include "SelectTwoPointsGUI.h"
#include "SelectTwoPoints.h"
//#include "CIniWriter.h"
//#include "Singleton.h"
//#include "DynamicFilesManager.h"

std::string strFullPathScenarios;

using namespace std;

SelectTwoPointsGUI::SelectTwoPointsGUI() {	
	setupUi(this);
	
	m_bArtery = false;
	m_pQVTKWidget->SetRenderWindow(m_SelectTwoPoints.GetRenderWindow());
	m_SelectTwoPoints.setInteractor(m_pQVTKWidget->GetInteractor());

	connect(actionLoadFile, SIGNAL(triggered()), this, SLOT(slotLoadFile()));
	connect(actionSaveFile, SIGNAL(triggered()), this, SLOT(slotSaveFile()));

	connect(m_pDoubleSpinBoxP1X, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));
	connect(m_pDoubleSpinBoxP1Y, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));
	connect(m_pDoubleSpinBoxP1Z, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));
	connect(m_pDoubleSpinBoxP2X, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));
	connect(m_pDoubleSpinBoxP2Y, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));
	connect(m_pDoubleSpinBoxP2Z, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));

	connect(m_pDoubleSpinBoxRadiuses, SIGNAL(valueChanged(double)), this, SLOT(slotUpdatePts(double)));
}


SelectTwoPointsGUI::~SelectTwoPointsGUI() {
}

QString SelectTwoPointsGUI::openDialog(const char * apchSuffix) {
	QString qstrFileName = QFileDialog::getOpenFileName(this, 
		tr("Open File"),
		tr(strFullPathScenarios.c_str()), 
		apchSuffix);
	QFile f(qstrFileName);
	QFileInfo fileInfo(f.fileName());
	QString qstrArteryFileName(fileInfo.fileName());
	m_strArteryFileName = qstrArteryFileName.toStdString();
	m_SelectTwoPoints.setArteryFileName(m_strArteryFileName);

	return(qstrFileName);
}

QString SelectTwoPointsGUI::saveDialog(const char * apchSuffix) {
	QString qstrFileName = QFileDialog::getSaveFileName(this, 
		tr("Save file"),
		tr(strFullPathScenarios.c_str()), apchSuffix);
	return(qstrFileName);
}

bool SelectTwoPointsGUI::getStatusArtery()
{
	return(m_bArtery);
}
  

void SelectTwoPointsGUI::setStatusArtery(bool abArtery)
{
	m_bArtery = abArtery;

}

void SelectTwoPointsGUI::slotLoadFile() {
	QString qstrFileName = openDialog("*.* \n *.vtk *.hdr *.nii \n* ");
	if(qstrFileName != "") {

		std::string strFileName = qstrFileName.toStdString();
		m_SelectTwoPoints.LoadArtery(strFileName);
		m_bArtery = true;
	}
	//updateGUI();
}

void SelectTwoPointsGUI::slotSaveFile() {
	//QString qstrFileName = saveDialog(".txt");

	//std::string strFileName = qstrFileName.toStdString();
	//CIniWriter * pCIniWriter = Singleton< CIniWriter > ::instance();
	//pCIniWriter->SetFileName(strFileName.c_str());

	//string strSection1 = m_strArteryFileName.c_str();
	//string strKey1X = "InitialPointX";
	//pCIniWriter->WriteDouble(strSection1.c_str(), strKey1X.c_str(), m_pDoubleSpinBoxP1X->value());
	//string strKey1Y = "InitialPointY";
	//	pCIniWriter->WriteDouble(strSection1.c_str(), strKey1Y.c_str(), m_pDoubleSpinBoxP1Y->value());
	//string strKey1Z = "InitialPointZ";
	//	pCIniWriter->WriteDouble(strSection1.c_str(), strKey1Z.c_str(), m_pDoubleSpinBoxP1Z->value());

	//string strSection2 = m_strArteryFileName.c_str();;
	//string strKey2X = "FinalPointX";
	//	pCIniWriter->WriteDouble(strSection2.c_str(), strKey2X.c_str(), m_pDoubleSpinBoxP2X->value());
	//string strKey2Y = "FinalPointY";
	//	pCIniWriter->WriteDouble(strSection2.c_str(), strKey2Y.c_str(), m_pDoubleSpinBoxP2Y->value());
	//string strKey2Z = "FinalPointZ";
	//	pCIniWriter->WriteDouble(strSection2.c_str(), strKey2Z.c_str(), m_pDoubleSpinBoxP2Z->value());

	//m_SelectTwoPoints.savePointAndIdxToFile(strFileName.c_str());
 //   

}

void SelectTwoPointsGUI::slotUpdatePts(double adbDummy)
{
	double arrdbPt1[3] = {m_pDoubleSpinBoxP1X->value(), m_pDoubleSpinBoxP1Y->value(), m_pDoubleSpinBoxP1Z->value()};
	double arrdbPt2[3] = {m_pDoubleSpinBoxP2X->value(), m_pDoubleSpinBoxP2Y->value(), m_pDoubleSpinBoxP2Z->value()};
	double dbRadiuses = m_pDoubleSpinBoxRadiuses->value();
	bool bArtery = getStatusArtery();
	m_SelectTwoPoints.UpdatePts(arrdbPt1, arrdbPt2, dbRadiuses, bArtery);
}