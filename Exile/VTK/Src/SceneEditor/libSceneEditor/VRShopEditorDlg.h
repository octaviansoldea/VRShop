#ifndef VR_SHOP_EDITOR_DLG_H
#define VR_SHOP_EDITOR_DLG_H

#include <iostream>
#include <string>

#include <QMainWindow>

#include "ui_VRShopEditorDlg.h"
#include "SceneEditor.h"
#include "ObjectEditor.h"

class VRShopEditorDlg : public QMainWindow, public Ui::VRShopEditorDlg	{
	Q_OBJECT

public:
	VRShopEditorDlg(QMainWindow *parent = 0);
	~VRShopEditorDlg();

private:

	QString openDialog(const char * apchSuffix);
	QString saveDialog(const char * apchSuffix);

	SceneEditor m_SceneEditor;
	ObjectEditor m_ObjectEditor;

private slots:
	void slotLoadScene();
	void slotSaveScene();

	void updateCategory();
	void updateProduct(const QString& aqstrCategoryName);
	void updateProductID(const QString& aqstrProductName);
	void addImage2Widget(const QString& aqstrProductCode);


	void updatePrimitive();
	void updateTexture();
	void addTexture2Widget(const QString& aqstrTextureName);
	
	
	void deleteItem() {};
	void searchItem() {};
	void editItem() {};

	//MenuBar 
	void newScene() {};
	void loadScene() {};
	void saveScene();

};
#endif // VR_SHOP_EDITOR_DLG_H