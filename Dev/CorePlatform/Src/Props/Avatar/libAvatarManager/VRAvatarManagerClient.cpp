#include "BasicDefinitions.h"
#include "BasicStringDefinitions.h"
#include "VRBasicOSGOperations.h"

#include "VRServerClientCommands.h"

#include "VRAvatar.h"
#include "VRClient.h"

#include "VRAnimationPath.h"

#include <QString>
#include <string>
#include <list>

#include <iostream>

#include <QTimer>

#include "VRAvatarManagerClient.h"

using namespace VR;
using namespace std;
using namespace osg;


//==============================================================================

AvatarManagerClient::AvatarManagerClient(Avatar * apAvatar) :
m_pAvatar(apAvatar)	{
	m_pClient = new Client;

	m_grpAvatars = new Group();
	//m_pAP = new VR::AnimationPath();

	//Register Avatar to DB
	registerAvatar();

	connect(&m_QTimerAvatarSelf, SIGNAL(timeout()), this, SLOT(slotSendAvatarData()));
	m_QTimerAvatarSelf.start(100);

	connect(&m_QTimerAvatarsOthers, SIGNAL(timeout()), this, SLOT(slotRequestAvatarsData()));
	m_QTimerAvatarsOthers.start(850);

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveDataFromServer()));
}

//------------------------------------------------------------------------------

AvatarManagerClient::~AvatarManagerClient()	{
	delete m_pClient;
}

//------------------------------------------------------------------------------

const char* AvatarManagerClient::className() const	{
	return "AvatarManagerClient";
}

//------------------------------------------------------------------------------

