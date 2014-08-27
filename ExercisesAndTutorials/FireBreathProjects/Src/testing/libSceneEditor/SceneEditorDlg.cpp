#include <string>

#include <qmenu.h>
#include <qmenubar.h>
#include <QSqlQuery>
#include <qsqlerror.h>
#include <QImageReader>
#include <QMessageBox>
#include <QString>

#include "SceneEditorDlg.h"

using namespace std;

int PrintQMsgBox(const char * apchMessage) {
	QMessageBox msgBox;
	msgBox.setText(apchMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Error Message");
	int nRes = msgBox.exec();
	return(nRes);
}

SceneEditorDlg::SceneEditorDlg(QWidget *parent) : QMainWindow(parent)	{
	//connect first to the database for the data
	
	m_strDBFileName = "C:/Projekti/QT/Database/Build/Test_Database/database.db";
	m_DB = QSqlDatabase::addDatabase("QSQLITE");
	m_DB.setDatabaseName(m_strDBFileName.c_str());
	if (!m_DB.open()) {
		QString strMsg = QString("Cannot open file ") + m_strDBFileName.c_str();
//		exit(-1);
	}

	m_pCentralWidget = new QWidget;
	setCentralWidget(m_pCentralWidget);

	createMenuBar();
	createPoseEditor();
	createQVTK();
	createChoosing();
	createObjectEditor();
	createProperties();

	setWindowTitle(tr("Scene Editor Dialog"));
}

SceneEditorDlg::~SceneEditorDlg() {	
	if(m_DB.isOpen())
		m_DB.close();
}
//--------------------------------------------------------------------------------

void SceneEditorDlg::createMenuBar()	{
	//Menu File
	QMenu *menu = menuBar()->addMenu("File");
	
	//Add actions
	m_pActionNewScene = new QAction("New Scene",menu);
	menu->addAction(m_pActionNewScene);
//	QObject::connect(m_pActionNewScene,SIGNAL(triggered()), this, SLOT(newScene()));

	m_pActionLoadScene = new QAction("Load Scene", menu);
	menu->addAction(m_pActionLoadScene);
//	QObject::connect(m_pActionLoadScene,SIGNAL(triggered()), this, SLOT(loadScene()));

	m_pActionSaveScene = new QAction("Save Scene", menu);
	menu->addAction(m_pActionSaveScene);
//	QObject::connect(m_pActionSaveScene,SIGNAL(triggered()), this, SLOT(saveScene()));
}

//--------------------------------------------------------------------------------

void SceneEditorDlg::createPoseEditor()	{
	//Left docked widget
	m_pDockWidgetSceneEditorPose = new QDockWidget("Pose Editor");
	m_pDockWidgetSceneEditorPose->setFloating(false);
	m_pDockWidgetSceneEditorPose->setFeatures(QDockWidget::AllDockWidgetFeatures);
	
	m_pDockWidgetPoseContents = new QWidget();
	m_pDockWidgetSceneEditorPose->setWidget(m_pDockWidgetPoseContents);
	addDockWidget(static_cast<Qt::DockWidgetArea>(1), m_pDockWidgetSceneEditorPose);

	gridLayout_2 = new QGridLayout(m_pDockWidgetPoseContents);
	m_pPoseEditorFrame = new QFrame(m_pDockWidgetPoseContents);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(m_pPoseEditorFrame->sizePolicy().hasHeightForWidth());
	m_pPoseEditorFrame->setSizePolicy(sizePolicy);
	m_pPoseEditorFrame->setAutoFillBackground(false);
	m_pPoseEditorFrame->setFrameShape(QFrame::Box);
	m_pPoseEditorFrame->setFrameShadow(QFrame::Plain);

	gridLayout_2->addWidget(m_pPoseEditorFrame, 0, 0, 1, 1);
	gridLayout_4 = new QGridLayout(m_pPoseEditorFrame);
}

//--------------------------------------------------------------------------------

void SceneEditorDlg::createQVTK() {
//	m_pQVTKWidgetSceneEditorPose = new QVTKWidget(m_pPoseEditorFrame);
	m_pQVTKWidgetSceneEditorPose = new QWidget(m_pPoseEditorFrame);

	m_pQVTKWidgetSceneEditorPose->setMinimumSize(QSize(400, 400));
//	m_pQVTKWidgetSceneEditorPose->setFrameShape(QFrame::StyledPanel);
//	m_pQVTKWidgetSceneEditorPose->setFrameShadow(QFrame::Raised);

	gridLayout_4->addWidget(m_pQVTKWidgetSceneEditorPose, 1, 0, 1, 1);
}

//--------------------------------------------------------------------------------

void SceneEditorDlg::createChoosing()	{
	//Layout
	m_pGroupBoxChoosingPose = new QGroupBox(m_pPoseEditorFrame);
	m_pGroupBoxChoosingPose->setTitle("Choosing");
	m_pGroupBoxChoosingPose->setMinimumSize(QSize(400, 140));
	m_pGroupBoxChoosingPose->setMaximumSize(QSize(400, 140));
	gridLayout_4->addWidget(m_pGroupBoxChoosingPose, 2, 0, 1, 1);
	
	//Category field
	m_pComboBoxCategoryPose = new QComboBox(m_pGroupBoxChoosingPose);
	m_pComboBoxCategoryPose->setGeometry(QRect(60, 20, 91, 20));
	m_pLabelCategoryPose = new QLabel(m_pGroupBoxChoosingPose);
	m_pLabelCategoryPose->setText("Category");
	m_pLabelCategoryPose->setGeometry(QRect(10, 20, 51, 16));
	//connect to the database and browse all available categories
	updateCategory();

	//Product field
	m_pComboBoxProductPose = new QComboBox(m_pGroupBoxChoosingPose);
	m_pComboBoxProductPose->setGeometry(QRect(60, 50, 91, 20));
	m_pLabelProductPose = new QLabel(m_pGroupBoxChoosingPose);
	m_pLabelProductPose->setText("Product");
	m_pLabelProductPose->setGeometry(QRect(10, 50, 51, 16));
	QObject::connect(m_pComboBoxCategoryPose, SIGNAL(highlighted(const QString &)), this, SLOT(updateProduct(const QString &)));

	//ID field
	m_pComboBoxProductCodePose = new QComboBox(m_pGroupBoxChoosingPose);
	m_pComboBoxProductCodePose->setGeometry(QRect(60, 80, 91, 20));
	m_pLabelProductCodePose = new QLabel(m_pGroupBoxChoosingPose);
	m_pLabelProductCodePose->setText("ID");
	m_pLabelProductCodePose->setGeometry(QRect(10, 80, 51, 16));
	connect(m_pComboBoxProductPose, SIGNAL(highlighted(const QString &)), this, SLOT(updateProductID(const QString &)));

	//ListWidget
	m_pImageViewerChoosingPose = new QLabel(m_pGroupBoxChoosingPose);
	m_pImageViewerChoosingPose->setGeometry(QRect(160, 13, 121, 111));
	connect(m_pComboBoxProductCodePose, SIGNAL(highlighted(const QString &)), this, SLOT(addImage2Widget(const QString &)));

	//Delete button
	m_pPushButtonDeleteProduct = new QPushButton(m_pGroupBoxChoosingPose);
	m_pPushButtonDeleteProduct->setText("Delete");
	m_pPushButtonDeleteProduct->setGeometry(QRect(310, 80, 75, 23));
//	connect();

	//Edit button
	m_pPushButtonEditProduct = new QPushButton(m_pGroupBoxChoosingPose);
	m_pPushButtonEditProduct->setText("Edit Product");
	m_pPushButtonEditProduct->setGeometry(QRect(310, 110, 75, 23));
//	connect();

	//Search button
	m_pPushButtonSearchPose = new QPushButton(m_pGroupBoxChoosingPose);
	m_pPushButtonSearchPose->setText("Search");
	m_pPushButtonSearchPose->setGeometry(QRect(60, 110, 75, 23));
//	connect();

	//Insert button
	m_pPushButtonInsertProduct = new QPushButton(m_pGroupBoxChoosingPose);
	m_pPushButtonInsertProduct->setText("Insert");
	m_pPushButtonInsertProduct->setGeometry(QRect(310, 50, 75, 23));
//	connect();

	//Select location
	m_pGroupBoxSelectLocation = new QGroupBox(m_pGroupBoxChoosingPose);
	m_pGroupBoxSelectLocation->setTitle("Select Location");
	m_pGroupBoxSelectLocation->setGeometry(QRect(300, 10, 91, 31));
	m_pRadioButtonSelectLocation = new QRadioButton(m_pGroupBoxSelectLocation);
	m_pRadioButtonSelectLocation->setGeometry(QRect(30, 10, 20, 20));
	m_pRadioButtonSelectLocation->setLayoutDirection(Qt::RightToLeft);
//	connect();
}

//-------------------------------------------------------------------------------

void SceneEditorDlg::createProperties()	{
	m_pTabWidgetPropertiesPose = new QTabWidget(m_pPoseEditorFrame);
	m_pTabWidgetPropertiesPose->setMinimumSize(QSize(260, 125));
	m_pTabWidgetPropertiesPose->setMaximumSize(QSize(260, 125));

	//Tabs
	m_pTabLocationPose = new QWidget();
	m_pTabWidgetPropertiesPose->addTab(m_pTabLocationPose,"Location");

	m_pTabOrientationPose = new QWidget();
	m_pTabWidgetPropertiesPose->addTab(m_pTabOrientationPose, "Orientation");

	m_pTabWidgetPropertiesPose->setTabText(m_pTabWidgetPropertiesPose->indexOf(m_pTabLocationPose), "Location");
	m_pTabWidgetPropertiesPose->setTabText(m_pTabWidgetPropertiesPose->indexOf(m_pTabOrientationPose), "Orientation");
	
	//Location tab
	m_pDoubleSpinBoxLocationXPose = new QDoubleSpinBox(m_pTabLocationPose);
	m_pDoubleSpinBoxLocationXPose->setGeometry(QRect(20, 10, 62, 22));
	m_pDoubleSpinBoxLocationZPose = new QDoubleSpinBox(m_pTabLocationPose);
	m_pDoubleSpinBoxLocationZPose->setGeometry(QRect(20, 70, 62, 22));
	m_pLabelLocationYPose = new QLabel(m_pTabLocationPose);
	m_pLabelLocationYPose->setText("Y");
	m_pLabelLocationYPose->setGeometry(QRect(10, 40, 16, 16));
	m_pLabelLocationZPose = new QLabel(m_pTabLocationPose);
	m_pLabelLocationZPose->setText("Z");
	m_pLabelLocationZPose->setGeometry(QRect(10, 70, 16, 16));
	m_pDoubleSpinBoxLocationYPose = new QDoubleSpinBox(m_pTabLocationPose);
	m_pDoubleSpinBoxLocationYPose->setGeometry(QRect(20, 40, 62, 22));
	m_pLabelLocationXPose = new QLabel(m_pTabLocationPose);
	m_pLabelLocationXPose->setText("X");
	m_pLabelLocationXPose->setGeometry(QRect(10, 10, 16, 16));

	m_pScrollBarLocationXPose = new QScrollBar(m_pTabLocationPose);
	m_pScrollBarLocationXPose->setGeometry(QRect(90, 10, 160, 16));
	m_pScrollBarLocationXPose->setOrientation(Qt::Horizontal);
	m_pScrollBarLocationYPose = new QScrollBar(m_pTabLocationPose);
	m_pScrollBarLocationYPose->setGeometry(QRect(90, 40, 160, 16));
	m_pScrollBarLocationYPose->setOrientation(Qt::Horizontal);
	m_pScrollBarLocationZPose = new QScrollBar(m_pTabLocationPose);
	m_pScrollBarLocationZPose->setGeometry(QRect(90, 70, 160, 16));
	m_pScrollBarLocationZPose->setOrientation(Qt::Horizontal);

	m_pLabelOrientationX = new QLabel(m_pTabOrientationPose);
	m_pLabelOrientationX->setText("X");
	m_pLabelOrientationX->setGeometry(QRect(10, 10, 16, 16));
	m_pScrollBarOrientationYPose = new QScrollBar(m_pTabOrientationPose);
	m_pScrollBarOrientationYPose->setGeometry(QRect(90, 40, 160, 16));
	m_pScrollBarOrientationYPose->setOrientation(Qt::Horizontal);
	m_pLabelOrientationZ = new QLabel(m_pTabOrientationPose);
	m_pLabelOrientationZ->setText("Z");
	m_pLabelOrientationZ->setGeometry(QRect(10, 70, 16, 16));
	m_pScrollBarOrientationZPose = new QScrollBar(m_pTabOrientationPose);
	m_pScrollBarOrientationZPose->setGeometry(QRect(90, 70, 160, 16));
	m_pScrollBarOrientationZPose->setOrientation(Qt::Horizontal);
	m_pDoubleSpinBoxOrientationXPose = new QDoubleSpinBox(m_pTabOrientationPose);
	m_pDoubleSpinBoxOrientationXPose->setGeometry(QRect(20, 10, 62, 22));
	m_pDoubleSpinBoxOrientationYPose = new QDoubleSpinBox(m_pTabOrientationPose);
	m_pDoubleSpinBoxOrientationYPose->setGeometry(QRect(20, 40, 62, 22));
	m_pScrollBarOrientationXPose = new QScrollBar(m_pTabOrientationPose);
	m_pScrollBarOrientationXPose->setGeometry(QRect(90, 10, 160, 16));
	m_pScrollBarOrientationXPose->setOrientation(Qt::Horizontal);
	m_pDoubleSpinBoxOrientationZpose = new QDoubleSpinBox(m_pTabOrientationPose);
	m_pDoubleSpinBoxOrientationZpose->setGeometry(QRect(20, 70, 62, 22));
	m_pLabelOrientationY = new QLabel(m_pTabOrientationPose);
	m_pLabelOrientationY->setText("X");
	m_pLabelOrientationY->setGeometry(QRect(10, 40, 16, 16));
	
	gridLayout_4->addWidget(m_pTabWidgetPropertiesPose, 3, 0, 1, 1);
}

void SceneEditorDlg::createObjectEditor()	{
	//Left docked widget
	m_pDockWidgetSceneEditorObject = new QDockWidget("Object Editor");
	m_pDockWidgetSceneEditorObject->setAutoFillBackground(false);
	m_pDockWidgetSceneEditorObject->setFloating(false);
	m_pDockWidgetSceneEditorObject->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pDockWidgetObjectContents = new QWidget();

	gridLayout_5 = new QGridLayout(m_pDockWidgetObjectContents);
	m_pObjectEditorFrame = new QFrame(m_pDockWidgetObjectContents);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(m_pObjectEditorFrame->sizePolicy().hasHeightForWidth());
	m_pObjectEditorFrame->setSizePolicy(sizePolicy);
	m_pObjectEditorFrame->setAutoFillBackground(false);
	m_pObjectEditorFrame->setFrameShape(QFrame::Box);
	m_pObjectEditorFrame->setFrameShadow(QFrame::Plain);

	gridLayout = new QGridLayout(m_pObjectEditorFrame);
	m_pGroupBoxChoosingObject = new QGroupBox(m_pObjectEditorFrame);
	m_pGroupBoxChoosingObject->setTitle("Choosing");
	m_pGroupBoxChoosingObject->setMinimumSize(QSize(290, 180));
	m_pGroupBoxChoosingObject->setMaximumSize(QSize(290, 180));
	m_pListWidgetChoosingObject = new QListWidget(m_pGroupBoxChoosingObject);
	m_pListWidgetChoosingObject->setGeometry(QRect(160, 60, 121, 111));
	m_pComboBoxCategoryObject = new QComboBox(m_pGroupBoxChoosingObject);
	m_pComboBoxCategoryObject->setGeometry(QRect(60, 20, 91, 20));
	m_pLabelCategoryObject = new QLabel(m_pGroupBoxChoosingObject);
	m_pLabelCategoryObject->setText("Category");
	m_pLabelCategoryObject->setGeometry(QRect(10, 20, 51, 16));
	m_pComboBoxProductObject = new QComboBox(m_pGroupBoxChoosingObject);
	m_pComboBoxProductObject->setGeometry(QRect(60, 50, 91, 20));
	m_pLabelProductObject = new QLabel(m_pGroupBoxChoosingObject);
	m_pLabelProductObject->setText("Product");
	m_pLabelProductObject->setGeometry(QRect(10, 50, 51, 16));
	m_pPushButtonSearchObject = new QPushButton(m_pGroupBoxChoosingObject);
	m_pPushButtonSearchObject->setText("Search");
	m_pPushButtonSearchObject->setGeometry(QRect(180, 30, 75, 23));
	m_pPushButtonAddProductObject = new QPushButton(m_pGroupBoxChoosingObject);
	m_pPushButtonAddProductObject->setText("Add New Product");
	m_pPushButtonAddProductObject->setGeometry(QRect(20, 120, 101, 23));
	m_pLabelProductCodeObject = new QLabel(m_pGroupBoxChoosingObject);
	m_pLabelProductCodeObject->setText("ID");
	m_pLabelProductCodeObject->setGeometry(QRect(10, 80, 21, 16));
	m_pLineEditProductCodeObject = new QLineEdit(m_pGroupBoxChoosingObject);
	m_pLineEditProductCodeObject->setGeometry(QRect(40, 80, 111, 20));
	m_pPushButtonDeleteProductObject = new QPushButton(m_pGroupBoxChoosingObject);
	m_pPushButtonDeleteProductObject->setText("Delete Product");
	m_pPushButtonDeleteProductObject->setGeometry(QRect(20, 150, 101, 23));

	gridLayout->addWidget(m_pGroupBoxChoosingObject, 0, 0, 1, 1);
	
//        m_pQVTKWidgetSceneEditorObject = new QVTKWidget(m_pObjectEditorFrame);
	m_pQVTKWidgetSceneEditorObject = new QWidget(m_pObjectEditorFrame);
	m_pQVTKWidgetSceneEditorObject->setMinimumSize(QSize(200, 200));
	m_pQVTKWidgetSceneEditorObject->setMaximumSize(QSize(16777215, 16777215));
//        m_pQVTKWidgetSceneEditorObject->setFrameShape(QFrame::StyledPanel);
 //       m_pQVTKWidgetSceneEditorObject->setFrameShadow(QFrame::Raised);
	gridLayout_3 = new QGridLayout(m_pQVTKWidgetSceneEditorObject);
	
	gridLayout->addWidget(m_pQVTKWidgetSceneEditorObject, 0, 1, 2, 1);
	
	m_pGroupBoxEditParts = new QGroupBox(m_pObjectEditorFrame);
	m_pGroupBoxEditParts->setTitle("Edit Parts Properties");
	m_pGroupBoxEditParts->setMinimumSize(QSize(290, 360));
	m_pGroupBoxEditParts->setMaximumSize(QSize(290, 360));
	m_pComboBoxEditPartsShape = new QComboBox(m_pGroupBoxEditParts);
	m_pComboBoxEditPartsShape->setGeometry(QRect(70, 20, 91, 20));
	m_pLabelEditPartsShape = new QLabel(m_pGroupBoxEditParts);
	m_pLabelEditPartsShape->setText("Shape");
	m_pLabelEditPartsShape->setGeometry(QRect(10, 20, 51, 16));
	m_pPushButtonAddPart = new QPushButton(m_pGroupBoxEditParts);
	m_pPushButtonAddPart->setText("Add Part");
	m_pPushButtonAddPart->setGeometry(QRect(190, 20, 75, 23));

	m_pGroupBoxTextureMap = new QGroupBox(m_pGroupBoxEditParts);
	m_pGroupBoxTextureMap->setTitle("Texture Maps");
	m_pGroupBoxTextureMap->setGeometry(QRect(10, 80, 251, 141));
	m_pListWidgetTextureMaps = new QListWidget(m_pGroupBoxTextureMap);
	m_pListWidgetTextureMaps->setGeometry(QRect(100, 10, 141, 121));
	m_pComboBoxTextureMapsName = new QComboBox(m_pGroupBoxTextureMap);
	m_pComboBoxTextureMapsName->setGeometry(QRect(10, 70, 81, 20));
	m_pLabelTextureMapsName = new QLabel(m_pGroupBoxTextureMap);
	m_pLabelTextureMapsName->setText("Texture Name");
	m_pLabelTextureMapsName->setGeometry(QRect(10, 40, 71, 16));
	m_pTabWidgetPropertiesObject = new QTabWidget(m_pGroupBoxEditParts);
	m_pTabWidgetPropertiesObject->setGeometry(QRect(10, 230, 260, 125));
	m_pTabWidgetPropertiesObject->setMinimumSize(QSize(260, 125));
	m_pTabWidgetPropertiesObject->setMaximumSize(QSize(260, 125));

	m_pLocationObject = new QWidget();
	m_pDoubleSpinBoxLocationXObject = new QDoubleSpinBox(m_pLocationObject);
	m_pDoubleSpinBoxLocationXObject->setGeometry(QRect(20, 10, 62, 22));
	m_pDoubleSpinBoxLocationZObject = new QDoubleSpinBox(m_pLocationObject);
	m_pDoubleSpinBoxLocationZObject->setGeometry(QRect(20, 70, 62, 22));
	m_pLabelLocationYObject = new QLabel(m_pLocationObject);
	m_pLabelLocationYObject->setText("Y");
	m_pLabelLocationYObject->setGeometry(QRect(10, 40, 16, 16));
	m_pLabelLocationZObject = new QLabel(m_pLocationObject);
	m_pLabelLocationZObject->setText("Z");
	m_pLabelLocationZObject->setGeometry(QRect(10, 70, 16, 16));
	m_pDoubleSpinBoxLocationYObject = new QDoubleSpinBox(m_pLocationObject);
	m_pDoubleSpinBoxLocationYObject->setGeometry(QRect(20, 40, 62, 22));
	m_pLabelLocationXObject = new QLabel(m_pLocationObject);
	m_pLabelLocationXObject->setText("X");
	m_pLabelLocationXObject->setGeometry(QRect(10, 10, 16, 16));
	m_pScrollBarLocationXObject = new QScrollBar(m_pLocationObject);
	m_pScrollBarLocationXObject->setGeometry(QRect(90, 10, 160, 16));
	m_pScrollBarLocationXObject->setOrientation(Qt::Horizontal);
	m_pScrollBarLocationYObject = new QScrollBar(m_pLocationObject);
	m_pScrollBarLocationYObject->setGeometry(QRect(90, 40, 160, 16));
	m_pScrollBarLocationYObject->setOrientation(Qt::Horizontal);
	m_pScrollBarLocationZObject = new QScrollBar(m_pLocationObject);
	m_pScrollBarLocationZObject->setGeometry(QRect(90, 70, 160, 16));
	m_pScrollBarLocationZObject->setOrientation(Qt::Horizontal);
	m_pTabWidgetPropertiesObject->addTab(m_pLocationObject, "Location");
	m_pTabWidgetPropertiesObject->setTabText(m_pTabWidgetPropertiesObject->indexOf(m_pLocationObject), "Location");

	m_pOrientationObject = new QWidget();
	m_pLabelOrientationXObject = new QLabel(m_pOrientationObject);
	m_pLabelOrientationXObject->setText("X");
	m_pLabelOrientationXObject->setGeometry(QRect(10, 10, 16, 16));
	m_pScrollBarOrientationYObject = new QScrollBar(m_pOrientationObject);
	m_pScrollBarOrientationYObject->setGeometry(QRect(90, 40, 160, 16));
	m_pScrollBarOrientationYObject->setOrientation(Qt::Horizontal);
	m_pLabelOrientationZObject = new QLabel(m_pOrientationObject);
	m_pLabelOrientationZObject->setText("Z");
	m_pLabelOrientationZObject->setGeometry(QRect(10, 70, 16, 16));
	m_pScrollBarOrientationZObject = new QScrollBar(m_pOrientationObject);
	m_pScrollBarOrientationZObject->setGeometry(QRect(90, 70, 160, 16));
	m_pScrollBarOrientationZObject->setOrientation(Qt::Horizontal);
	m_pDoubleSpinBoxOrientationXObject = new QDoubleSpinBox(m_pOrientationObject);
	m_pDoubleSpinBoxOrientationXObject->setGeometry(QRect(20, 10, 62, 22));
	m_pDoubleSpinBoxOrientationYObject = new QDoubleSpinBox(m_pOrientationObject);
	m_pDoubleSpinBoxOrientationYObject->setGeometry(QRect(20, 40, 62, 22));
	m_pScrollBarOrientationXObject = new QScrollBar(m_pOrientationObject);
	m_pScrollBarOrientationXObject->setGeometry(QRect(90, 10, 160, 16));
	m_pScrollBarOrientationXObject->setOrientation(Qt::Horizontal);
	m_pDoubleSpinBoxOrientationZObject = new QDoubleSpinBox(m_pOrientationObject);
	m_pDoubleSpinBoxOrientationZObject->setGeometry(QRect(20, 70, 62, 22));
	m_pLabelOrientationYObject = new QLabel(m_pOrientationObject);
	m_pLabelOrientationYObject->setText("Y");
	m_pLabelOrientationYObject->setGeometry(QRect(10, 40, 16, 16));
	m_pTabWidgetPropertiesObject->addTab(m_pOrientationObject, "Orientation");
	m_pTabWidgetPropertiesObject->setTabText(m_pTabWidgetPropertiesObject->indexOf(m_pOrientationObject), "Orientation");

	m_pLabelPartIndex = new QLabel(m_pGroupBoxEditParts);
	m_pLabelPartIndex->setText("Part Index");
	m_pLabelPartIndex->setGeometry(QRect(10, 50, 51, 16));
	m_pSpinBoxPartIndex = new QSpinBox(m_pGroupBoxEditParts);
	m_pSpinBoxPartIndex->setGeometry(QRect(71, 50, 61, 22));
	m_pPushButtonDeletePart = new QPushButton(m_pGroupBoxEditParts);
	m_pPushButtonDeletePart->setText("Delete Part");
	m_pPushButtonDeletePart->setGeometry(QRect(190, 50, 75, 23));
	
	gridLayout->addWidget(m_pGroupBoxEditParts, 1, 0, 1, 1);
	
	
	gridLayout_5->addWidget(m_pObjectEditorFrame, 0, 0, 1, 1);
	
	m_pDockWidgetSceneEditorObject->setWidget(m_pDockWidgetObjectContents);
	addDockWidget(static_cast<Qt::DockWidgetArea>(2), m_pDockWidgetSceneEditorObject);
}

//===================================================================================

// SIGNALS AND SLOTS

void SceneEditorDlg::updateCategory()	{

	if (m_DB.isOpen())	{
		QSqlQuery tQuery;
		//Check if the Scene defined via the argument is already in the table
		QString tqry = QString("SELECT CategoryName FROM Category");
		tQuery.exec(tqry);
		//See if category includes any item
		if(tQuery.last() == '\0')	{
			std::cout << "Category is empty." << std::endl;
			m_pComboBoxCategoryPose->addItem("<empty>");
		}
		else	{
			//Not empty, navigate through results
			std::cout << "Category is not empty." << std::endl;
			QStringList items;
			QString item;
			if (tQuery.exec(tqry))	{
				//next() advances through results until the last item
				while(tQuery.next())	{
					items.push_back(tQuery.value(0).toString());
				}
				//Populate ComboBox with adequate data
				m_pComboBoxCategoryPose->addItems(items);
			}
		}
		m_DB.close();
	}
	else	{
		qDebug() << "Can't open DB." << m_DB.lastError().text();
	}
}

//------------------------------------------------------------------------------

void SceneEditorDlg::updateProduct(const QString& anCategoryName)	{
	//Clear any content of the ComboBox Product
	m_pComboBoxProductPose->clear();
	m_pComboBoxProductCodePose->clear();
	//connect first to the database for the data
	if (m_DB.open())	{
		QSqlQuery tQuery;
		//Check if the Category defined via the argument has any element
		QString tqry = QString("SELECT Product.ProductName FROM Product "
			"JOIN Category "
			"ON Product.CategoryID=Category.CategoryID "
			"AND Category.CategoryName = '%1'").arg(anCategoryName);
		tQuery.exec(tqry);
		//See if category includes any item
		if(tQuery.last() == '\0')	{
			std::cout << "Category is empty." << std::endl;
			m_pComboBoxProductPose->addItem("<empty>");
		}
		else	{
			//Not empty, navigate through results
			std::cout << "Category is not empty." << std::endl;
			QStringList items;
			QString item;
			if (tQuery.exec(tqry))	{
				//next() advances through results until the last item
				while(tQuery.next())	{
					items.push_back(tQuery.value(0).toString());
				}
				//Populate ComboBox with adequate data
				m_pComboBoxProductPose->addItems(items);
			}
		}
	}
	else	{
		qDebug() << "Can't open DB." << m_DB.lastError().text();
	}
	m_DB.close();
}

//------------------------------------------------------------------------------

void SceneEditorDlg::updateProductID(const QString& anProductName)	{
	//Clear any content of the ComboBox Product
	m_pComboBoxProductCodePose->clear();
	if (m_DB.open())	{
		QSqlQuery tQuery;
		//Check if the Category defined via the argument has any element
		QString tqry = QString("SELECT ProductCode.ProductCodeNumber FROM ProductCode "
			"JOIN Product "
			"ON ProductCode.ProductID=Product.ProductID "
			"AND Product.ProductName = '%1'").arg(anProductName);
		tQuery.exec(tqry);
		//See if category includes any item
		if(tQuery.last() == '\0')	{
			std::cout << "Category is empty." << std::endl;
		}
		else	{
			//Not empty, navigate through results
			std::cout << "Category is not empty." << std::endl;
			QStringList items;
			QString item;
			if (tQuery.exec(tqry))	{
				//next() advances through results until the last item
				while(tQuery.next())	{
					items.push_back(tQuery.value(0).toString());
				}
				//Populate ComboBox with adequate data
				m_pComboBoxProductCodePose->addItems(items);
			}
		}
	}
	else	{
		qDebug() << "Can't open DB." << m_DB.lastError().text();
	}
	m_DB.close();
}

//-------------------------------------------------------------------------------

void SceneEditorDlg::addImage2Widget(const QString& anProductCode)	{
	//connect first to the database for the data
	if (m_DB.open())	{
		QSqlQuery tQuery;
		//Check if the Category defined via the argument has any element
		QString tqry = QString("SELECT ProductCodeImage.ProductCodeImageName FROM ProductCodeImage "
			"JOIN ProductCode "
			"ON ProductCodeImage.ProductCodeID=ProductCode.ProductCodeID "
			"AND ProductCode.ProductCodeNumber = '%1'").arg(anProductCode);
		tQuery.exec(tqry);
		//See if category includes any item
		if(tQuery.last() == '\0')	{
			std::cout << "Product Code is empty." << std::endl;
		}
		else	{
			//Not empty, navigate through results
			std::cout << "Product code is not empty." << std::endl;
			QString path("C:/Projekti/QT/Database/Resources/");
			QString name;
			if (tQuery.exec(tqry))	{
				//next() advances through results until the last item
				while(tQuery.next())	{
					name = tQuery.value(0).toString();
				}
				QImageReader image(path+name);
				m_pImageViewerChoosingPose->setPixmap(QPixmap::fromImageReader(&image));
			}
		}
	}
	else	{
		qDebug() << "Can't open DB." << m_DB.lastError().text();
	}
	m_DB.close();
}

//------------------------------------------------------------------------------
void SceneEditorDlg::saveScene()	{
}

//-----------------------------------------------------------------------------
