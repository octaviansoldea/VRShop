#ifndef INPUT_WINDOW_H
#define INPUT_WINDOW_H

#include <qobject>
#include <qlabel>
#include <qlineEdit>
#include <qwidget>
#include <qdialog>

#include <qpushbutton>
#include <qgridlayout>
#include <qhboxlayout>
#include <qvboxlayout>
#include <qstring>

/*************************************************************************************************
* This class provides an interface to get an input data from the user. It is based on the        *
* QDialog and QLineEdit classes. When the form is filled and "Proceed" button is pressed	     *
* the signal is emitted and data about the store, product and price of the product sent forward. *
*************************************************************************************************/

class InputWindow : public QDialog	{
	Q_OBJECT

public:
	InputWindow(QWidget *parent = 0);
	~InputWindow();

signals:
	void inputDataChanged(QString &astrStore, QString &astrproduct, QString &astrprice);

public slots:
	void newInquiry();

public:
	QWidget		*widget;

	//Input variables
	QLineEdit	*storeLineEdit;
	QLineEdit	*productLineEdit;
	QLineEdit	*priceLineEdit;

private:
	//Proceed/quit
	QPushButton	*cancelButton;
	QPushButton	*okButton;

	//Input variables
	QLabel		*labelStore;
	QLabel		*labelProduct;
	QLabel		*labelPrice;

	//Create functions
	void createLayout();
	void createWidgets();
	void tabOrder();

	//Layouts
	QHBoxLayout *bottomLayout;
	QGridLayout *gridLayout;
	QVBoxLayout	*mainLayout;
};
#endif // INPUT_WINDOW_H
