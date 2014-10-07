#ifndef VR_AVATAR_MANAGER_CLIENT_H
#define VR_AVATAR_MANAGER_CLIENT_H

/*
	This class manages avatars present in the client's scene.

	TASKS:
		- regularly reports client's avatar matrix to the Server
		- regularly asks for other avatars' matrices and updates their positioning
*/

#include <list>

#include <osg/Group>

#include <QObject>
#include <QString>

#include <QTimer>

namespace VR {
	class Avatar;
	class Client;
	class AnimationPath;

	class AvatarManagerClient : public QObject	{
		Q_OBJECT
	public:
		AvatarManagerClient(Avatar * apAvatar);
		~AvatarManagerClient();

		const char* className() const;

		void addAvatar(Avatar * apAvatar);
		void removeAvatar(Avatar * apAvatar);
		void clearAll();
		osg::ref_ptr<osg::Group> getAvatars();	//A group of others' avatars in the client's scene

		int getNumberOfAvatars() const;

	private:
		Client * m_pClient;
		Avatar * m_pAvatar;	//Client's avatar
		QTimer m_QTimerAvatarSelf;

		osg::ref_ptr<osg::Group> m_grpAvatars;	//A group of others' avatars in the client's scene
		QTimer m_QTimerAvatarsOthers;

		int m_nMaxNrOfAvatars;

		void registerAvatar();

		QByteArray dataStreamBlock(const quint8 & astrType, QString & aqstrInputData);

	private slots:
		void slotSendAvatarData();
		void slotRequestAvatarsData();
		void slotReceiveDataFromServer();

	private:
		std::vector<std::string> m_vecAvatarNames;
	};
}
#endif //VR_AVATAR_MANAGER_CLIENT_H