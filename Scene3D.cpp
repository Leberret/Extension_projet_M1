/**
 * @Authors: LE FUR Anthony / LE BERRE Thomas
 * @Company: ISEN Yncréa Ouest
 * @Email: anthony.le-fur@isen-ouest.yncrea.fr / thomas.le-berre@isen-ouest.yncrea.fr
 * @Last Modified: 30-Apr-2020
 */

#include "Scene3D.h"
#include "DICOM_3Dmouse.h"
#include "Widget3D.h"



/*--------------------------------------------------------------------------
* Fonction : init()
*
* Description : Initialisation des variables globales qui permettent la 
* mémorisation des données réçues par la souris
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
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
* Description : Création des objets 3D constituant la scène 3D, plans 3D
* recouverts d'une texture sur chaque face
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
/*void My3DScene::createObjects()
{
    

    //for (int i = Min; i < Max; i++) {
        
        int c = 5;
        int l = 5;
        
        int k = (colonne * ligne) * 100;
        //int k = (c * l) * 100;

        for (int i = 0; i < l; i++) {

            for (int j = 0; j < c; j++)
            {
                //int pixel = (*allpixels)[k];
                int pixel = 100;
                //if (pixel > 70) {
                    cuboid = new Qt3DExtras::QCuboidMesh();
                    cuboid->setXExtent(1);
                    cuboid->setYExtent(1);
                    cuboid->setZExtent(1);
                    cuboid->setXYMeshResolution(QSize (1,1));
                    cuboid->setXZMeshResolution(QSize(1, 1));

                    Qt3DExtras::QPhongMaterial* cuboidMaterial = new Qt3DExtras::QPhongMaterial();


                    cuboidMaterial->setDiffuse(QColor(pixel, pixel, pixel));
                    cuboidMaterial->setAmbient(QColor(pixel, pixel, pixel));

                    cuboidTransform = new Qt3DCore::QTransform(cuboid);
                    cuboidTransform->setTranslation(QVector3D((float)j, (float)i, 0.0));

                    //Cuboid
                    m_cuboidEntity = new Qt3DCore::QEntity(&this->scene);
                    m_cuboidEntity->addComponent(cuboid);
                    m_cuboidEntity->addComponent(cuboidMaterial);
                    m_cuboidEntity->addComponent(cuboidTransform);
                //}
                


                k++; //Décalage d'une valeur dans le vecteur global
            }
        }
                    
    //}
    
}*/


