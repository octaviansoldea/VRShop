#include <fstream>
#include <string>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include <osgDB/ReadFile>
#include <osgDB/writeFile>
#include <osg/Matrix>
#include <osg/AnimationPath>

#include "VRAppData.h"
#include "VRFileManager.h"
#include "VRAxes.h"

#include "AnimtkViewer.h"
#include "AnimtkViewerGUI.h"
#include "AnimtkViewerKeyHandler.h"

#include "VRKeyboardMouseManipulator.h"
#include "VRAnimationEditorGUI.h"

using namespace std;
using namespace osg;
using namespace VR;

using namespace Ui;

//----------------------------------------------------------------------

AnimationEditorGUI::AnimationEditorGUI()	{
	m_pScene = new Group();
	m_pMt = new MatrixTransform();

	setupUi(this);

	connect(m_pPushButtonLoadAvatar,SIGNAL(clicked(bool)),this,SLOT(slotLoadAvatar()));
	connect(m_pPushButtonSaveAvatar,SIGNAL(clicked(bool)),this,SLOT(slotSaveAvatar()));
    connect(m_pToolButtonPlay, SIGNAL(toggled(bool)), this, SLOT(slotPlay(bool)));

	connect(m_pDoubleSpinBoxScaleX, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));
	connect(m_pDoubleSpinBoxScaleY, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));
	connect(m_pDoubleSpinBoxScaleZ, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));
	connect(m_pDoubleSpinBoxPosZ, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulator()); 
	m_pOSGQTWidget->show();

	ref_ptr<Axes > pAxes = new Axes;
	m_pScene->addChild(pAxes);

	show();
}

//----------------------------------------------------------------------

QString AnimationEditorGUI::openOrSaveDialog(const char * apchSuffix, bool bOpen) {
	QString qstrFileName;

	//QString qstrCurrentPath = QDir::currentPath();
	std::string strDir = AppData::getFPathResources() +  "/Models3D/";

	if(bOpen == true) 
		qstrFileName = QFileDialog::getOpenFileName(this, 
			tr("Open File"),
			tr(strDir.c_str()),
			apchSuffix);
	else
		qstrFileName = QFileDialog::getSaveFileName(this, 
			tr("Save File"),
			tr(strDir.c_str()),
			apchSuffix);
	return(qstrFileName);
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotLoadAvatar() {
	QString qstrFileName = openOrSaveDialog("Avatar (*.osg)", true);
	if(qstrFileName != "") {
		m_strNodeFileName = qstrFileName.toStdString();
		if(m_strNodeFileName != "" && QFile::exists(m_strNodeFileName.c_str()))	{
			m_pScene->removeChildren(0,m_pScene->getNumChildren());
		
			m_pGroup = dynamic_cast<osg::Group*>(osgDB::readNodeFile(m_strNodeFileName));

			osg::MatrixTransform * pMT = dynamic_cast<osg::MatrixTransform*>(m_pGroup.get());
			if(pMT) {
				m_pMt = pMT;
				m_pGroup = dynamic_cast<osg::Group*>(m_pMt->getChild(0));
			} else {
				m_pMt->addChild(m_pGroup);
			}
			m_pScene->removeChildren(1,m_pScene->getNumChildren() - 1);
			m_pScene->addChild(m_pMt);
		}
	}
	setWindowTitle(qstrFileName.toStdString().c_str());

	/*osgAnimation::AnimationManagerBase* b =
		dynamic_cast<osgAnimation::AnimationManagerBase*>(m_pNode->getUpdateCallback());
	if (b) {
		osgAnimation::BasicAnimationManager * pBam = new osgAnimation::BasicAnimationManager(*b);
		const osgAnimation::AnimationList & pAL = b->getAnimationList();
		for(osgAnimation::AnimationList::const_iterator citAL = pAL.begin();
			citAL != pAL.end();
			citAL++) {
				osgAnimation::ChannelList & channelList = (*citAL)->getChannels();
				for(osgAnimation::ChannelList::iterator itCL = channelList.begin();
					itCL != channelList.end();
					itCL++) {
						osgAnimation::Sampler * pSampler = (*itCL)->getSampler();
						
						osgAnimation::KeyframeContainer * pKFC = pSampler->getKeyframeContainer();
						{
							osgAnimation::TemplateKeyframeContainer<osg::Vec3f> *pTKFC_Vec3f =
								dynamic_cast<osgAnimation::TemplateKeyframeContainer<osg::Vec3f> *>(pKFC);

							osgAnimation::TemplateKeyframeContainer<osg::Vec3f> m_TKFC_Vec3f = *pTKFC_Vec3f;
						}
				}
		}
	}*/

}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotSaveAvatar() {
	QString qstrFileName = openOrSaveDialog("*.osg", false);

	int nKeyframeFrom = m_pSpinBoxFrameFrom->value();
	int nKeyframeTo = m_pSpinBoxFrameTo->value();
	cutAnimation(nKeyframeFrom,nKeyframeTo);

	if(qstrFileName != "") {
		string strOutFileName = qstrFileName.toStdString().c_str();
		osgDB::writeNodeFile(*m_pMt,strOutFileName);
		
	}
}

//----------------------------------------------------------------------

//void AnimationEditorGUI::slotLoadNewAnimation() {
//	std::string strFileName = m_pLineEditInputFile->text().toStdString();
//	if(strFileName != "" && QFile::exists(strFileName.c_str()))	{
//		m_pScene->removeChildren(0,m_pScene->getNumChildren());
//
//		m_pNode = dynamic_cast<osg::Group*>(osgDB::readNodeFile(strFileName));
//
//		m_pMt->addChild(m_pNode);
//		m_pScene->addChild(m_pMt);
//	}
//}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotPlay(bool abPressed) {
	// Set our Singleton's model.
    AnimationManagerFinder finder;
//    m_pNode->accept(finder);

	m_pScene->removeChild(0, m_pScene->getNumChildren());

	m_pGroup = dynamic_cast<osg::Group*>(osgDB::readNodeFile(m_strNodeFileName));
		
	osg::MatrixTransform * pMT = dynamic_cast<osg::MatrixTransform*>(m_pGroup.get());
	if(pMT) {
			
		m_pMt->removeChildren(0, m_pMt->getNumChildren());
		m_pMt = pMT;
		m_pGroup = dynamic_cast<osg::Group*>(m_pMt->getChild(0));
	}
	m_pScene->addChild(m_pMt);


	m_pMt->removeChildren(0, m_pMt->getNumChildren());
	m_pMt->addChild(m_pGroup);

	osg::Transform * pTransform = dynamic_cast<Transform*>(m_pMt.get());
	osg::ref_ptr<Group> pGroup = dynamic_cast<Group*>(pTransform->getChild(0));

	pGroup->accept(finder);

	int nKeyframeFrom = m_pSpinBoxFrameFrom->value();
	int nKeyframeTo = m_pSpinBoxFrameTo->value();
	cutAnimation(nKeyframeFrom,nKeyframeTo);


	if (finder._am.valid()) {
//		m_pNode->setUpdateCallback(finder._am.get());
		pGroup->setUpdateCallback(finder._am.get());
		AnimtkViewerModelController::setModel(finder._am.get());

		osgAnimation::BasicAnimationManager* model = finder._am.get();
		const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
		const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
		osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);
		anim->computeDuration();
		anim->setStartTime(0);
		if(abPressed == true) {
			model->playAnimation(anim);
		} else {
			model->stopAnimation(anim);
		}
	} else {
		std::cerr << "no osgAnimation::AnimationManagerBase found in the subgraph, no animations available" << std::endl;
	}
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotMatrixTransformChanged()	{
	float flScale[3] = {m_pDoubleSpinBoxScaleX->value(),m_pDoubleSpinBoxScaleY->value(),m_pDoubleSpinBoxScaleZ->value()};
	float flPosZ = m_pDoubleSpinBoxPosZ->value();

	osg::Matrix mtrxMt = m_pMt->getMatrix();
	osg::Matrix mtrxTransform =
		mtrxMt.scale(flScale[0],flScale[1],flScale[2])	*
		mtrxMt.translate(0,0,flPosZ);
	m_pMt->setMatrix(mtrxTransform);

	//m_pScene->removeChildren(0,m_pScene->getNumChildren());
	//m_pScene->addChild(pMt);
}

