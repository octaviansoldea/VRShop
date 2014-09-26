#ifndef VR_AGENT_INTERFACE_H
#define VR_AGENT_INTERFACE_H

#include <QObject>

class QFrame;
class QToolButton;
class QLineEdit;
class QPushButton;

namespace VR	{
	class AbstractUser;

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
			AbstractUser * apAbstractUser
		);	//End of constructor

		~AgentInterface();

	private slots:
		void slotUserClicked(bool abIsProfileVisible);
		void slotSignIn();
		void slotSignOut();
		void slotRemoveAccount();
		void slotChangeSettings();

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
	};
}
#endif //VR_AGENT_INTERFACE_H