void My3DScene::initializeGL()
{
    glClearColor(0, 0, 0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glEnable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);


    //Création barre de chargement des images
    /*QProgressDialog Chargement= new QProgressDialog("Reconstruction 3D", "Cancel", 0, *NbFichiers, this);//Paramètres de la barre
    Chargement.setWindowTitle("Chargement");
    Chargement.setMinimumSize(400, 50);
    Chargement.setWindowModality(Qt::WindowModal);
    Chargement.setCancelButton(0);//Impossible d'annuler
    Chargement.setMinimumDuration(5);//Pas de temps mini de chargement*/

    // compile the display list, store a triangle in it
    glNewList(1, GL_COMPILE);
    
    float f = round(EcartCoupe*(1/EcartPixel));
    /*static const GLfloat coords[6][4][3] =
    {
      { { +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 },
      { +1.0, +1.0, -1.0 }, { +1.0, +1.0, +1.0 } },//face de droite
      { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, +1.0 },
      { -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 } },//face de gauche
      { { +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 },
      { -1.0, +1.0, -1.0 }, { +1.0, +1.0, -1.0 } },//face avant
      { { -1.0, -1.0, +1.0 }, { +1.0, -1.0, +1.0 },
      { +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 } },//face arrière
      { { -1.0, -1.0, -1.0 }, { +1.0, -1.0, -1.0 },
      { +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 } },//face du bas
      { { -1.0, +1.0, +1.0 }, { +1.0, +1.0, +1.0 },
      { +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 } }///face du haut
    };*/
    static const GLfloat coords[6][4][3] =
    {
      { { +1.0, -1.0, +f }, { +1.0, -1.0, -f },
      { +1.0, +1.0, -f }, { +1.0, +1.0, +f } },//face de droite
      { { -1.0, -1.0, -f }, { -1.0, -1.0, +f },
      { -1.0, +1.0, +f }, { -1.0, +1.0, -f } },//face de gauche
      { { +1.0, -1.0, -f }, { -1.0, -1.0, -f },
      { -1.0, +1.0, -f }, { +1.0, +1.0, -f } },//face avant
      { { -1.0, -1.0, +f }, { +1.0, -1.0, +f },
      { +1.0, +1.0, +f }, { -1.0, +1.0, +f } },//face arrière
      { { -1.0, -1.0, -f }, { +1.0, -1.0, -f },
      { +1.0, -1.0, +f }, { -1.0, -1.0, +f } },//face du bas
      { { -1.0, +1.0, +f }, { +1.0, +1.0, +f },
      { +1.0, +1.0, -f }, { -1.0, +1.0, -f } }///face du haut
    };
    /*static const GLfloat coords[6][4][3] =
    {
      { { +f, -1.0, +1.0 }, { +f, -1.0, -1.0 },
      { +f, +1.0, -1.0 }, { +f, +1.0, +1.0 } },//face de droite
      { { -f, -1.0, -1.0 }, { -f, -1.0, +1.0 },
      { -f, +1.0, +1.0 }, { -f, +1.0, -1.0 } },//face de gauche
      { { +f, -1.0, -1.0 }, { -f, -1.0, -1.0 },
      { -f, +1.0, -1.0 }, { +f, +1.0, -1.0 } },//face avant
      { { -f, -1.0, +1.0 }, { +f, -1.0, +1.0 },
      { +f, +1.0, +1.0 }, { -f, +1.0, +1.0 } },//face arrière
      { { -f, -1.0, -1.0 }, { +f, -1.0, -1.0 },
      { +f, -1.0, +1.0 }, { -f, -1.0, +1.0 } },//face du bas
      { { -f, +1.0, +1.0 }, { +f, +1.0, +1.0 },
      { +f, +1.0, -1.0 }, { -f, +1.0, -1.0 } }///face du haut
    };*/
    /*static const GLfloat coords[6][4][3] =
    {
      { { +1.0, -f, +1.0 }, { +1.0, -f, -1.0 },
      { +1.0, +f, -1.0 }, { +1.0, +f, +1.0 } },//face de droite
      { { -1.0, -f, -1.0 }, { -1.0, -f, +1.0 },
      { -1.0, +f, +1.0 }, { -1.0, +f, -1.0 } },//face de gauche
      { { +1.0, -f, -1.0 }, { -1.0, -f, -1.0 },
      { -1.0, +f, -1.0 }, { +1.0, +f, -1.0 } },//face avant
      { { -1.0, -f, +1.0 }, { +1.0, -f, +1.0 },
      { +1.0, +f, +1.0 }, { -1.0, +f, +1.0 } },//face arrière
      { { -1.0, -f, -1.0 }, { +1.0, -f, -1.0 },
      { +1.0, -f, +1.0 }, { -1.0, -f, +1.0 } },//face du bas
      { { -1.0, +f, +1.0 }, { +1.0, +f, +1.0 },
      { +1.0, +f, -1.0 }, { -1.0, +f, -1.0 } }///face du haut
    };*/
    QVector<Vec3b>* imgs = VectorImages(allpixels);
    
    int k = 0*colonne*ligne;
    for (int z = 0; z < *NbFichiers; z++) {

        for (int y = 0; y < ligne; y++) {

            for (int x = 0; x < colonne; x++)
            {
                Vec3b pixel = (*imgs)[k];
                //if((pixel[0]==pixel[1])&&(pixel[0]==pixel[2])){ //si noir et blanc
                    if ((pixel[0] > 40) || (pixel[1] > 40) || (pixel[2] > 40)) {
                        if ((k < colonne * ligne * 1) || (k > colonne * ligne * (*NbFichiers - 1))) {
                            for (int i = 0; i < 6; i++)
                            {
                                glBegin(GL_QUADS);
                                for (int j = 0; j < 4; j++)
                                {
                                    glColor4b(pixel[2], pixel[1], pixel[0], 100);
                                    glVertex3f(coords[i][j][0] + x, coords[i][j][1] + y, coords[i][j][2] + f*z);
                                }
                                glEnd();
                            }
                        }

                        else if ((((*imgs)[k + 1][0] < 40)&&((*imgs)[k + 1][1] < 40)&&((*imgs)[k + 1][2] < 40)) || (((*imgs)[k - 1][0] < 40)&& ((*imgs)[k - 1][1] < 40)&& ((*imgs)[k - 1][2] < 40)) || (((*imgs)[k + colonne][0] < 40)&&((*imgs)[k + colonne][1] < 40)&& ((*imgs)[k + colonne][2] < 40)) || (((*imgs)[k - colonne][0] < 40)&& ((*imgs)[k - colonne][1] < 40)&& ((*imgs)[k - colonne][2] < 40)) || (((*imgs)[k + ligne * colonne][0] < 40)&& ((*imgs)[k + ligne * colonne][1] < 40)&& ((*imgs)[k + ligne * colonne][2] < 40)) || (((*imgs)[k - ligne * colonne][0] < 40)&& ((*imgs)[k - ligne * colonne][1] < 40)&& ((*imgs)[k - ligne * colonne][2] < 40))) {
                            for (int i = 0; i < 6; i++)
                            {
                                glBegin(GL_QUADS);
                                for (int j = 0; j < 4; j++)
                                {
                                    //glColor4b(pixel[0], pixel[1], pixel[2], 100);

                                    glColor4b(pixel[2], pixel[1], pixel[0], 10);
                                    glVertex3f(coords[i][j][0] + x, coords[i][j][1] + y, coords[i][j][2] + f * z);
                                }
                                glEnd();
                            }
                        }
                    }
                //}
                
                k++;
            }
        }
        //Chargement->setValue(z);
        
    }
    //Hors de la boucle for, ajout de la valeur max pour fin de chargement
    //Chargement->setValue(*NbFichiers);
    //delete Chargement;
    glEndList();
}

