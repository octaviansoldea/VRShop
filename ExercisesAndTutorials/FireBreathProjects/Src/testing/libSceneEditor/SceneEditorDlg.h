#ifndef SCENE_EDITOR_DLG_H
#define SCENE_EDITOR_DLG_H

#include <string>

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSpinBox>
#include <QStatusBar>
#include <QTabWidget>
#include <QWidget>
#include <QSqlDatabase>
//#include <qvtkwidget.h>

#include <iostream>

#include <QDebug>
#include <QFile>
#include <qsettings.h>

class SceneEditorDlg : public QMainWindow	{
	Q_OBJECT

public:
	SceneEditorDlg(QWidget *parent = 0);
	~SceneEditorDlg();

private:
	void createMenuBar();
	void createPoseEditor();
	void createQVTK();
	void createChoosing();
	void createProperties();
	void createObjectEditor();


	QSqlDatabase m_DB;
	std::string m_strDBFileName;

private slots:
	void updateCategory();
	void updateProduct(const QString& anCategoryName);
	void updateProductID(const QString& anProductName);
	void addImage2Widget(const QString& anProductCode);

	void insertItem2QVTKWidget(const int& anProductCodePose) {};

	void deleteItem() {};
	void searchItem() {};
	void editItem() {};

	//MenuBar 
	void newScene() {};
	void loadScene() {};
	void saveScene();

public:
    QWidget *m_pCentralWidget;

    QAction *m_pActionNewScene;
    QAction *m_pActionLoadScene;
    QAction *m_pActionSaveScene;
    QAction *m_pActionClose;
    QStatusBar *m_pStatusBar;
    QDockWidget *m_pDockWidgetSceneEditorPose;
    QWidget *m_pDockWidgetPoseContents;
    QGridLayout *gridLayout_2;
    QFrame *m_pPoseEditorFrame;
    QGridLayout *gridLayout_4;
    QGroupBox *m_pGroupBoxChoosingPose;
    QLabel *m_pImageViewerChoosingPose;
    QComboBox *m_pComboBoxCategoryPose;
    QLabel *m_pLabelCategoryPose;
    QComboBox *m_pComboBoxProductPose;
    QLabel *m_pLabelProductPose;
    QPushButton *m_pPushButtonSearchPose;
    QPushButton *m_pPushButtonInsertProduct;
    QGroupBox *m_pGroupBoxSelectLocation;
    QRadioButton *m_pRadioButtonSelectLocation;
    QComboBox *m_pComboBoxProductCodePose;
    QLabel *m_pLabelProductCodePose;
    QPushButton *m_pPushButtonDeleteProduct;
    QPushButton *m_pPushButtonEditProduct;
    QTabWidget *m_pTabWidgetPropertiesPose;
    QWidget *m_pTabLocationPose;
    QDoubleSpinBox *m_pDoubleSpinBoxLocationXPose;
    QDoubleSpinBox *m_pDoubleSpinBoxLocationZPose;
    QLabel *m_pLabelLocationYPose;
    QLabel *m_pLabelLocationZPose;
    QDoubleSpinBox *m_pDoubleSpinBoxLocationYPose;
    QLabel *m_pLabelLocationXPose;
    QScrollBar *m_pScrollBarLocationXPose;
    QScrollBar *m_pScrollBarLocationYPose;
    QScrollBar *m_pScrollBarLocationZPose;
    QWidget *m_pTabOrientationPose;
    QLabel *m_pLabelOrientationX;
    QScrollBar *m_pScrollBarOrientationYPose;
    QLabel *m_pLabelOrientationZ;
    QScrollBar *m_pScrollBarOrientationZPose;
    QDoubleSpinBox *m_pDoubleSpinBoxOrientationXPose;
    QDoubleSpinBox *m_pDoubleSpinBoxOrientationYPose;
    QScrollBar *m_pScrollBarOrientationXPose;
    QDoubleSpinBox *m_pDoubleSpinBoxOrientationZpose;
    QLabel *m_pLabelOrientationY;
//    QVTKWidget *m_pQVTKWidgetSceneEditorPose;
	QWidget *m_pQVTKWidgetSceneEditorPose;
    QDockWidget *m_pDockWidgetSceneEditorObject;
    QWidget *m_pDockWidgetObjectContents;
    QGridLayout *gridLayout_5;
    QFrame *m_pObjectEditorFrame;
    QGridLayout *gridLayout;
    QGroupBox *m_pGroupBoxChoosingObject;
    QListWidget *m_pListWidgetChoosingObject;
    QComboBox *m_pComboBoxCategoryObject;
    QLabel *m_pLabelCategoryObject;
    QComboBox *m_pComboBoxProductObject;
    QLabel *m_pLabelProductObject;
    QPushButton *m_pPushButtonSearchObject;
    QPushButton *m_pPushButtonAddProductObject;
    QLabel *m_pLabelProductCodeObject;
    QLineEdit *m_pLineEditProductCodeObject;
    QPushButton *m_pPushButtonDeleteProductObject;
//    QVTKWidget *m_pQVTKWidgetSceneEditorObject;
	QWidget *m_pQVTKWidgetSceneEditorObject;
    QGridLayout *gridLayout_3;
    QGroupBox *m_pGroupBoxEditParts;
    QComboBox *m_pComboBoxEditPartsShape;
    QLabel *m_pLabelEditPartsShape;
    QPushButton *m_pPushButtonAddPart;
    QGroupBox *m_pGroupBoxTextureMap;
    QListWidget *m_pListWidgetTextureMaps;
    QComboBox *m_pComboBoxTextureMapsName;
    QLabel *m_pLabelTextureMapsName;
    QTabWidget *m_pTabWidgetPropertiesObject;
    QWidget *m_pLocationObject;
    QDoubleSpinBox *m_pDoubleSpinBoxLocationXObject;
    QDoubleSpinBox *m_pDoubleSpinBoxLocationZObject;
    QLabel *m_pLabelLocationYObject;
    QLabel *m_pLabelLocationZObject;
    QDoubleSpinBox *m_pDoubleSpinBoxLocationYObject;
    QLabel *m_pLabelLocationXObject;
    QScrollBar *m_pScrollBarLocationXObject;
    QScrollBar *m_pScrollBarLocationYObject;
    QScrollBar *m_pScrollBarLocationZObject;
    QWidget *m_pOrientationObject;
    QLabel *m_pLabelOrientationXObject;
    QScrollBar *m_pScrollBarOrientationYObject;
    QLabel *m_pLabelOrientationZObject;
    QScrollBar *m_pScrollBarOrientationZObject;
    QDoubleSpinBox *m_pDoubleSpinBoxOrientationXObject;
    QDoubleSpinBox *m_pDoubleSpinBoxOrientationYObject;
    QScrollBar *m_pScrollBarOrientationXObject;
    QDoubleSpinBox *m_pDoubleSpinBoxOrientationZObject;
    QLabel *m_pLabelOrientationYObject;
    QLabel *m_pLabelPartIndex;
    QSpinBox *m_pSpinBoxPartIndex;
    QPushButton *m_pPushButtonDeletePart;
};
#endif // SCENE_EDITOR_DLG_H

