#include "VRClient.h"

#include "VRAbstractManagerClient.h"

using namespace VR;

//==============================================================

AbstractManagerClient::AbstractManagerClient(QObject * apParent) : QObject(apParent)	{
	m_pClient = new Client();
}

//--------------------------------------------------------------

AbstractManagerClient::~AbstractManagerClient()	{
	delete m_pClient;
}
