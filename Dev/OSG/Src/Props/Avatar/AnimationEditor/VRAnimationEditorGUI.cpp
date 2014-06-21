#include <fstream>

#include <osgDB/ReadFile>
#include <osgDB/writeFile>
#include <osg/Matrix>

#include "VRFileManager.h"
#include "VRAxes.h"

#include <osg/AnimationPath>

#include "AnimtkViewer.h"
#include "AnimtkViewerGUI.h"
#include "AnimtkViewerKeyHandler.h"

#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "VRKeyboardMouseManipulator.h"

#include "VRAnimationEditorGUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

AnimationEditorGUI::AnimationEditorGUI()	{
	m_pScene = new Group();
	m_pMt = new MatrixTransform();

	setupUi(this);

	connect(m_pPushButtonSearchFile, SIGNAL(clicked(bool)), this, SLOT(slotBrowseDirectory()));
	connect(m_pLineEditInputFile,SIGNAL(returnPressed()),this,SLOT(slotLoadNewAnimation()));
	connect(m_pPushButtonRun, SIGNAL(clicked(bool)), this, SLOT(slotRunAnimationPressed()));
	connect(m_pPushButtonLoadFile, SIGNAL(clicked(bool)), this, SLOT(slotLoadNewAnimation()));
    connect(m_pPushButtonSave, SIGNAL(clicked(bool)), this, SLOT(slotSaveAnimationPressed()));

	connect(m_pDoubleSpinBoxScaleX, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));
	connect(m_pDoubleSpinBoxScaleY, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));
	connect(m_pDoubleSpinBoxScaleZ, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));
	connect(m_pDoubleSpinBoxPosZ, SIGNAL(editingFinished()), this, SLOT(slotMatrixTransformChanged()));

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulator()); 
	m_pOSGQTWidget->show();

	show();
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotBrowseDirectory()	{
	QString qstrFileName = QFileDialog::getOpenFileName(this);

	m_pLineEditInputFile->setText(qstrFileName);
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotSaveAnimationPressed()	{
	QString qstrFileName;
	if(m_pLineEditOutputFile->text().isEmpty())	{
		qstrFileName = QFileDialog::getSaveFileName(this);
		m_pLineEditOutputFile->setText(qstrFileName);
	} else {
		qstrFileName = m_pLineEditOutputFile->text();
	}

	if (qstrFileName.isEmpty())	{
		return;
	}

	int nKeyframeFrom = m_pSpinBoxFrameFrom->value();
	int nKeyframeTo = m_pSpinBoxFrameTo->value();
	cutAnimation(nKeyframeFrom,nKeyframeTo);
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotLoadNewAnimation()	{
	std::string strFileName = m_pLineEditInputFile->text().toStdString();
	if(strFileName != "" && QFile::exists(strFileName.c_str()))	{
		m_pScene->removeChildren(0,m_pScene->getNumChildren());
		
		ref_ptr<Axes > pAxes = new Axes;
		m_pScene->addChild(pAxes);

		m_pNode = dynamic_cast<osg::Group*>(osgDB::readNodeFile(strFileName));

		m_pMt->addChild(m_pNode);
		m_pScene->addChild(m_pMt);
	}
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotRunAnimationPressed()	{
	// Set our Singleton's model.
    AnimationManagerFinder finder;
//    m_pNode->accept(finder);

	osg::Transform * pTransform = dynamic_cast<Transform*>(m_pMt.get());
	osg::ref_ptr<Group> pGroup = dynamic_cast<Group*>(pTransform->getChild(0));

	pGroup->accept(finder);


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
		model->playAnimation(anim);
	} else {
		std::cerr << "no osgAnimation::AnimationManagerBase found in the subgraph, no animations available" << std::endl;
	}
}

//----------------------------------------------------------------------

void AnimationEditorGUI::slotMatrixTransformChanged()	{
	float flScale[3] = {m_pDoubleSpinBoxScaleX->value(),m_pDoubleSpinBoxScaleY->value(),m_pDoubleSpinBoxScaleZ->value()};
	float flPosZ = m_pDoubleSpinBoxPosZ->value();

	osg::Matrix mtrxMt = m_pMt->getMatrix();
	osg::Matrix & mtrxTransform =
		mtrxMt.scale(flScale[0],flScale[1],flScale[2])	*
		mtrxMt.translate(0,0,flPosZ);
	m_pMt->setMatrix(mtrxTransform);

	//m_pScene->removeChildren(0,m_pScene->getNumChildren());
	//m_pScene->addChild(pMt);
}

//----------------------------------------------------------------------

void AnimationEditorGUI::cutAnimation(int & anFrom, int & anTo)	{
	std::string & strOutFileName = m_pLineEditOutputFile->text().toStdString();
	
	osgAnimation::AnimationManagerBase* b = dynamic_cast<osgAnimation::AnimationManagerBase*>(m_pNode->getUpdateCallback());
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
				osgDB::writeNodeFile(*m_pMt,strOutFileName);
		}
	}	
}