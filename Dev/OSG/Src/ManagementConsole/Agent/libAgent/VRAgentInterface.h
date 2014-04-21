#ifndef VR_AGENT_INTERFACE_H
#define VR_AGENT_INTERFACE_H

#include <QObject>

class QFrame;
class QToolButton;
class QLineEdit;
class QPushButton;

namespace VR	{
	class AgentInterface : public QObject	{
		Q_OBJECT
	public:
		AgentInterface(
			QFrame * apFrameSettings,
			QToolButton * apToolButtonUser,
			QLineEdit * apLineEditPassword,
			QLineEdit * apLineEditUserName,
			QPushButton * apPushButtonSignIn
		);	//End of constructor

		~AgentInterface();

	private slots:
		void slotUserClicked(bool abIndicator);
		void slotSignUp();

	private:
		QFrame * m_pFrameSettings;
		QToolButton * m_pToolButtonUser;
		QLineEdit * m_pLineEditPassword;
		QLineEdit * m_pLineEditUserName;
		QPushButton * m_pPushButtonSignIn;
	};
}
#endif //VR_AGENT_INTERFACE_H