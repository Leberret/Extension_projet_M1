#pragma once

// Includes
#include "glut.h"
#include <iostream>
#include <QApplication>
#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "si.h"      
#include "siapp.h"
// Namespaces.
using namespace std;
using namespace cv;

//Variables globales externes
//extern INT			Coupe, Min, Max;
extern INT			pTx, pTy, pTz, pRx, pRy, pRz;
extern INT			colonne;
extern INT			ligne;
extern qint16*		NbFichiers;
extern qint16*		NbCouleurs;
//extern 	qint16*		coupe;
extern QVector<unsigned short>* allpixels;
extern FLOAT		EcartCoupe;
extern FLOAT        EcartPixel;



//Class My3DScene
class My3DScene : public QGLWidget
{
private:
	// Attributes.
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	GLfloat zoomZ;
	GLfloat TranslationX;
	GLfloat TranslationY;
	QPoint lastPosition;

	// Private methods.
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

	//void mouse3DMoveEvent(SiSpwEvent* pEvent);
	QVector<Vec3b>* VectorImages(QVector<unsigned short>* all);

	//Variables globales
	qint16* precValueTX;
	qint16* compteurTX;
	qint16* precValueTY;
	qint16* compteurTY;
	qint16* precValueTZ;
	qint16* compteurTZ;
	qint16* precValueRX;
	qint16* compteurRX;
	qint16* precValueRY;
	qint16* compteurRY;
	qint16* precValueRZ;
	qint16* compteurRZ;
	QVector<Vec3b>* ImgVec;

	
public slots:
	void Recentrer();
	void BloquerScene();
	void mouse3DMove();
public:
	My3DScene();
	void init();

};