#ifndef VR_DATABASE_NETWORK_MANAGER_H
#define VR_DATABASE_NETWORK_MANAGER_H

#include <list>
#include <string>

#include <QByteArray>

namespace VR	{
	class DatabaseNetworkManager	{

	public:
		DatabaseNetworkManager();
		~DatabaseNetworkManager();

		static QByteArray databaseRequest(QByteArray & aData);
	};
}
#endif //VR_DATABASE_NETWORK_MANAGER_H