#ifndef VR_DATABASE_NETWORK_MANAGER_H
#define VR_DATABASE_NETWORK_MANAGER_H

#include <QObject>

#include <list>
#include <string>

namespace VR	{
	class DatabaseNetworkManager : public QObject	{
		Q_OBJECT

	public:
		DatabaseNetworkManager(QObject *apParent=0);
		~DatabaseNetworkManager();

		bool requestDatabase(std::string & astrDatabaseRequest);
		std::list<std::string> getResult();

	private:
		std::list<std::string> m_lststrResult;
	};
}
#endif //VR_DATABASE_NETWORK_MANAGER_H