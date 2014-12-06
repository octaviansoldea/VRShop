#include "VRClient.h"

#include "VRAbstractManagerClient.h"

using namespace VR;

//==============================================================

AbstractManagerClient::AbstractManagerClient(Client * apClient, QObject * apParent) : 
m_pClient(apClient), QObject(apParent)	{
}

//--------------------------------------------------------------

AbstractManagerClient::~AbstractManagerClient()	{
}

//==============================================================================
