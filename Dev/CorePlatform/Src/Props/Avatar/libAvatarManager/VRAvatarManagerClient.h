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

#include <QString>

#include <QTimer>

#include "VRAbstractManagerClient.h"

#include "VRServerClientCommands.h"


namespace VR {
	class Avatar;
	class AnimationPath;

	class AvatarManagerClient : public AbstractManagerClient	{
		Q_OBJECT
	public:
		AvatarManagerClient(Avatar * apAvatar, QObject *parent=0);
		virtual ~AvatarManagerClient();

		const char* className() const;

		struct AvatarManagerClientParams : public AbstractManagerClientParams {
			std::string m_strAvatarName;
		};


		virtual void requestToServer(
			const enum ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

		virtual void slotReceiveDataFromServer();


		void addAvatar(Avatar * apAvatar);
		void removeAvatar(Avatar * apAvatar);
		void clearAll();
		osg::ref_ptr<osg::Group> getAvatars();	//A group of others' avatars in the client's scene

		int getNumberOfAvatars() const;

	private:
		Avatar * m_pAvatar;	//Client's avatar
		QTimer m_QTimerAvatarSelf;

		osg::ref_ptr<osg::Group> m_grpAvatars;	//A group of others' avatars in the client's scene
		QTimer m_QTimerAvatarsOthers;

		int m_nMaxNrOfAvatars;

	private slots:
		void slotSendAvatarData();
		void slotRequestAvatarsData();

	private:
		std::vector<std::string> m_vecAvatarNames;
	};
}
#endif //VR_AVATAR_MANAGER_CLIENT_H