#ifndef VR_FILE_MANAGER_H
#define VR_FILE_MANAGER_H

#include <QObject>
#include <string>
#include <QString>

namespace VR	{
	class FileManager : public QObject	{
		Q_OBJECT
	public:
		FileManager();

		bool newProject();
		bool openDB();
		bool saveDB();
		bool saveAsDB();
		bool closeDB();

	private:
		QString openDialog(const char * apchDBName);
		QString saveDialog(const char * apchDBName);
	};
}
#endif //VR_FILE_MANAGER_H