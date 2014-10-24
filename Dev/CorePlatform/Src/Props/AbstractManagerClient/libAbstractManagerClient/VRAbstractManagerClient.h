#ifndef VR_ABSTRACT_MANAGER_CLIENT_H
#define VR_ABSTRACT_MANAGER_CLIENT_H

#include "VRServerClientCommands.h"

#include <QObject>

namespace VR	{
	class Client;

	class AbstractManagerClient	: public QObject	{
		Q_OBJECT
	public:
		AbstractManagerClient(QObject * apParent=0);
		virtual ~AbstractManagerClient() = 0;

        const char* className() const;

		struct AbstractManagerClientParams	{
		};

		virtual void requestToServer(
			const enum ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		) = 0;

	protected:
		Client * m_pClient;

	public slots:
		virtual void slotReceiveDataFromServer() = 0;

	signals:
		void done();
	};
}
#endif //VR_ABSTRACT_MANAGER_CLIENT_H