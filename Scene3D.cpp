/**
 * @Authors: LE FUR Anthony / LE BERRE Thomas
 * @Company: ISEN Yncr�a Ouest
 * @Email: anthony.le-fur@isen-ouest.yncrea.fr / thomas.le-berre@isen-ouest.yncrea.fr
 * @Last Modified: 30-Apr-2020
 */

#include "Scene3D.h"
#include "DICOM_3Dmouse.h"
#include "Widget3D.h"

//Appel des variables globales externes
extern int Coupe, Min, Max;

/*--------------------------------------------------------------------------
* Fonction : init()
*
* Description : Initialisation des variables globales qui permettent la 
* m�morisation des donn�es r��ues par la souris
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::init() {
    //Navigation selon TX
    precValueTX = new qint16;
    compteurTX = new qint16;
    *precValueTX = 0;
    *compteurTX = 0;

    //Navigation selon TY
    precValueTY = new qint16;
    compteurTY = new qint16;
    *precValueTY = 0;
    *compteurTY = 0;

    //Navigation selon TZ
    precValueTZ = new qint16;
    compteurTZ = new qint16;
    *precValueTZ = 0;
    *compteurTZ = 0;

    //Rotation selon RX
    precValueRX = new qint16;
    compteurRX = new qint16;
    *precValueRX = 0;
    *compteurRX = 0;

    //Rotation selon RY
    precValueRY = new qint16;
    compteurRY = new qint16;
    *precValueRY = 0;
    *compteurRY = 0;

    //Rotation selon RZ
    precValueRZ = new qint16;
    compteurRZ = new qint16;
    *precValueRZ = 0;
    *compteurRZ = 0;
}

/*--------------------------------------------------------------------------
* Fonction : createObjects()
*
* Description : Cr�ation des objets 3D constituant la sc�ne 3D, plans 3D
* recouverts d'une texture sur chaque face
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::createObjects()
{
    //R�cup�ration de la coupe pour ajouter dans chemin d'acc�s
    string coupe = to_string(Coupe);
    int Milieu = (int)((Max - Min )/ 2);
    int nbImage = Max - Milieu;
    //Definition texture
    Qt3DRender::QTextureLoader* loader;

    if ((int)(Max - Min) < 200) {

        //De l'image de d�part � l'image d'arriv�e
        for (int i=0; i < Milieu; i++)
        {
            //R�p�tition de la m�me image trois fois
            for (int k = 0; k < 3; k += 1)
            {
                //--------------------------FACE RECTO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeMesh = new Qt3DExtras::QPlaneMesh(this->planeEntity);
                this->planeMesh->setWidth(6);
                this->planeMesh->setHeight(5);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, 0.02 * i + 0.005 * k, 0));

                // Ajout texture � la face recto du plan, � partir d'une image locale suivant la valeur du NumImageTx i
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                string cheminimage;
                string format = ".PNG";
                string numero = to_string(nbImage +i);
                cheminimage = "Images/Coupe" + coupe + "_" + numero + format;
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);
                loader->setMirrored(false);//Garder le sens correct de l'image
                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);

                //--------------------------FACE VERSO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);
                this->planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 180.0f)); //Copie de la texture � 180�

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, 0.02 * i + 0.005 * k, 0));

                // Ajout de la m�me texture � la face verso du plan
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);

                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);
            }
        }
        for (int i = 0; i < Milieu; i++)
        {
            //R�p�tition de la m�me image trois fois
            for (int k = 0; k < 3; k += 1)
            {
                //--------------------------FACE RECTO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeMesh = new Qt3DExtras::QPlaneMesh(this->planeEntity);
                this->planeMesh->setWidth(6);
                this->planeMesh->setHeight(5);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, -(0.02 * i + 0.005 * k), 0));

                // Ajout texture � la face recto du plan, � partir d'une image locale suivant la valeur du NumImageTx i
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                string cheminimage;
                string format = ".PNG";
                string numero = to_string(nbImage -i);
                cheminimage = "Images/Coupe" + coupe + "_" + numero + format;
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);
                loader->setMirrored(false);//Garder le sens correct de l'image
                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);

                //--------------------------FACE VERSO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);
                this->planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 180.0f)); //Copie de la texture � 180�

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, -(0.02 * i + 0.005 * k), 0));

                // Ajout de la m�me texture � la face verso du plan
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);

                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);
            }
        }
    }
    else if((int)(Max - Min) >= 200 &&(int)( Max - Min) <= 300)
    {
        for (int i = 0; i < Milieu; i++)
        {
            //R�p�tition de la m�me image trois fois
            for (int k = 0; k < 2; k += 1)
            {
                //--------------------------FACE RECTO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeMesh = new Qt3DExtras::QPlaneMesh(this->planeEntity);
                this->planeMesh->setWidth(6);
                this->planeMesh->setHeight(5);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, 0.02 * i + 0.01 * k, 0));

                // Ajout texture � la face recto du plan, � partir d'une image locale suivant la valeur du NumImageTx i
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                string cheminimage;
                string format = ".PNG";
                string numero = to_string(nbImage +i);
                cheminimage = "Images/Coupe" + coupe + "_" + numero + format;
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);
                loader->setMirrored(false);//Garder le sens correct de l'image
                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);

                //--------------------------FACE VERSO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);
                this->planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 180.0f)); //Copie de la texture � 180�

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, 0.02 * i + 0.01 * k, 0));

                // Ajout de la m�me texture � la face verso du plan
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);

                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);
            }
        }
        for (int i = 0; i < Milieu; i++)
        {
            //R�p�tition de la m�me image trois fois
            for (int k = 0; k < 2; k += 1)
            {
                //--------------------------FACE RECTO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeMesh = new Qt3DExtras::QPlaneMesh(this->planeEntity);
                this->planeMesh->setWidth(6);
                this->planeMesh->setHeight(5);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, -(0.02 * i + 0.01 * k), 0));

                // Ajout texture � la face recto du plan, � partir d'une image locale suivant la valeur du NumImageTx i
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                string cheminimage;
                string format = ".PNG";
                string numero = to_string(nbImage -i);
                cheminimage = "Images/Coupe" + coupe + "_" + numero + format;
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);
                loader->setMirrored(false);//Garder le sens correct de l'image
                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);

                //--------------------------FACE VERSO---------------------------------------
                //Initialisation Entit�, plan et transform
                this->planeEntity = new Qt3DCore::QEntity(&this->scene);
                this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);
                this->planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 180.0f)); //Copie de la texture � 180�

                //Translation pour d�caler les images lors du changement de plan
                this->planeTransform->setTranslation(QVector3D(0, -(0.02 * i + 0.01 * k), 0));

                // Ajout de la m�me texture � la face verso du plan
                loader = new Qt3DRender::QTextureLoader(this->planeMesh);
                this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
                loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
                this->planeTexture->setTexture(loader);

                this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

                //Ajouts des diff�rents composants � l'entit�
                this->planeEntity->addComponent(this->planeMesh);
                this->planeEntity->addComponent(this->planeTexture);
                this->planeEntity->addComponent(this->planeTransform);
            }
        }
    }
    else
    {
        //De l'image de d�part � l'image d'arriv�e
        for (int i = 0; i < Milieu; i++)
        {
            //--------------------------FACE RECTO---------------------------------------
            //Initialisation Entit�, plan et transform
            this->planeEntity = new Qt3DCore::QEntity(&this->scene);
            this->planeMesh = new Qt3DExtras::QPlaneMesh(this->planeEntity);
            this->planeMesh->setWidth(6);
            this->planeMesh->setHeight(5);
            this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);

            //Translation pour d�caler les images lors du changement de plan
            this->planeTransform->setTranslation(QVector3D(0, 0.01 * i, 0));

            // Ajout texture � la face recto du plan, � partir d'une image locale suivant la valeur du NumImageTx i
            loader = new Qt3DRender::QTextureLoader(this->planeMesh);
            this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
            string cheminimage;
            string format = ".PNG";
            string numero = to_string(nbImage +i);
            cheminimage = "Images/Coupe" + coupe + "_" + numero + format;
            loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
            this->planeTexture->setTexture(loader);
            loader->setMirrored(false);//Garder le sens correct de l'image
            this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

            //Ajouts des diff�rents composants � l'entit�
            this->planeEntity->addComponent(this->planeMesh);
            this->planeEntity->addComponent(this->planeTexture);
            this->planeEntity->addComponent(this->planeTransform);

            //--------------------------FACE VERSO---------------------------------------
            //Initialisation Entit�, plan et transform
            this->planeEntity = new Qt3DCore::QEntity(&this->scene);
            this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);
            this->planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 180.0f)); //Copie de la texture � 180�

            //Translation pour d�caler les images lors du changement de plan
            this->planeTransform->setTranslation(QVector3D(0, 0.01 * i, 0));

            // Ajout de la m�me texture � la face verso du plan
            loader = new Qt3DRender::QTextureLoader(this->planeMesh);
            this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
            loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
            this->planeTexture->setTexture(loader);

            this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

            //Ajouts des diff�rents composants � l'entit�
            this->planeEntity->addComponent(this->planeMesh);
            this->planeEntity->addComponent(this->planeTexture);
            this->planeEntity->addComponent(this->planeTransform);
        }
        for (int i = 0; i < Milieu; i++)
        {
            //--------------------------FACE RECTO---------------------------------------
            //Initialisation Entit�, plan et transform
            this->planeEntity = new Qt3DCore::QEntity(&this->scene);
            this->planeMesh = new Qt3DExtras::QPlaneMesh(this->planeEntity);
            this->planeMesh->setWidth(6);
            this->planeMesh->setHeight(5);
            this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);

            //Translation pour d�caler les images lors du changement de plan
            this->planeTransform->setTranslation(QVector3D(0, -(0.01 * i), 0));

            // Ajout texture � la face recto du plan, � partir d'une image locale suivant la valeur du NumImageTx i
            loader = new Qt3DRender::QTextureLoader(this->planeMesh);
            this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
            string cheminimage;
            string format = ".PNG";
            string numero = to_string(nbImage -i);
            cheminimage = "Images/Coupe" + coupe + "_" + numero + format;
            loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
            this->planeTexture->setTexture(loader);
            loader->setMirrored(false);//Garder le sens correct de l'image
            this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

            //Ajouts des diff�rents composants � l'entit�
            this->planeEntity->addComponent(this->planeMesh);
            this->planeEntity->addComponent(this->planeTexture);
            this->planeEntity->addComponent(this->planeTransform);

            //--------------------------FACE VERSO---------------------------------------
            //Initialisation Entit�, plan et transform
            this->planeEntity = new Qt3DCore::QEntity(&this->scene);
            this->planeTransform = new  Qt3DCore::QTransform(this->planeMesh);
            this->planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 180.0f)); //Copie de la texture � 180�

            //Translation pour d�caler les images lors du changement de plan
            this->planeTransform->setTranslation(QVector3D(0,-( 0.01 * i), 0));

            // Ajout de la m�me texture � la face verso du plan
            loader = new Qt3DRender::QTextureLoader(this->planeMesh);
            this->planeTexture = new Qt3DExtras::QTextureMaterial(this->planeMesh);
            loader->setSource(QUrl::fromLocalFile(QString::fromStdString(cheminimage)));
            this->planeTexture->setTexture(loader);

            this->planeTexture->setAlphaBlendingEnabled(true);//Rendre transparents les valeurs d'alpha � 0

            //Ajouts des diff�rents composants � l'entit�
            this->planeEntity->addComponent(this->planeMesh);
            this->planeEntity->addComponent(this->planeTexture);
            this->planeEntity->addComponent(this->planeTransform);
        }
    }
}

/*--------------------------------------------------------------------------
* Fonction : createCamera()
*
* Description : Cr�ation de la cam�ra avec un point de vu central sur l'image centrale
* et contr�le de la cam�ra avec la souris classique
*(clic droit : rotaion, clic gauche : translation)
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::createCamera()
{

    //Initialisation de la cam�ra
    this->camera()->lens()->setPerspectiveProjection(10.0f, 1.0f, 0.1f, 1000.0f);
    this->camera()->setPosition(QVector3D(0, 70.0f, 0));
    this->camera()->setViewCenter(QVector3D(0,0, 0));
    this->camera()->setUpVector(QVector3D(0, 0, 1));
   

    //Contr�le de la cam�ra
    this->cameraController = new Qt3DExtras::QOrbitCameraController(&this->scene);
    this->cameraController->setLinearSpeed(10.0f);
    this->cameraController->setLookSpeed(100.0f);
    this->cameraController->setCamera(this->camera());
}

/*--------------------------------------------------------------------------
* Fonction : mouse3DMove()
*
* Description : Contr�le de la sc�ne avec la souris 3D
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::mouse3DMove()
{   
    //Condition si souris en mode interface 2D
    if (mode3D == 0)
        return;

    //Initialisation des transformations de la sc�ne
    this->SceneTransform = new Qt3DCore::QTransform();

    //Passage des valeurs globales en locales
    int h = *compteurTX;
    int l = *compteurTY;
    int m = *compteurTZ;
    int i = *compteurRX;
    int j = *compteurRY;
    int k = *compteurRZ;
    
    if ((pTx > 5) || (pTx < -5) || (pTy > 5) || (pTy < -5) || (pTy > 5) || (pTy < -5) || (pRx > 5) || (pRx < -5) || (pRy > 5) || (pRy < -5) || (pRz > 5) || (pRz < -5)) {
        //R�initialisation de la cam�ra
        this->camera()->lens()->setPerspectiveProjection(10.0f, 1.0f, 0.1f, 1000.0f);
        this->camera()->setPosition(QVector3D(0, 70.0f, 0));
        this->camera()->setViewCenter(QVector3D(0,0, 0));
        this->camera()->setUpVector(QVector3D(0, 0, 1));
    }

    //Translation selon les veleurs de la souris pTx, pTy, pTz
    this->SceneTransform->setTranslation(QVector3D((float)h/10.0, (float)l/2.0, (float)m / 10.0));

    //--------------------------TX-------------------------------
    //Conditions de sensibilit� de la souris 3D
    if ((pTx > 5) && (pTx >= *precValueTX) && (pTx < 20)) {
        h = h - 1;
    }
    else if ((pTx >= 20) && (pTx >= *precValueTX) && (pTx < 600)) {
        h = h - 3;
    }

    else if ((pTx < -5) && (pTx <= *precValueTX) && (pTx > -20)) {
        h = h + 1;
    }
    else if ((pTx <= -20) && (pTx <= *precValueTX) && (pTx > -600)) {
        h = h + 3;
    }

    //M�morisation de la valeur du NumImageTx
    *compteurTX = h;

    //M�morisation de la valeur pTx de la souris 3D
    *precValueTX = pTx; 


    //--------------------------TY-------------------------------
    //Conditions de sensibilit� de la souris 3D
    if ((-pTy > 5) && (-pTy >= *precValueTY) && (-pTy < 20)) {
        l = l - 1;
    }
    else if ((-pTy >= 20) && (-pTy >= *precValueTY) && (-pTy < 600)) {
        l = l - 3;
    }

    else if ((-pTy < -5) && (-pTy <= *precValueTY) && (-pTy > -20)) {
        l = l + 1;
    }
    else if ((-pTy <= -20) && (-pTy <= *precValueTY) && (-pTy > -600)) {
        l = l + 3;
    }

    //M�morisation de la valeur du NumImageTx
    *compteurTY = l;

    //M�morisation de la valeur pTy de la souris 3D
    *precValueTY = -pTy;


    //--------------------------TZ-------------------------------
    //Conditions de sensibilit� de la souris 3D
    if ((-pTz > 5) && (-pTz >= *precValueTZ) && (-pTz < 20)) {
        m = m - 1;
    }
    else if ((-pTz >= 20) && (-pTz >= *precValueTZ) && (-pTz < 600)) {
        m = m - 3;
    }

    else if ((-pTz < -5) && (-pTz <= *precValueTZ) && (-pTz > -20)) {
        m = m + 1;
    }
    else if ((-pTz <= -20) && (-pTz <= *precValueTZ) && (-pTz > -600)) {
        m = m + 3;
    }

    //M�morisation de la valeur du NumImageTx
    *compteurTZ = m;

    //M�morisation de la valeur pTz de la souris 3D
    *precValueTZ = -pTz;


    //--------------------------RX-------------------------------
    //Conditions pour avoir une valeur d'angle coh�rente
    if ((i > -360) && (i < 360)) {
        this->SceneTransform->setRotationX(i);
        
        //Conditions de sensibilit� de la souris 3D
        if ((pRx > 5) && (pRx >= *precValueRX) && (pRx < 20)) {
            i = i - 1;
        }
        else if ((pRx >= 20) && (pRx >= *precValueRX) && (pRx < 600)) {
            i = i - 3;
        }

        else if ((pRx < -5) && (pRx <= *precValueRX) && (pRx > -20)) {
            i = i + 1;
        }
        else if ((pRx <= -20) && (pRx <= *precValueRX) && (pRx > -600)) {
            i = i + 3;
        }
    }

    else if (i <= -360) {
        i = 0;
    }
    else if (i >= 360) {
        i = 0;
    }

    //M�morisation de la valeur du NumImageTx
    *compteurRX = i;

    //M�morisation de la valeur pRx de la souris 3D
    *precValueRX = pRx;

    //--------------------------RY-------------------------------
    //Conditions pour avoir une valeur d'angle coh�rente
    if ((j > -360) && (j < 360)) {
        this->SceneTransform->setRotationY(j);
        
        //Conditions de sensibilit� de la souris 3D
        if ((-pRy > 5) && (-pRy >= *precValueRY) && (-pRy < 20)) {
            j = j - 1;
        }
        else if ((-pRy >= 20) && (-pRy >= *precValueRY) && (-pRy < 600)) {
            j = j - 3;
        }

        else if ((-pRy < -5) && (-pRy <= *precValueRY) && (-pRy > -20)) {
            j = j + 1;
        }
        else if ((-pRy <= -20) && (-pRy <= *precValueRY) && (-pRy > -600)) {
            j = j + 3;
        }
    }

    else if (j <= -360) {
        j = 0;
    }
    else if (j >= 360) {
        j = 0;
    }

    //M�morisation de la valeur du NumImageTx
    *compteurRY = j;

    //M�morisation de la valeur pRy de la souris 3D
    *precValueRY = -pRy;


    //--------------------------RZ-------------------------------
    //Conditions pour avoir une valeur d'angle coh�rente
    if ((k > -360) && (k < 360)) {
        this->SceneTransform->setRotationZ(k);
        //Conditions de sensibilit� de la souris 3D
        if ((-pRz > 5) && (-pRz >= *precValueRZ) && (-pRz < 20)) {
            k = k - 1;
        }
        else if ((-pRz >= 20) && (-pRz >= *precValueRZ) && (-pRz < 600)) {
            k = k - 3;
        }

        else if ((-pRz < -5) && (-pRz <= *precValueRZ) && (-pRz > -20)) {
            k = k + 1;
        }
        else if ((-pRz <= -20) && (-pRz <= *precValueRZ) && (-pRz > -600)) {
            k = k + 3;
        }
    }

    else if (k <= -360) {
        k = 0;
    }
    else if (k >= 360) {
        k = 0;
    }


    //M�morisation de la valeur du NumImageTx
    *compteurRZ = k;

    //M�morisation de la valeur -pRz de la souris 3D
    *precValueRZ = -pRz;


    //Ajout des composants � la sc�ne
    scene.addComponent(this->SceneTransform);
    
}

/*--------------------------------------------------------------------------
* Fonction : Recentrer()
*
* Description : Recentrer l'objet 3D et la cam�ra
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::Recentrer()
{
    this->camera()->setViewCenter(QVector3D(0.0, 0.0, 0.0));//Position initiale
    *compteurTX = 0;
    *compteurTY = 0;
    *compteurTZ = 0;
}

/*--------------------------------------------------------------------------
* Fonction : BloquerScene()
*
* Description : Recentrer l'objet 3D et la cam�ra et le v�rouiller au centre
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::BloquerScene()
{
    this->camera()->setViewCenter(QVector3D(0.0, 0.0, 0.0));//Position initiale
    *compteurTX = 0;
    *compteurTZ = 0;
}

/*--------------------------------------------------------------------------
* Fonction : My3DScene()
*
* Description : Initialisation de la sc�ne et de la souris et construction de la fen�tre
*
* Arguments : Aucun
*
* Valeur retourn�e : Aucune
*--------------------------------------------------------------------------*/
My3DScene::My3DScene()
{
    //Initialisation des variables globales
    init();

    //Construction de la sc�ne
    createObjects();
    createCamera();
    setRootEntity(&scene);
}