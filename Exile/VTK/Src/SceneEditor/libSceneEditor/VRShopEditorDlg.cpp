#include "VRShopEditorDlg.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QImageReader>
#include <QFileDialog>

VRShopEditorDlg::VRShopEditorDlg(QMainWindow *parent) : QMainWindow(parent)	
{
	setupUi(this);

	m_SceneEditor.setQVTKWidgets(m_pQVTKWidgetSceneEditorPose);
	m_ObjectEditor.setQVTKWidgets(m_pQVTKWidgetSceneEditorObject);

	setWindowTitle(tr("VR Shop Editor Dialog"));

	connect(actionLoadScene, SIGNAL(triggered()), this, SLOT(slotLoadScene()));
	connect(actionSaveScene, SIGNAL(triggered()), this, SLOT(slotSaveScene()));

	//Exit application
	connect(actionExit,SIGNAL(triggered()), this, SLOT(close()));

	//Calling functions
	updateCategory();
	connect(m_pComboBoxCategoryPose, SIGNAL(highlighted(const QString &)), this, SLOT(updateProduct(const QString &)));
	connect(m_pComboBoxProductPose, SIGNAL(highlighted(const QString &)), this, SLOT(updateProductID(const QString &)));
	connect(m_pComboBoxProductCodePose, SIGNAL(highlighted(const QString &)), this, SLOT(addImage2Widget(const QString &)));

	updateTexture();
	connect(m_pComboBoxTextureMapsName, SIGNAL(highlighted(const QString &)), this, SLOT(addTexture2Widget(const QString &)));

	updatePrimitive();
}

//--------------------------------------------------------------------------------

VRShopEditorDlg::~VRShopEditorDlg() {
}

//--------------------------------------------------------------------------------

QString VRShopEditorDlg::openDialog(const char * apchSuffix) {
	QString qstrFileName = QFileDialog::getOpenFileName(this, 
		tr("Open File"),
		//tr("E:/Octavian/CMIND/test_input/Patient")
		tr("D:/WaitingList/Hippocampus/test_input/Patient")
		, apchSuffix);

	return(qstrFileName);
}

QString VRShopEditorDlg::saveDialog(const char * apchSuffix) {
	QString qstrFileName = QFileDialog::getSaveFileName(this, 
		tr("Save file"),
		tr(".\\"), apchSuffix);
	return(qstrFileName);
}

void VRShopEditorDlg::slotLoadScene() {
	QString qstrFileName = openDialog("*.* \n *.vtk *.hdr *.nii \n* ");
}

void VRShopEditorDlg::slotSaveScene() {
	QString qstrFileName = saveDialog("*.txt");
}

//===================================================================================

// SIGNALS AND SLOTS

void VRShopEditorDlg::updateCategory()	{
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
}

//------------------------------------------------------------------------------

