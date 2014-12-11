#ifndef VR_READ_AND_SAVE_FILE_CALLBACK_H
#define VR_READ_AND_SAVE_FILE_CALLBACK_H

#include <string>

#include <osgDB/ReadFile>

namespace VR {
	class ReadAndSaveFileCallback : public osgDB::ReadFileCallback	{
	public:
		virtual osgDB::ReaderWriter::ReadResult readImage(
			const std::string& astrFileName, const osgDB::Options* aOptions
		);

	protected:
		osg::Image* getImageByName(const std::string& astrFileName);
		std::map<std::string, osg::ref_ptr<osg::Image> > m_ImageMap;
	};


	class ReadAndSaveNodeCallback : public osgDB::ReadFileCallback	{
	public:
		virtual osgDB::ReaderWriter::ReadResult readNode(const std::string& filename, const osgDB::Options* options);

	protected:
		osg::Node* getNodeByName(const std::string& astrFileName);
		std::map<std::string, osg::ref_ptr<osg::Node> > m_NodeMap;
	};

}
#endif //VR_READ_AND_SAVE_FILE_CALLBACK_H