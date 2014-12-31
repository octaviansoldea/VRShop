/*
	Taken from Rui Wang and Xuelei Qian, OpenSceneGraph 3.0: Beginner's Guide
*/

#include "VRReadAndSaveFileCallback.h"

using namespace std;
using namespace VR;
using namespace osg;

Image * ReadAndSaveFileCallback::getImageByName(const string& filename)	{
	map<string, ref_ptr<Image> >::iterator it = m_ImageMap.find(filename);
	if(it != m_ImageMap.end())
		return it->second.get();

	return NULL;
}

//---------------------------------------------------------------------------------------

osgDB::ReaderWriter::ReadResult ReadAndSaveFileCallback::readImage(
const string& filename, const osgDB::Options* options)	{
	Image* image = getImageByName(filename);
	if(!image)	{
		osgDB::ReaderWriter::ReadResult rr;
		rr = osgDB::Registry::instance()->readImageImplementation(filename, options);
		if (rr.success())
			m_ImageMap[filename] = rr.getImage();
		return rr;
	}
	return image;
}