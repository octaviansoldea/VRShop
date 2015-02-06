#ifndef VR_AGENT_INTERFACE_H
#define VR_AGENT_INTERFACE_H

#include <QObject>

class QFrame;
class QToolButton;
class QLineEdit;
class QPushButton;

namespace VR	{
	class AbstractUser;
	class Client;

	class AgentInterface : public QObject	{
		Q_OBJECT
	public:
		AgentInterface(
			QFrame * apFrameSettings,
			QToolButton * apToolButtonUser,
			QLineEdit * apLineEditPassword,
			QLineEdit * apLineEditUserName,
			QPushButton * apPushButtonSignIn,
			QPushButton * apPushButtonSignOut,
			QPushButton * apPushButtonRemoveAccount,
			QPushButton * apPushButtonChangeSettings,
			AbstractUser * apAbstractUser,
			Client * apClient
		);	//End of constructor

		~AgentInterface();

	private slots:
		void slotUserClicked(bool abIsProfileVisible);
		void slotSignUp();
		void slotSignIn();
		void slotSignOut();
		void slotRemoveAccount();
		void slotChangeSettings();

		void slotSignedIn();

	private:
		QFrame * m_pFrameSettings;
		QToolButton * m_pToolButtonUser;
		QLineEdit * m_pLineEditPassword;
		QLineEdit * m_pLineEditUserName;
		QPushButton * m_pPushButtonSignIn;
		QPushButton * m_pPushButtonSignOut;
		QPushButton * m_pPushButtonRemoveAccount;
		QPushButton * m_pPushButtonChangeSettings;
		AbstractUser * m_pAbstractUser;
		Client * m_pClient;


	public:
		void signInRespond(QDataStream & aDataStream);
		void signUpRespond(QDataStream & aDataStream);
		void signOutRespond(QDataStream & aDataStream);
		void modifyAccountRespond(QDataStream & aDataStream);
	};
}
#endif //VR_AGENT_INTERFACE_H