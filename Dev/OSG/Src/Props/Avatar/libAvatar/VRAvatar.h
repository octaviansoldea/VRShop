#ifndef VR_AVATAR_H
#define VR_AVATAR_H

#include <QObject>
#include <QTimer>

#include <osg/MatrixTransform>

namespace VR {
	class AnimationPath;

	class Avatar : public osg::MatrixTransform, QObject	{
	public:
		Avatar();

		void rotateHeadTo(const osg::Vec3d & avec3dOrientation, float aflSpeed);
		void lookAround();	//Just moves the head in a predefined manner

		void pickProduct();		//Either from a shelf or a basket
		void returnProduct();	//Either to a shelf or a basket
		void communicate();

		//First turn to the destination
		void moveTo(const osg::Vec3d & avec3dPosition, float aflSpeed, AnimationPath & aAP);
		void bodyTurn(const osg::Vec3d & avec3dDirection, float aflSpeed);

		void stretchHand(/*Left,right,both*/);
		void bendHand(/*Left,right,both*/);

		void animatePick();
		void stopAnimation();

	protected:
		
		Q_OBJECT

	public slots:

		void step();

	
		typedef enum STATUS {
			SITTING,
			STANDING,
			WALKING,
			RUNNING,
			OTHER
		};

		STATUS m_Status;
		osg::Vec3d m_vec3dLocation;
		osg::Vec3d m_vec3dOrientationBody;
		osg::Vec3d m_vec3dOrientationHead;

		osg::Vec3d m_From;
		osg::Vec3d m_Towards;
		osg::Vec3d m_CurrentLocation;
		
		int m_nTwoStepsFragmentsNr;
		double m_dbStepFragmentLength;
		
		QTimer m_Timer;


		double m_dbHeight;
		bool m_bIsFemale;
		bool m_bIsChild;
	};
}
#endif //VR_AVATAR_H