void My3DScene::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)width / height;
    glFrustum(-x, x, -1.0, 1.0, 15.0, 3500.0);
    glMatrixMode(GL_MODELVIEW);
}

void My3DScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0, 0.0, -3000.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
 
    glCallList(1);
}



void My3DScene::mousePressEvent(QMouseEvent* event)
{
    lastPosition = event->pos();
}

void My3DScene::mouseMoveEvent(QMouseEvent* event)
{
    GLfloat dx = (GLfloat)(event->x() - lastPosition.x()) / width();
    GLfloat dy = (GLfloat)(event->y() - lastPosition.y()) / height();
    if (event->buttons() & Qt::LeftButton)
    {
        rotationX += 180 * dy;
        rotationY += 180 * dx;
        updateGL();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        rotationX += 180 * dy;
        rotationZ += 180 * dx;
        updateGL();
    }
    lastPosition = event->pos();
}


QVector<Vec3b>* My3DScene::VectorImages(QVector<unsigned short>* all) {

    //Création d'un image vide de la taille obtenue dans OuvrirFichier
    ImgVec=new QVector<Vec3b>;
    int k=0;
    for (int z = 0; z < *NbFichiers; z++) {
        Mat image = Mat::zeros(ligne, colonne, CV_8UC1);
        for (int y = 0; y < ligne; y++)
        {
            for (int x = 0; x < colonne; x++)
            {
                // get pixel 
                image.at<uchar>(y, x) = (*all)[k];
                k++;
            }
        }
        //Mat image;// = Mat::zeros(ligne, colonne, CV_16UC3);


        //Application de la couleur et convertion en format adapté
        switch (*NbCouleurs)
        {
        case 0:
            cvtColor(image, image, COLOR_GRAY2BGR);
            break;
        case 1:
            applyColorMap(image, image, COLORMAP_JET);//Application de la couleur a l'image
            break;
        case 2:
            applyColorMap(image, image, COLORMAP_BONE);//Application de la couleur a l'image
            break;
        case 3:
            applyColorMap(image, image, COLORMAP_CIVIDIS);//Application de la couleur a l'image
            break;
        case 4:
            applyColorMap(image, image, COLORMAP_TURBO);//Application de la couleur a l'image
            break;
        case 5:
            applyColorMap(image, image, COLORMAP_HOT);//Application de la couleur a l'image
            break;
        case 6:
            applyColorMap(image, image, COLORMAP_PARULA);//Application de la couleur a l'image
            break;
        case 7:
            applyColorMap(image, image, COLORMAP_TWILIGHT_SHIFTED);//Application de la couleur a l'image
            break;
        }

        //QVector<Vec3b> pixels;

        MatIterator_<Vec3b> it, end;
        for (it = image.begin<Vec3b>(), end = image.end<Vec3b>(); it != end; ++it)
        {
            ImgVec->push_back(*it);
        }

    }


    return ImgVec;
}


//------------------------------------------------------------------------------
//--- Constructors -------------------------------------------------------------
//------------------------------------------------------------------------------
My3DScene::My3DScene()
{
    init();
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
}





