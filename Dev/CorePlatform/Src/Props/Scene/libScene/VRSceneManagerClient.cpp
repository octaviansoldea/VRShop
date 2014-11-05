#include <string>
#include <fstream>
#include <iostream>

#include <vector>

#include "BasicStringDefinitions.h"

#include "VRAbstractObject.h"

#include "VRSceneManagerClient.h"

using namespace VR;
using namespace osg;
using namespace std;


SceneManagerClient::SceneManagerClient()	{
}

SceneManagerClient::SceneManagerClient(const std::string & astrDBFileName)	{
}


SceneManagerClient::~SceneManagerClient()	{
}

const char* SceneManagerClient::className() const	{
	return "SceneManagerClient";
}

Scene * SceneManagerClient::getSceneClient()	{
	return m_pSceneClient;
}
		
void SceneManagerClient::requestSceneData(string & astrDBFileName)	{
}
