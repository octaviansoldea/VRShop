#ifndef VR_BASIC_QT_OPERATIONS_H
#define VR_BASIC_QT_OPERATIONS_H

#include <QString>
#include <string>
#include <QMessageBox>

namespace VR	{
	class BasicQtOperations	{
	public:
		static void printError(const QString & aqstrMessage);
		static void printWarning(const QString & aqstrMessage);

		enum MESSAGE_BOX_TYPE	{
			OPEN_NEW_FILE = 0,
			FILE_ALREADY_EXISTS
		};

		static int getMsgBox(MESSAGE_BOX_TYPE aenumMESSAGE_BOX_TYPE, QMessageBox & aMsgBox);

		enum FILE_OPERATION	{
			FILE_OPEN = 0,
			FILE_OPEN_TRUNCATE
		};

		static bool QtFileOperation(std::string & astrFileName, enum FILE_OPERATION aenumFileOperation);
	};
}

#endif //VR_BASIC_QT_OPERATIONS_H