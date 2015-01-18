#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QByteArray>

#include "VRBasicQtOperations.h"

using namespace VR;
using namespace std;

void BasicQtOperations::printError(const QString & aqstrMessage) {
	QMessageBox msgBox;
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Error window");
	int nRes = msgBox.exec();
}

//-----------------------------------------------------------------------------

void BasicQtOperations::printWarning(const QString & aqstrMessage) {
	QMessageBox msgBox;
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Warning window");
	int nRes = msgBox.exec();
}

//-----------------------------------------------------------------------------

int BasicQtOperations::getMsgBox(MESSAGE_BOX_TYPE aenumMESSAGE_BOX_TYPE, QMessageBox & aMsgBox)	{
	switch (aenumMESSAGE_BOX_TYPE)	{
	case OPEN_NEW_FILE:
		{
			aMsgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
			aMsgBox.setText("Changes to the current file will be lost if not saved. \n\nDo you want to save them?");
			aMsgBox.setWindowTitle("Warning window");

			break;
		}
	case FILE_ALREADY_EXISTS:
		{
			aMsgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
			aMsgBox.setText("File already exists. \n Press OK to overwrite it, else press NO.");
			aMsgBox.setWindowTitle("Warning window");

			break;
		}
	}

	return aMsgBox.exec();
}

//-----------------------------------------------------------------------------

bool BasicQtOperations::QtFileOperation(string & astrFileName, FILE_OPERATION aenumFileOperation)	{
	QFile file(astrFileName.c_str());
	QIODevice::OpenMode opMode;

	switch (aenumFileOperation)	{
	case FILE_OPEN:
		{
			opMode = QIODevice::ReadOnly | QIODevice::Text;
			break;
		}
	case FILE_OPEN_TRUNCATE:
		{
			opMode = QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate;
			break;
		}
	default:
		break;
	}
			
	file.open(opMode);
	file.close();

	return true;
}

//-----------------------------------------------------------------------------

string BasicQtOperations::openSaveDialog(const char * apchDBName,QWidget * apParent, bool abOpen) {
	string strFileName;
	strFileName = (abOpen == true) 
		? QFileDialog::getOpenFileName(apParent, "Open File",".", apchDBName).toStdString()
		: QFileDialog::getSaveFileName(apParent, "Save file",".\\", apchDBName).toStdString();

	return(strFileName);
}

//-----------------------------------------------------------------------------

bool BasicQtOperations::fileTransferRead(const std::string & astrFileName, QByteArray & aFileData)	{
	QDataStream out(&aFileData, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	out.setFloatingPointPrecision(QDataStream::SinglePrecision);

	QFile fileScene(astrFileName.c_str());
	if(!fileScene.open(QIODevice::ReadOnly))	{
		return 0;
	}
	QByteArray bytes = fileScene.readAll();
	fileScene.close();

	out << quint64(0) << bytes;	//Size of the package

	bool bRes = out.device()->seek(0);
	quint64 unTotalToWrite = (quint64)(aFileData.size());
	out << (quint64)(unTotalToWrite - sizeof(quint64));

	return true;
}

//-----------------------------------------------------------------------------

bool BasicQtOperations::fileTransferWrite(const std::string & astrFileName, QByteArray & aFileData)	{
	QDataStream out(&aFileData,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint32 nFileSize;
	out >> nFileSize;	//QByteArray always starts with a "quint32" additional value

	QFile fileScene(astrFileName.c_str());

	if(!(fileScene.open(QIODevice::Append)))	{
		return false;
	} else {
		QByteArray read = out.device()->readAll();

		int nSize = read.size();

		fileScene.write(read);
		fileScene.close();
	}
	return true;
}