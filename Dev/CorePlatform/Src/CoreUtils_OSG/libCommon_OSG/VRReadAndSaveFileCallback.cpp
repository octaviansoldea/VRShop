/*
	Taken from Rui Wang and Xuelei Qian, OpenSceneGraph 3.0: Beginner's Guide
*/

#include "VRReadAndSaveFileCallback.h"

using namespace std;
using namespace VR;
using namespace osg;

Image * ReadAndSaveFileCallback::getImageByName(const string& astrFileName)	{
	map<string, ref_ptr<Image> >::iterator it = m_ImageMap.find(astrFileName);
	if(it != m_ImageMap.end())
		return it->second.get();

	return NULL;
}

//---------------------------------------------------------------------------------------

osgDB::ReaderWriter::ReadResult ReadAndSaveFileCallback::readImage(
const string& astrFileName, const osgDB::Options* aOptions)	{
	Image* image = getImageByName(astrFileName);
	if(!image)	{
		osgDB::ReaderWriter::ReadResult rr;
		rr = osgDB::Registry::instance()->readImageImplementation(astrFileName, aOptions);
		if (rr.success())
			m_ImageMap[astrFileName] = rr.getImage();
		return rr;
	}
	return image;
}


//==========================================================================================================

Node * ReadAndSaveNodeCallback::getNodeByName(const string& astrFileName)	{
	map<string, ref_ptr<Node> >::iterator it = m_NodeMap.find(astrFileName);
	if(it != m_NodeMap.end())
		return it->second.get();

	return NULL;
}

//---------------------------------------------------------------------------------------

osgDB::ReaderWriter::ReadResult ReadAndSaveNodeCallback::readNode(
const string& astrFileName, const osgDB::Options* aOptions)	{
	Node* node = getNodeByName(astrFileName);
	if(!node)	{
		osgDB::ReaderWriter::ReadResult rr;
		rr = osgDB::Registry::instance()->readNodeImplementation(astrFileName, aOptions);
		if (rr.success())
			m_NodeMap[astrFileName] = rr.getNode();
		return rr;
	}
	return node;
}
