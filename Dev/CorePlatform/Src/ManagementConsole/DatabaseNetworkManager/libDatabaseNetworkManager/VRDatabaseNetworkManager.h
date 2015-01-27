#ifndef VR_DATABASE_NETWORK_MANAGER_H
#define VR_DATABASE_NETWORK_MANAGER_H

#include <QByteArray>

namespace VR	{
	class DatabaseNetworkManager	{

	public:
		static QByteArray databaseRequest(QByteArray & aData);

		static void checkDatabaseTables();
		static void checkAvatarActivity();
		static void printOrderList();

		static void clientQuitApplication(const int & anUserID);
	};
}
#endif //VR_DATABASE_NETWORK_MANAGER_H