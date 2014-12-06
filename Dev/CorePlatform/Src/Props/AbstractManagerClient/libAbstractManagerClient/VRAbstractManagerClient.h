#ifndef VR_ABSTRACT_MANAGER_CLIENT_H
#define VR_ABSTRACT_MANAGER_CLIENT_H

#include "VRServerClientCommands.h"

#include <QDataStream>

#include <QObject>

namespace VR	{
	class Client;

	class AbstractManagerClient	: public QObject	{
		Q_OBJECT
	public:
		AbstractManagerClient(Client * apClient, QObject * apParent=0);
		virtual ~AbstractManagerClient() = 0;

        const char* className() const;

		struct AbstractManagerClientParams	{
		};

	protected:
		virtual void requestToServer(
			const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		) = 0;

		Client * m_pClient;
		

	signals:
		void done();
	};
}
#endif //VR_ABSTRACT_MANAGER_CLIENT_H