/*--------------------------------------------------------------------------
* Fonction : mouse3DMove()
*
* Description : Contrôle de la scène avec la souris 3D
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::mouse3DMove()
{   
    //Condition si souris en mode interface 2D
    if (mode3D == 0)
        return;

    //Initialisation des transformations de la scène
    //this->SceneTransform = new Qt3DCore::QTransform();

    //Passage des valeurs globales en locales
    int h = *compteurTX;
    int l = *compteurTY;
    int m = *compteurTZ;
    int i = *compteurRX;
    int j = *compteurRY;
    int k = *compteurRZ;
    
    if ((pTx > 5) || (pTx < -5) || (pTy > 5) || (pTy < -5) || (pTy > 5) || (pTy < -5) || (pRx > 5) || (pRx < -5) || (pRy > 5) || (pRy < -5) || (pRz > 5) || (pRz < -5)) {
        //Réinitialisation de la caméra
        /*this->camera()->lens()->setPerspectiveProjection(10.0f, 1.0f, 0.1f, 1000.0f);
        this->camera()->setPosition(QVector3D(0, 70.0f, 0));
        this->camera()->setViewCenter(QVector3D(0,0, 0));
        this->camera()->setUpVector(QVector3D(0, 0, 1));*/
    }

    //Translation selon les veleurs de la souris pTx, pTy, pTz
    //this->SceneTransform->setTranslation(QVector3D((float)h/10.0, (float)l/2.0, (float)m / 10.0));

    //--------------------------TX-------------------------------
    //Conditions de sensibilité de la souris 3D
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

    //Mémorisation de la valeur du NumImageTx
    *compteurTX = h;

    //Mémorisation de la valeur pTx de la souris 3D
    *precValueTX = pTx; 


    //--------------------------TY-------------------------------
    //Conditions de sensibilité de la souris 3D
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

    //Mémorisation de la valeur du NumImageTx
    *compteurTY = l;

    //Mémorisation de la valeur pTy de la souris 3D
    *precValueTY = -pTy;


    //--------------------------TZ-------------------------------
    //Conditions de sensibilité de la souris 3D
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

    //Mémorisation de la valeur du NumImageTx
    *compteurTZ = m;

    //Mémorisation de la valeur pTz de la souris 3D
    *precValueTZ = -pTz;


    //--------------------------RX-------------------------------
    //Conditions pour avoir une valeur d'angle cohérente
    if ((i > -360) && (i < 360)) {
        //this->SceneTransform->setRotationX(i);
        
        //Conditions de sensibilité de la souris 3D
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

    //Mémorisation de la valeur du NumImageTx
    *compteurRX = i;

    //Mémorisation de la valeur pRx de la souris 3D
    *precValueRX = pRx;

    //--------------------------RY-------------------------------
    //Conditions pour avoir une valeur d'angle cohérente
    if ((j > -360) && (j < 360)) {
        //this->SceneTransform->setRotationY(j);
        
        //Conditions de sensibilité de la souris 3D
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

    //Mémorisation de la valeur du NumImageTx
    *compteurRY = j;

    //Mémorisation de la valeur pRy de la souris 3D
    *precValueRY = -pRy;


    //--------------------------RZ-------------------------------
    //Conditions pour avoir une valeur d'angle cohérente
    if ((k > -360) && (k < 360)) {
        //this->SceneTransform->setRotationZ(k);
        //Conditions de sensibilité de la souris 3D
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


    //Mémorisation de la valeur du NumImageTx
    *compteurRZ = k;

    //Mémorisation de la valeur -pRz de la souris 3D
    *precValueRZ = -pRz;


    //Ajout des composants à la scène
    //scene.addComponent(this->SceneTransform);
    
}

/*--------------------------------------------------------------------------
* Fonction : Recentrer()
*
* Description : Recentrer l'objet 3D et la caméra
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::Recentrer()
{
    //this->camera()->setViewCenter(QVector3D(0.0, 0.0, 0.0));//Position initiale
    *compteurTX = 0;
    *compteurTY = 0;
    *compteurTZ = 0;
}

/*--------------------------------------------------------------------------
* Fonction : BloquerScene()
*
* Description : Recentrer l'objet 3D et la caméra et le vérouiller au centre
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::BloquerScene()
{
    //this->camera()->setViewCenter(QVector3D(0.0, 0.0, 0.0));//Position initiale
    *compteurTX = 0;
    *compteurTZ = 0;
}