void AvatarManagerClient::registerAvatar()	{
	QString qstrAvatarData = QString(m_pAvatar->getName().c_str()) + ";";

	Matrixd mtrxAvatar = m_pAvatar->getMatrix();

	string strMtrx2String = matrix2String(mtrxAvatar);
	qstrAvatarData += strMtrx2String.c_str();

	char chType = ServerClientCommands::getOperationType(ServerClientCommands::AVATAR_REGISTER);

	QByteArray & block = dataStreamBlock(chType,qstrAvatarData);
	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotSendAvatarData()	{
	QString qstrAvatarData = QString(m_pAvatar->getName().c_str()) + ";";

	Matrixd mtrxAvatar = m_pAvatar->getMatrix();

	string strMtrx2String = matrix2String(mtrxAvatar);
	qstrAvatarData += strMtrx2String.c_str();

	char chType = ServerClientCommands::getOperationType(ServerClientCommands::AVATAR_UPDATE);

	QByteArray & block = dataStreamBlock(chType,qstrAvatarData);
	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotRequestAvatarsData()	{
	QString qstrAvatarNames;

	int nI;
	for (nI=0;nI<m_grpAvatars->getNumChildren();nI++)	{
		qstrAvatarNames += (m_grpAvatars->getChild(nI)->getName().c_str() + QString(";"));
	}
	qstrAvatarNames.chop(1);

	char chType = ServerClientCommands::getOperationType(ServerClientCommands::OTHER_AVATARS_REQUEST);

	QByteArray & block = dataStreamBlock(chType,qstrAvatarNames);
	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotReceiveDataFromServer()	{
	QByteArray & data = m_pClient->getTransmittedData();

	QDataStream out(&data,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint8 nType;	//Type of the data received
	out >> nType;

	if (nType == ServerClientCommands::getOperationType(ServerClientCommands::AVATAR_REGISTER))	{
		//Do nothing
		return;
	} else if (nType == ServerClientCommands::getOperationType(ServerClientCommands::AVATAR_UPDATE))	{
		//Do nothing
		return;
	} else if (nType == ServerClientCommands::getOperationType(ServerClientCommands::OTHER_AVATARS_REQUEST))	{

		QString qstrAvatarsData;
		out >> qstrAvatarsData;

		string strDataFromServer = qstrAvatarsData.toStdString();

		vector<string> & lststrAvatarNameData = splitString(strDataFromServer,";");
		int nSize = lststrAvatarNameData.size() / 2;

		//First: avatarName; Second: avatarMatrix
		vector<pair<string,string>> vecpairAvatarData;

		int nIndexAvatar;
		for (nIndexAvatar=0; nIndexAvatar<nSize-1; nIndexAvatar++)	{
			vecpairAvatarData.push_back(make_pair(lststrAvatarNameData[2*nIndexAvatar],lststrAvatarNameData[2*nIndexAvatar+1]));
		}
		vecpairAvatarData.push_back(make_pair(lststrAvatarNameData[2*(nSize-1)],lststrAvatarNameData[2*nSize-1]));


		vector<pair<string,string>>::iterator it = vecpairAvatarData.begin();
		for (it; it != vecpairAvatarData.end(); it++, nIndexAvatar++)	{
			string strAvatarName = (*it).first;
			if (strAvatarName == m_pAvatar->getName())
				continue;

			//Reposition active avatars
			vector<string> & vecflAvatarData = splitString((*it).second, " ");
			Matrixd mtrxNewMatrixAvatar = vecstr2Matrix(vecflAvatarData);		

			nIndexAvatar = 0;
			vector<string>::iterator itt;
			itt = find(m_vecAvatarNames.begin(), m_vecAvatarNames.end(), strAvatarName);
			if(itt != m_vecAvatarNames.end())	{
				nIndexAvatar = itt - m_vecAvatarNames.begin();
				Avatar * pAvatar = dynamic_cast<Avatar*>(m_grpAvatars->getChild(nIndexAvatar));
				Matrixd mtrxOldMatrixAvatar = pAvatar->getMatrix();

				if(distanceL2Matrixd(mtrxOldMatrixAvatar, mtrxNewMatrixAvatar) > EPS) {
					pAvatar->setAnimation(mtrxOldMatrixAvatar, mtrxNewMatrixAvatar);
				}
			} else {
				//Avatar
				AvatarParams avatarParams;
				avatarParams.m_strAvatarFile = 
					//"D:/Octavian/Companies/VirtualShop/GitHub/VRShop/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
					"C:/Projekti/VRShop/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
				//"../../../Resources/Models3D/avatarOut.osg";
				avatarParams.m_strAvatarName = strAvatarName;

				ref_ptr<Avatar> ppAvatar = new Avatar(&avatarParams);
				ppAvatar->setMatrix(mtrxNewMatrixAvatar);
				addAvatar(ppAvatar);
			}
		}
	}
}

//------------------------------------------------------------------------------

void AvatarManagerClient::addAvatar(Avatar * apAvatar)	{
	if (apAvatar == 0)	{
		return;
	}

	m_grpAvatars->addChild(apAvatar);
	
	m_vecAvatarNames.push_back(apAvatar->getName());
}

//------------------------------------------------------------------------------

void AvatarManagerClient::removeAvatar(Avatar * apAvatar)	{
	if (apAvatar == 0)	{
		return;
	}

	m_grpAvatars->removeChild(apAvatar);

	string strAvatarName = apAvatar->getName();
	vector <string>::const_iterator it = m_vecAvatarNames.begin();
	for (it; it != m_vecAvatarNames.end(); it++)	{
		if (*it==strAvatarName)	{
			m_vecAvatarNames.erase(it);
			return;
		}
	}
}

//------------------------------------------------------------------------------

void AvatarManagerClient::clearAll()	{
	m_grpAvatars->removeChildren(0,m_grpAvatars->getNumChildren());
	m_vecAvatarNames.clear();
}

//------------------------------------------------------------------------------

int AvatarManagerClient::getNumberOfAvatars() const	{
	return m_grpAvatars->getNumChildren();
}

//------------------------------------------------------------------------------

ref_ptr<Group> AvatarManagerClient::getAvatars()	{
	return m_grpAvatars;
}

//------------------------------------------------------------------------------

QByteArray AvatarManagerClient::dataStreamBlock(const quint8 & astrType, QString & aqstrInputData)	{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	out << quint64(0) << astrType << aqstrInputData;
	
	return block;
}