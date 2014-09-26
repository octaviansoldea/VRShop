#include "BasicStringDefinitions.h"
#include "VRBasicOSGOperations.h"

#include "VRAvatar.h"
#include "VRClient.h"

#include "VRAnimationPath.h"

#include <QString>
#include <string>
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

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveAvatarsData()));
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
	//Here establish client - server communication
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrAvatarName = QString(m_pAvatar->getName().c_str());
	out << quint64(0) << quint8('R') << qstrAvatarName;

	/*
		PATTERN:	
			quint64(0)  - size
			quint8('P') - product
			quint8('A') - avatar
			quint8('R') - register avatar
			request
	*/

	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotSendAvatarData()	{
	//Here establish client - server communication
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrAvatarData = QString(m_pAvatar->getName().c_str()) + ";";

	const Matrixd & mtrxAvatar = m_pAvatar->getMatrix();
	int nI,nJ;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			qstrAvatarData += QString(tostr(mtrxAvatar(nI,nJ)).c_str()) + " ";
		}
	}
	qstrAvatarData.chop(1);

	out << quint64(0) << quint8('A') << qstrAvatarData;

	/*
		PATTERN:	
			quint64(0)  - size
			quint8('P') - product
			quint8('A') - avatar
			request
	*/

	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotRequestAvatarsData()	{
	//Here establish client - server communication
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	
	QString qstrAvatarNames;

	int nI;
	for (nI=0;nI<m_grpAvatars->getNumChildren();nI++)	{
		qstrAvatarNames += (m_grpAvatars->getChild(nI)->getName().c_str() + QString(";"));
	}
	qstrAvatarNames.chop(1);

	out << quint64(0) << quint8('a') << qstrAvatarNames;

	/*
		PATTERN:	
			quint64(0)  - size
			quint8('P') - product
			quint8('A') - avatar
			quint8('a') - other avatars' names
			request
	*/

	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AvatarManagerClient::slotReceiveAvatarsData()	{
	string strDataFromServer = m_pClient->m_qstrAvatarsData.toStdString();

	vector<string> & lststrAvatarNameData = splitString(strDataFromServer,";");
	int nSize = lststrAvatarNameData.size() / 2;

	//First: avatarName; Second: avatarMatrix
	vector<pair<string,string>> vecpairAvatarData;
	
	int nI;
	for (nI=0;nI<nSize-1;nI++)	{
		vecpairAvatarData.push_back(make_pair(lststrAvatarNameData[2*nI],lststrAvatarNameData[2*nI+1]));
	}
	vecpairAvatarData.push_back(make_pair(lststrAvatarNameData[2*(nSize-1)],lststrAvatarNameData[2*nSize-1]));

	BasicOSGOperations BOO;
	
	vector<pair<string,string>>::iterator it = vecpairAvatarData.begin();
	for (it; it != vecpairAvatarData.end(); it++, nI++)	{
		if ((*it).first == m_pAvatar->getName())
			continue;

		vector<string> & vecflAvatarData = splitString((*it).second, " ");
		Matrixd mtrxNewMatrixAvatar = BOO.vecstr2Matrix(vecflAvatarData);		
		
		nI = 0;
		vector<string>::iterator itt;
		itt = find(m_vecAvatarNames.begin(), m_vecAvatarNames.end(), (*it).first);
		if(itt != m_vecAvatarNames.end())	{
			nI = itt - m_vecAvatarNames.begin();
			Avatar * pAvatar = dynamic_cast<Avatar*>(m_grpAvatars->getChild(nI));
			Matrixd mtrxOldMatrixAvatar = pAvatar->getMatrix();

			//Both matrices set and attached to the animation
			pAvatar->setAnimation(mtrxOldMatrixAvatar, mtrxNewMatrixAvatar);
		} else {
			//Avatar
			AvatarParams avatarParams;
			avatarParams.m_strAvatarFile = //"D:/Octavian/Companies/VirtualShop/GitHub/VRShop/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
				"D:/Octavian/Companies/VirtualShop/GitHub/VRShop/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
				//"../../../Resources/Models3D/avatarOut.osg";
			avatarParams.m_strAvatarName = (*it).first;

			ref_ptr<Avatar> ppAvatar = new Avatar(&avatarParams);
			ppAvatar->setMatrix(mtrxNewMatrixAvatar);
			addAvatar(ppAvatar);
		}

		//if (m_grpAvatars->getNumChildren() == 0)	{
		//	//Avatar
		//	AvatarParams avatarParams;
		//	avatarParams.m_strAvatarFile = "../../../Resources/Models3D/avatarOut.osg";
		//	avatarParams.m_strAvatarName = (*it).first;

		//	ref_ptr<Avatar> ppAvatar = new Avatar(&avatarParams);
		//	ppAvatar->setMatrix(mtrxNewMatrixAvatar);
		//	addAvatar(ppAvatar);
		//} else {
		//	Avatar * pAvatar = dynamic_cast<Avatar*>(m_grpAvatars->getChild(0));
		//	Matrixd mtrxOldMatrixAvatar = pAvatar->getMatrix();

		//	//Both matrices set and attached to the animation
		//	pAvatar->setAnimation(mtrxOldMatrixAvatar, mtrxNewMatrixAvatar);
		//}
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