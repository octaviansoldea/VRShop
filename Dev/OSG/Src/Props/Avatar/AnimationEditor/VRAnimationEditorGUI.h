#ifndef VR_ANIMATION_EDITOR_GUI_H
#define VR_ANIMATION_EDITOR_GUI_H

#include <QDialog>

#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/AnimationPath>

#include "ui_VRAnimationEditorGUI.h"

namespace VR	{
	class AnimationEditorGUI : public QFrame, public Ui::ShopAvatarEditor {
		Q_OBJECT
	public:
		AnimationEditorGUI();

	public slots:
		void slotLoadAvatar();
		void slotSaveAvatar();
		void slotPlay(bool abPressed);
		void slotMatrixTransformChanged();

	private:
		QString openOrSaveDialog(const char * apchSuffix, bool bOpen);

		osg::ref_ptr<osg::Group> m_pScene;
		osg::ref_ptr<osg::Group> m_pGroup;
		std::string m_strNodeFileName;
		osg::ref_ptr<osg::MatrixTransform> m_pMt;

		void cutAnimation(int & anFrom, int & anTo);

		//osgAnimation::TemplateKeyframeContainer<osg::Vec3f> m_TKFC_Vec3f;
	};
}
#endif //VR_ANIMATION_EDITOR_GUI_H