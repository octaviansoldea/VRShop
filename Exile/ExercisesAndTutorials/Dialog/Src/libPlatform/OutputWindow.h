#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include "Database.h"
#include "InputWindow.h"
#include "DataModel.h"
#include <QSpacerItem>

class OutputWindow : public QDialog	{
	Q_OBJECT

public:
	OutputWindow(QWidget *parent = 0);
	~OutputWindow();

private slots:
	void newData(QString &astrStore, QString &astrProduct, QString &astrPrice);
	void resumeSearch();

private:
	//instantiation of classes
	InputWindow *inputWindow;
	Database *database;
	DataModel *dataModel;

	//Labels
	QLabel *yourPriceLabel;
	QLabel *yourPrice;
	QLabel *bestPriceLabel;
	QLabel *bestPrice;

	//Resume/quit
	QPushButton	*cancelButton;
	QPushButton	*resumeButton;

	//Layouts
	QGridLayout *gridLayout;
	QHBoxLayout *bottomLayout;
	QVBoxLayout *commonLayout;

	//void functions
	void createWidget();
	void createLayout();

	//member parameters
	QString m_strStore;
	QString m_strProduct;
	QString m_strPrice;
};
#endif // OUTPUT_WINDOW_H
