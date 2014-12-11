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
#include <vector>

#include <iostream>

#include <QTimer>

#include "VRAvatarManagerClient.h"

using namespace VR;
using namespace std;
using namespace osg;


//==============================================================================

AvatarManagerClient::AvatarManagerClient(Client * apClient, Avatar * apAvatar, QObject *parent) :
m_pAvatar(apAvatar), AbstractManagerClient(apClient, parent)	{
	m_grpAvatars = new Group();
	//m_pAP = new VR::AnimationPath();

	//Register Avatar to DB
	requestToServer(ServerClientCommands::AVATAR_REGISTER);


	connect(&m_QTimerAvatarSelf, SIGNAL(timeout()), this, SLOT(slotSendAvatarData()));
	m_QTimerAvatarSelf.start(100);

	connect(&m_QTimerAvatarsOthers, SIGNAL(timeout()), this, SLOT(slotRequestAvatarsData()));
	m_QTimerAvatarsOthers.start(850);
}

//------------------------------------------------------------------------------

AvatarManagerClient::~AvatarManagerClient()	{
}

//------------------------------------------------------------------------------

const char* AvatarManagerClient::className() const	{
	return "AvatarManagerClient";
}

//------------------------------------------------------------------------------

void AvatarManagerClient::requestToServer(
const ServerClientCommands::OperationType & aenumOperationType, 
AbstractManagerClientParams * apAbstractManagerClientParams)	{

	AvatarManagerClientParams * pParams = (AvatarManagerClientParams*)apAbstractManagerClientParams;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrInputData;

	int nType = aenumOperationType;

	out << quint64(0) << quint8(nType);

	switch (nType)	{
	case ServerClientCommands::AVATAR_REGISTER:
	case ServerClientCommands::AVATAR_UPDATE:
		{
			QString qstrAvatarName = m_pAvatar->getName().c_str();

			Matrixd mtrxAvatar = m_pAvatar->getMatrix();
			string strMtrx2String = matrix2String(mtrxAvatar);
			QString qstrAvatarMatrix = strMtrx2String.c_str();
			
			out << qstrAvatarName << qstrAvatarMatrix;
			break;
		}
	case ServerClientCommands::OTHER_AVATARS_REQUEST:
		{
			QString qstrAvatarNames="";
			int nI;
			for (nI=0;nI<m_grpAvatars->getNumChildren();nI++)	{
				qstrAvatarNames += (m_grpAvatars->getChild(nI)->getName().c_str() + QString(";"));
			}
			qstrAvatarNames.chop(1);
			out << qstrAvatarNames;
			break;
		}
	default:
		return;
	}
	
	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotSendAvatarData()	{
	requestToServer(ServerClientCommands::AVATAR_UPDATE);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotRequestAvatarsData()	{
	requestToServer(ServerClientCommands::OTHER_AVATARS_REQUEST);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::addAvatar(Avatar * apAvatar)	{
	if (apAvatar == 0)	{
		return;
	}

	m_grpAvatars->addChild(apAvatar);
	
	m_vecAvatarNames.push_back(apAvatar->getName());
	m_pairAvatarNamesAndObjects.push_back(make_pair(apAvatar->getName(),apAvatar));
}

//------------------------------------------------------------------------------

void AvatarManagerClient::removeAvatar(Avatar * apAvatar)	{
	if (apAvatar == 0)	{
		return;
	}

	string strAvatarName = apAvatar->getName();

	m_grpAvatars->removeChild(apAvatar);

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
	m_pairAvatarNamesAndObjects.clear();
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

void AvatarManagerClient::registerAvatarReceived(QDataStream & aDataStreamAvatar)	{
	QString qstrAvatarsData;
	aDataStreamAvatar >> qstrAvatarsData;
}

//------------------------------------------------------------------------------

void AvatarManagerClient::otherAvatarsReceived(QDataStream & aDataStreamAvatar)	{
	QString qstrAvatarsData;
	aDataStreamAvatar >> qstrAvatarsData;

	string strDataFromServer = qstrAvatarsData.toStdString();

	if (strDataFromServer == "")	{
		if (m_grpAvatars->getNumChildren() == 0)
			return;
		clearAll();
		return;
	}

	vector<string> lststrAvatarNameData = splitString(strDataFromServer,";");
	int nSize = lststrAvatarNameData.size() / 2;

	//First: avatarName; Second: avatarMatrix
	vector<pair<string,string>> vecpairAvatarData;

	int nIndexAvatar;
	for (nIndexAvatar=0; nIndexAvatar<nSize-1; nIndexAvatar++)	{
		vecpairAvatarData.push_back(make_pair(lststrAvatarNameData[2*nIndexAvatar],lststrAvatarNameData[2*nIndexAvatar+1]));
	}
	vecpairAvatarData.push_back(make_pair(lststrAvatarNameData[2*(nSize-1)],lststrAvatarNameData[2*nSize-1]));

	//=====================

	bool bSize = (m_pairAvatarNamesAndObjects.size() > 0) ? true : false;
	if (bSize == true)	{
		//Avatars from the DB
		vector<pair<string,string>>::iterator itAvatarData;
		vector<pair<string, ref_ptr<Avatar>>>::iterator itAvatarNames;

		for(itAvatarData= vecpairAvatarData.begin(); itAvatarData != vecpairAvatarData.end(); itAvatarData++)	{
			string strDBItem = itAvatarData->first;

			vector<pair<string, ref_ptr<Avatar>>> vecAvatarNamesTemp;

			//Current avatars in the scene
			for(itAvatarNames = m_pairAvatarNamesAndObjects.begin(); itAvatarNames != m_pairAvatarNamesAndObjects.end(); itAvatarNames++)	{
				if (itAvatarNames->first == strDBItem)	{
					vecAvatarNamesTemp.push_back(make_pair(itAvatarNames->first,itAvatarNames->second));
				} else {
					ref_ptr<Avatar> pAvatar = itAvatarNames->second;
					removeAvatar(pAvatar);
				}
			}
			m_pairAvatarNamesAndObjects = vecAvatarNamesTemp;
		}
	}
	//=====================

	vector<pair<string,string>>::iterator it = vecpairAvatarData.begin();
	for (it; it != vecpairAvatarData.end(); it++, nIndexAvatar++)	{
		string strAvatarName = (*it).first;
		if (strAvatarName == m_pAvatar->getName())
			continue;

		//Reposition active avatars
		vector<string> vecflAvatarData = splitString((*it).second, " ");
		Matrixd mtrxNewMatrixAvatar = vecstr2Matrix(vecflAvatarData);		

		nIndexAvatar = 0;
		vector<string>::iterator itt;
		itt = find(m_vecAvatarNames.begin(), m_vecAvatarNames.end(), strAvatarName);
		if(itt != m_vecAvatarNames.end())	{
			nIndexAvatar = itt - m_vecAvatarNames.begin();
			ref_ptr<Avatar> pAvatar = dynamic_cast<Avatar*>(m_grpAvatars->getChild(nIndexAvatar));
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