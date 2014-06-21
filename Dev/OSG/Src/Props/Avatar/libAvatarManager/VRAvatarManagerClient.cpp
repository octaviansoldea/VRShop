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

//#define DEBUG_AVATARS 

//==============================================================================

AvatarManagerClient::AvatarManagerClient(Avatar * apAvatar) :
m_pAvatar(apAvatar)	{
	m_pClient = new Client;
	m_grpAvatars = new Group();
	m_pAP = new VR::AnimationPath();

	//Client reports position of his avatar
	//QTimer *pTimer1 = new QTimer(this);
	//connect(pTimer1, SIGNAL(timeout()), this, SLOT(slotSendAvatarData2Server()));
	//pTimer1->start(10000);

	//Client gets matrices of avatars in his view
	/*QTimer *pTimer2 = new QTimer(this);
	connect(pTimer2, SIGNAL(timeout()), this, SLOT(slotRequestAvatarsDataFromServer()));
	pTimer2->start(10000);*/

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveAvatarsData()));

#ifdef DEBUG_AVATARS

	AvatarParams avatarParams;
	avatarParams.m_strAvatarFile = "../../../Resources/Models3D/avatarOut.osg";
	avatarParams.m_strAvatarName = "avatar_1";
	ref_ptr<Avatar> pAvatar1 = new Avatar(&avatarParams);
	addAvatar(pAvatar1);

	avatarParams.m_strAvatarName = "avatar_2";
	ref_ptr<Avatar> pAvatar2 = new Avatar(&avatarParams);
	addAvatar(pAvatar2);

#endif //DEBUG_AVATARS
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

void AvatarManagerClient::slotSendAvatarData2Server()	{
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

void AvatarManagerClient::slotRequestAvatarsDataFromServer()	{
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
	QDataStream out(&m_pClient->getTcpSocket());
	out.setVersion(QDataStream::Qt_4_8);
	QTcpSocket * pSocket = static_cast<QTcpSocket*>(out.device());

	int nBytesAvaliable = pSocket->bytesAvailable();

	QString qstrDataFromServer;
	out >> qstrDataFromServer;

	string & strDataFromServer = qstrDataFromServer.toStdString();

	if (strDataFromServer.empty())	{
		cout << "No data was returned." << endl;
		return;
	}

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
	
	nI = 0;
	vector<pair<string,string>>::iterator it = vecpairAvatarData.begin();
	for (it; it != vecpairAvatarData.end(); it++, nI++)	{
		vector<string> & vecflAvatarData = splitString((*it).second, " ");
		const Matrixd & mtrxNewMatrixAvatar = BOO.vecstr2Matrix(vecflAvatarData);		

		Avatar * pAvatar = dynamic_cast<Avatar*>(m_grpAvatars->getChild(nI));
		const Matrixd & mtrxOldMatrixAvatar = pAvatar->getMatrix();

		//VR::AnimationPath * pAP = dynamic_cast<VR::AnimationPath*>(m_pAP->createAnimationPath(mtrxOldMatrixAvatar, mtrxNewMatrixAvatar));
		//pAvatar->addAnimationPath(pAP);

		//pAvatar->setMatrix(mtrxNewMatrixAvatar);

		//Both matrices set and attached to the animation
		pAvatar->setAnimation(mtrxOldMatrixAvatar, mtrxNewMatrixAvatar);
	}
}

//------------------------------------------------------------------------------

void AvatarManagerClient::addAvatar(Avatar * apAvatar)	{
	if (apAvatar == 0)	{
		return;
	}

	m_grpAvatars->addChild(apAvatar);
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
}

//------------------------------------------------------------------------------

int AvatarManagerClient::getNumberOfAvatars() const	{
	return m_grpAvatars->getNumChildren();
}

//------------------------------------------------------------------------------

ref_ptr<Group> AvatarManagerClient::getAvatars()	{
	return m_grpAvatars;
}