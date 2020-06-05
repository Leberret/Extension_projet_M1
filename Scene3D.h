#pragma once

// Includes
#include "glut.h"
#include <iostream>
#include <QApplication>
#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>
// Namespaces.
using namespace std;

//Variables globales externes
//extern INT			Coupe, Min, Max;
extern INT			pTx, pTy, pTz, pRx, pRy, pRz;
extern INT			colonne;
extern INT			ligne;
extern qint16*		NbFichiers;
extern QVector<vector<unsigned short>>* allpixels;



//Class My3DScene
class My3DScene : public QGLWidget
{
private:
	// Attributes.
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QPoint lastPosition;

	// Private methods.
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

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
	
public slots:
	void mouse3DMove();
	void Recentrer();
	void BloquerScene();

public:
	My3DScene();
	void init();
};