void VRShopEditorDlg::updateProduct(const QString& aqstrCategoryName)	{
	//Clear any content of the ComboBox Product
	m_pComboBoxProductPose->clear();
	m_pComboBoxProductCodePose->clear();
	QSqlQuery tQuery;
	//Check if the Category defined via the argument has any element
	QString tqry = QString("SELECT Product.ProductName FROM Product "
		"JOIN Category "
		"ON Product.CategoryID=Category.CategoryID "
		"AND Category.CategoryName = '%1'").arg(aqstrCategoryName);
	tQuery.exec(tqry);
	//See if category includes any item
	if(tQuery.last() == '\0')	{
		std::cout << "Product is empty." << std::endl;
		m_pComboBoxProductPose->addItem("<empty>");
	}
	else	{
		//Not empty, navigate through results
		std::cout << "Product is not empty." << std::endl;
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

//------------------------------------------------------------------------------

void VRShopEditorDlg::updateProductID(const QString& aqstrProductName)	{
	//Clear any content of the ComboBox Product
	m_pComboBoxProductCodePose->clear();
	QSqlQuery tQuery;
	//Check if the Category defined via the argument has any element
	QString tqry = QString("SELECT ProductCode.ProductCodeNumber FROM ProductCode "
		"JOIN Product "
		"ON ProductCode.ProductID=Product.ProductID "
		"AND Product.ProductName = '%1'").arg(aqstrProductName);
	tQuery.exec(tqry);
	//See if category includes any item
	if(tQuery.last() == '\0')	{
		std::cout << "Product ID is empty." << std::endl;
		m_pComboBoxProductCodePose->addItem("<empty>");
	}
	else	{
		//Not empty, navigate through results
		std::cout << "Product ID is not empty." << std::endl;
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

//-------------------------------------------------------------------------------

void VRShopEditorDlg::addImage2Widget(const QString& aqstrProductCode)	{
	QSqlQuery tQuery;
	//Check if the Category defined via the argument has any element
	QString tqry = QString("SELECT ProductCodeImage.ProductCodeImageName FROM ProductCodeImage "
		"JOIN ProductCode "
		"ON ProductCodeImage.ProductCodeID=ProductCode.ProductCodeID "
		"AND ProductCode.ProductCodeNumber = '%1'").arg(aqstrProductCode);
	tQuery.exec(tqry);
	//See if category includes any item
	if(tQuery.last() == '\0')	{
		std::cout << "Product image is empty." << std::endl;
	}
	else	{
		//Not empty, navigate through results
		std::cout << "Product image is not empty." << std::endl;
		QString name;
		if (tQuery.exec(tqry))	{
			//next() advances through results until the last item
			while(tQuery.next())	{
				name = tQuery.value(0).toString();
			}
			FunctorPathResource f;
			QImageReader image(f("/Images/").c_str()+ name);
			m_pImageViewerChoosingPose->setPixmap(QPixmap::fromImageReader(&image));
		}
	}
}

//------------------------------------------------------------------------------

void VRShopEditorDlg::updateTexture()	{
	QSqlQuery tQuery;
	//Check if the Scene defined via the argument is already in the table
	QString tqry = QString("SELECT TextureName FROM Texture");
	tQuery.exec(tqry);
	//See if category includes any item
	if(tQuery.last() == '\0')	{
		std::cout << "Texture is empty." << std::endl;
		m_pComboBoxTextureMapsName->addItem("<empty>");
	}
	else	{
		//Not empty, navigate through results
		std::cout << "Texture is not empty." << std::endl;
		QStringList items;
		QString item;
		if (tQuery.exec(tqry))	{
			//next() advances through results until the last item
			while(tQuery.next())	{
				items.push_back(tQuery.value(0).toString());
			}
			//Populate ComboBox with adequate data
			m_pComboBoxTextureMapsName->addItems(items);
		}
	}
}

//-----------------------------------------------------------------------------

void VRShopEditorDlg::addTexture2Widget(const QString& aqstrTextureName)	{
	QSqlQuery tQuery;
	//Check if the Category defined via the argument has any element
	QString tqry = QString("SELECT Texture.TextureName FROM Texture "
		"WHERE Texture.TextureName = '%1'").arg(aqstrTextureName);
	tQuery.exec(tqry);
	//See if category includes any item
	if(tQuery.last() == '\0')	{
		std::cout << "Texture is empty." << std::endl;
	}
	else	{
		//Not empty, navigate through results
		std::cout << "Texture is not empty." << std::endl;
		QString name;
		if (tQuery.exec(tqry))	{
			//next() advances through results until the last item
			while(tQuery.next())	{
				name = tQuery.value(0).toString();
			}
			FunctorPathResource f;
			QImageReader image(f("/Textures/").c_str()+ name);
			m_pImageViewerTextureName->setPixmap(QPixmap::fromImageReader(&image));
		}
	}

}

//-----------------------------------------------------------------------------

void VRShopEditorDlg::updatePrimitive()	{
	QSqlQuery tQuery;
	//Check if the Scene defined via the argument is already in the table
	QString tqry = QString("SELECT PrimitiveName FROM Primitive");
	tQuery.exec(tqry);
	//See if category includes any item
	if(tQuery.last() == '\0')	{
		std::cout << "Primitive is empty." << std::endl;
		m_pComboBoxEditPartsPrimitive->addItem("<empty>");
	}
	else	{
		//Not empty, navigate through results
		std::cout << "Primitive is not empty." << std::endl;
		QStringList items;
		QString item;
		if (tQuery.exec(tqry))	{
			//next() advances through results until the last item
			while(tQuery.next())	{
				items.push_back(tQuery.value(0).toString());
			}
			//Populate ComboBox with adequate data
			m_pComboBoxEditPartsPrimitive->addItems(items);
		}
	}
}

//-----------------------------------------------------------------------------

void VRShopEditorDlg::saveScene()	{
}

