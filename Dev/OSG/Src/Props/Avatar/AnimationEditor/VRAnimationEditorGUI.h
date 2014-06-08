#ifndef VR_ANIMATION_EDITOR_GUI_H
#define VR_ANIMATION_EDITOR_GUI_H

#include <QDialog>

#include <osg/Group>
#include <osg/MatrixTransform>

#include "ui_VRAnimationEditorGUI.h"

namespace VR	{
	class AnimationEditorGUI : public QFrame, public Ui::ShopAvatarEditor {
		Q_OBJECT
	public:
		AnimationEditorGUI();

	public slots:
		void slotBrowseDirectory();
		void slotLoadNewAnimation();
		void slotRunAnimationPressed();
		void slotSaveAnimationPressed();
		void slotMatrixTransformChanged();

	private:
		osg::ref_ptr<osg::Group> m_pScene;
		osg::ref_ptr<osg::Group> m_pNode;
		osg::ref_ptr<osg::MatrixTransform> m_pMt;

		void cutAnimation(int & anFrom, int & anTo);
	};
}
#endif //VR_ANIMATION_EDITOR_GUI_H