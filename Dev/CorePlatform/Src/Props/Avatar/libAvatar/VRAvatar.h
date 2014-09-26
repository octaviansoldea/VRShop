#ifndef VR_AVATAR_H
#define VR_AVATAR_H

#include <QObject>
#include <QTimer>
#include <string>

#include <osg/MatrixTransform>
#include "VRAnimationPath.h"

struct AnimationManagerFinder;

namespace VR {
	class AnimationPath;
	class KeyboardMouseManipulatorShopClient;

	struct AvatarParams	{
		AvatarParams();

		std::string m_strAvatarFile;
		std::string m_strAvatarName;
		KeyboardMouseManipulatorShopClient * m_pKeyboardMouseManipulatorShopClient;
		QObject * m_pParent;
	};

	class Avatar : public QObject, public osg::MatrixTransform {
		Q_OBJECT

	public:
		Avatar(std::string & astrAvatarFile, QObject * parent=0);
		Avatar(const AvatarParams * apAvatarParams);
		
		~Avatar();

		virtual const char* className() const;

		void setAnimation(const osg::Matrixd & amtrxOldMatrix, const osg::Matrixd & amtrxNewMatrix);

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

		void addAnimationPath(VR::AnimationPath * apAnimationPath);
		VR::AnimationPath * getAnimationPath();

	public slots:
		void slotUpdatePosition(bool abAnimation);

	private:
		std::list<osg::ref_ptr<VR::AnimationPath>> m_plstAnimationPaths;
		KeyboardMouseManipulatorShopClient * m_pKeyboardMouseManipulatorShopClient;

		osg::ref_ptr<VR::AnimationPath> m_pAnimationPath;
		osg::ref_ptr<osg::AnimationPathCallback> m_pAPCallback;

		osg::ref_ptr<osg::Group> m_p_LocalCoords_Avatar;

		AnimationManagerFinder * m_pFinder;
	};
}
#endif //VR_AVATAR_H