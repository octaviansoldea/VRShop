#ifndef VR_SCENE_MANAGER_CLIENT_H
#define VR_SCENE_MANAGER_CLIENT_H

#include <osg/Group>

#include <string>

namespace VR	{
	class Scene;

	class AbstractObject;

	class SceneManagerClient	{
	public:
		SceneManagerClient();
		SceneManagerClient(const std::string & astrDBFileName);
		~SceneManagerClient();

		virtual const char* className() const;

		Scene * getSceneClient();
		
		void requestSceneData(std::string & astrDBFileName);
		
	private:
		std::string m_strDBFileName;
		Scene * m_pSceneClient;
	};
}
#endif //VR_SCENE_MANAGER_CLIENT_H