#ifndef VR_AVATAR_H
#define VR_AVATAR_H

#include <QObject>
#include <QTimer>
#include <string>

#include <osg/MatrixTransform>
#include <osg/AnimationPath>

class AnimationManagerFinder;

namespace VR {
	class AnimationPath;
	class KeyboardMouseManipulatorShopClient;

	class Avatar : public QObject, public osg::MatrixTransform {
		Q_OBJECT

	public:
		Avatar(std::string & astrAvatarFile, QObject * parent=0);
		Avatar(std::string & astrAvatarFile,
			KeyboardMouseManipulatorShopClient *apKeyboardMouseManipulatorShopClient, 
			QObject * parent=0);
		
		~Avatar();

		virtual const char* className() const;

		void pickProduct();		//Either from a shelf or a basket
		//void returnProduct();	//Either to a shelf or a basket
		//void communicate();

		////First turn to the destination
		//void moveTo(const osg::Vec3d & avec3dPosition, float aflSpeed, AnimationPath & aAP);
		//void bodyTurn(const osg::Vec3d & avec3dDirection, float aflSpeed);

		//void animatePick();
		void startAnimation();
		void stopAnimation();//clears all the actions

		void setPosition(const osg::Vec3d & aVec3d);
		void setOrientation(const osg::Vec3d & aVec3d);

		void addAnimationPath(osg::AnimationPath & aAnimationPath);
		osg::AnimationPath * getAnimationPath();

	public slots:
		void slotUpdatePosition();

	private:
		std::list<osg::ref_ptr<osg::AnimationPath>> m_plstAnimationPaths;
		KeyboardMouseManipulatorShopClient * m_pKeyboardMouseManipulatorShopClient;

		osg::ref_ptr<osg::AnimationPath> m_pAnimationPath;
		osg::ref_ptr<osg::Group> m_pAvatar;

		AnimationManagerFinder * m_pFinder;
	};
}
#endif //VR_AVATAR_H