//----------------------------------------------------------------------

void AnimationEditorGUI::cutAnimation(int & anFrom, int & anTo)	{
	osgAnimation::AnimationManagerBase* b = dynamic_cast<osgAnimation::AnimationManagerBase*>(m_pGroup->getUpdateCallback());
	if (b) {
		osgAnimation::BasicAnimationManager * pBam = new osgAnimation::BasicAnimationManager(*b);
		const osgAnimation::AnimationList & pAL = b->getAnimationList();
		for(osgAnimation::AnimationList::const_iterator citAL = pAL.begin();
			citAL != pAL.end();
			citAL++) {
				osgAnimation::ChannelList & channelList = (*citAL)->getChannels();
				for(osgAnimation::ChannelList::iterator itCL = channelList.begin();
					itCL != channelList.end();
					itCL++) {
						osgAnimation::Sampler * pSampler = (*itCL)->getSampler();
						
						osgAnimation::KeyframeContainer * pKFC = pSampler->getKeyframeContainer();
						{
							osgAnimation::TemplateKeyframeContainer<osg::Vec3f> *pTKFC_Vec3f =
								dynamic_cast<osgAnimation::TemplateKeyframeContainer<osg::Vec3f> *>(pKFC);

							if(pTKFC_Vec3f != 0) {
								int nTo = pTKFC_Vec3f->end() - pTKFC_Vec3f->begin();	
								nTo = (anTo > nTo) ? nTo : anTo;

								pTKFC_Vec3f->erase(pTKFC_Vec3f->begin() + nTo - 1, pTKFC_Vec3f->end());
								pTKFC_Vec3f->erase(pTKFC_Vec3f->begin(), pTKFC_Vec3f->begin() + anFrom);
							}
						}

						{
							osgAnimation::TemplateKeyframeContainer<osg::Quat> *pTKFC_Quat =
								dynamic_cast<osgAnimation::TemplateKeyframeContainer<osg::Quat> *>(pKFC);

							if(pTKFC_Quat != 0) {
								int nTo = pTKFC_Quat->end() - pTKFC_Quat->begin();	
								nTo = (anTo > nTo) ? nTo : anTo;

								pTKFC_Quat->erase(pTKFC_Quat->begin() + nTo - 1, pTKFC_Quat->end());
								pTKFC_Quat->erase(pTKFC_Quat->begin(), pTKFC_Quat->begin() + anFrom);
							}
						}
				}
		}
	}	
}