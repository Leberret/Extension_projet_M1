/**
 * @Authors: LE FUR Anthony / LE BERRE Thomas
 * @Company: ISEN Yncréa Ouest
 * @Email: anthony.le-fur@isen-ouest.yncrea.fr / thomas.le-berre@isen-ouest.yncrea.fr
 * @Last Modified: 02-Juil-2020
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
* Fonction : initializeGL()
*
* Description : Initialisation de la fenêtre OpenGL et reconstruction 3D
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::initializeGL()
{
    glClearColor(0, 0, 0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);

    QVector<Vec3b>* imgs = VectorImages(allpixels);

    //Création barre de chargement de la reconstruction 3D
    QProgressDialog Chargement ("Reconstruction 3D", "Cancel", 0, *NbFichiers);//Paramètres de la barre
    Chargement.setWindowTitle("Chargement");
    Chargement.setWindowModality(Qt::WindowModal);
    Chargement.setMinimumDuration(5);//Pas de temps mini de chargement

    //Compiler la liste d'affichage, y stocker la reconstruction 3D
    glNewList(1, GL_COMPILE);
    
    float f = round(EcartCoupe*(1/EcartPixel));

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
    
    //Valeurs seuils
    int BackColorB = (*imgs)[1][0] + 40;
    int BackColorG = (*imgs)[1][1] + 40;
    int BackColorR = (*imgs)[1][2] + 40;


    int e = 1;

    //Reconstruction 3D
    int k = 0;
    for (int z = 0; z < *NbFichiers; z++) {

        for (int y = 0; y < ligne; y++) {

            for (int x = 0; x < colonne; x++)
            {
                Vec3b pixel = (*imgs)[k];
                if ((pixel[0] > BackColorB) || (pixel[1] > BackColorG) || (pixel[2] > BackColorR)) {
                    if ((k < colonne * ligne * 1) || (k > colonne * ligne * (*NbFichiers - 1))) {
                        for (int i = 0; i < 6; i++)
                        {
                            glBegin(GL_QUADS);
                            for (int j = 0; j < 4; j++)
                            {
                                glColor4b(pixel[2], pixel[1], pixel[0], 10);
                                glVertex3f((coords[i][j][0] + x)/2, (coords[i][j][1] + y)/2, (coords[i][j][2] + f*z)/2);
                            }
                            glEnd();
                        }
                    }
                    
                    else if ((((*imgs)[k + e][0] < BackColorB)&&((*imgs)[k + e][1] < BackColorG)&&((*imgs)[k + e][2] < BackColorR)) || (((*imgs)[k - e][0] < BackColorB)&& ((*imgs)[k - e][1] < BackColorG)&& ((*imgs)[k - e][2] < BackColorR)) || (((*imgs)[k + e*colonne][0] < BackColorB)&&((*imgs)[k + e*colonne][1] < BackColorG)&& ((*imgs)[k + e*colonne][2] < BackColorR)) || (((*imgs)[k - e*colonne][0] < BackColorB)&& ((*imgs)[k - e*colonne][1] < BackColorG)&& ((*imgs)[k - colonne][2] < BackColorR)) || (((*imgs)[k + e*ligne * colonne][0] < BackColorB)&& ((*imgs)[k + e*ligne * colonne][1] < BackColorG)&& ((*imgs)[k + e*ligne * colonne][2] < BackColorR)) || (((*imgs)[k - e*ligne * colonne][0] < BackColorB)&& ((*imgs)[k - e*ligne * colonne][1] < BackColorG)&& ((*imgs)[k - e*ligne * colonne][2] < BackColorR))) {
                        for (int i = 0; i < 6; i++)
                        {
                            glBegin(GL_QUADS);
                            for (int j = 0; j < 4; j++)
                            {
                                glColor4b(pixel[2], pixel[1], pixel[0], 10);
                                glVertex3f((coords[i][j][0] + x)/2, (coords[i][j][1] + y) / 2, (coords[i][j][2] + f * z) / 2);
                            }
                            glEnd();
                        }
                    }

                }
                k++;
            }
        }
        Chargement.setValue(z);
        if (Chargement.wasCanceled())
            break;
    }
    //Hors de la boucle for, ajout de la valeur max pour fin de chargement
    Chargement.setValue(*NbFichiers);
    glEndList();
}

/*--------------------------------------------------------------------------
* Fonction : resizeGL()
*
* Description : Gestion de la zone de visualisation 3D
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)width / height;
    glFrustum(-x, x, -1.0, 1.0, 15, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

/*--------------------------------------------------------------------------
* Fonction : paintGL()
*
* Description : Translation et rotation de la reconstruction 3D
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(TranslationX, TranslationY, zoomZ - 3000.0);
    glTranslatef(colonne / 2, ligne / 2, *NbFichiers / 2);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glTranslatef(-colonne / 2, -ligne / 2, -*NbFichiers / 2);
 
    glCallList(1);
}

/*--------------------------------------------------------------------------
* Fonction : mousePressEvent()
*
* Description : Récupération de la dernière position de la souris classique
*
* Arguments : event : évènement de la souris classique
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::mousePressEvent(QMouseEvent* event)
{
    lastPosition = event->pos();
}

/*--------------------------------------------------------------------------
* Fonction : mouseMoveEvent()
*
* Description : Contrôle de la scène avec la souris classique
*
* Arguments : event : évènement de la souris classique
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::mouseMoveEvent(QMouseEvent* event)
{

    GLfloat dx = (GLfloat)(event->x() - lastPosition.x()) / width();
    GLfloat dy = (GLfloat)(event->y() - lastPosition.y()) / height();

    if (event->buttons() & Qt::LeftButton)
    {
        TranslationY -= 500 * dy;
        TranslationX += 500 * dx;
        updateGL();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        rotationX += 180 * dy;
        rotationY += 180 * dx;
        updateGL();
    }

    lastPosition = event->pos();
}

void My3DScene::wheelEvent(QWheelEvent* event) {
    zoomZ+= (GLfloat)event->delta();
    updateGL();
}

/*--------------------------------------------------------------------------
* Fonction : VectorImages()
*
* Description : Stockages de tous les pixels de chaque image dans un QVector sous forme de Vec3b
*
* Arguments : *all : vecteur contenant la valeur de tous les pixels de toutes images à la suite
*
* Valeur retournée : ImgVec : vecteur contenant la valeur de tous les pixels de toutes images à la suite sous forme de Vec3b
*--------------------------------------------------------------------------*/
QVector<Vec3b>* My3DScene::VectorImages(QVector<unsigned short>* all) {

    //Barre de chargement
    QProgressDialog Prep("Preparation a la reconstruction 3D", "Cancel", 0, *NbFichiers);//Paramètres de la barre
    Prep.setWindowTitle("Chargement");
    Prep.setWindowModality(Qt::WindowModal);
    Prep.setMinimumDuration(5);//Temps mini de chargement

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
                //if ((*all)[k] > 40)
                    image.at<uchar>(y, x) = (*all)[k];
                /*else
                    image.at<uchar>(y, x) = 0;*/
                k++;
            }
        }

        //Application de la couleur
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

        Prep.setValue(z);
        if (Prep.wasCanceled())
            break;

        MatIterator_<Vec3b> it, end;
        for (it = image.begin<Vec3b>(), end = image.end<Vec3b>(); it != end; ++it)
        {
            ImgVec->push_back(*it);
        }

    }
    //Hors de la boucle for, ajout de la valeur max pour fin de chargement
    Prep.setValue(*NbFichiers);

    return ImgVec;
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

    //Passage des valeurs globales en locales
    int h = *compteurTX;
    int l = *compteurTY;
    int m = *compteurTZ;
    int i = *compteurRX;
    int j = *compteurRY;
    int k = *compteurRZ;



    if ((-pTx > 5)|| (-pTx < -5) || (-pTy > 5) || (-pTy < -5) || (-pTz > 5) || (-pTz < -5) || (-pRx > 5) || (-pRx < -5) || (pRy > 5) || (pRy < -5)|| (pRz > 5) || (pRz < -5))
        updateGL();
    else
        return;

    TranslationX = 10*h;
    //--------------------------TX------------------------------ -
    //Conditions de sensibilité de la souris 3D
    if ((-pTx > 5) && (-pTx >= *precValueTX) && (-pTx < 20)) {
        h = h - 1;
    }
    else if ((-pTx >= 20) && (-pTx >= *precValueTX) && (-pTx < 600)) {
        h = h - 3;
    }

    else if ((-pTx < -5) && (-pTx <= *precValueTX) && (-pTx > -20)) {
        h = h + 1;
    }
    else if ((-pTx <= -20) && (-pTx <= *precValueTX) && (-pTx > -600)) {
        h = h + 3;
    }

    //Mémorisation de la valeur du NumImageTx
    *compteurTX = h;

    //Mémorisation de la valeur -pTx de la souris 3D
    *precValueTX = -pTx;

    zoomZ = 10 * l;

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

    TranslationY = 10* m;

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
        rotationX=i;
        
        //Conditions de sensibilité de la souris 3D
        if ((-pRx > 5) && (-pRx >= *precValueRX) && (-pRx < 20)) {
            i = i - 1;
        }
        else if ((-pRx >= 20) && (-pRx >= *precValueRX) && (-pRx < 600)) {
            i = i - 3;
        }

        else if ((-pRx < -5) && (-pRx <= *precValueRX) && (-pRx > -20)) {
            i = i + 1;
        }
        else if ((-pRx <= -20) && (-pRx <= *precValueRX) && (-pRx > -600)) {
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

    //Mémorisation de la valeur -pRx de la souris 3D
    *precValueRX = -pRx;

    //--------------------------RY-------------------------------
    //Conditions pour avoir une valeur d'angle cohérente
    if ((j > -360) && (j < 360)) {
        rotationY=j;

        //Conditions de sensibilité de la souris 3D
        if ((pRy > 5) && (pRy >= *precValueRY) && (pRy < 20)) {
            j = j - 1;
        }
        else if ((pRy >= 20) && (pRy >= *precValueRY) && (pRy < 600)) {
            j = j - 3;
        }

        else if ((pRy < -5) && (pRy <= *precValueRY) && (pRy > -20)) {
            j = j + 1;
        }
        else if ((pRy <= -20) && (pRy <= *precValueRY) && (pRy > -600)) {
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
    *precValueRY = pRy;


    //--------------------------RZ-------------------------------
    //Conditions pour avoir une valeur d'angle cohérente
    if ((k > -360) && (k < 360)) {
        rotationZ=k;

        //Conditions de sensibilité de la souris 3D
        if ((pRz > 5) && (pRz >= *precValueRZ) && (pRz < 20)) {
            k = k - 1;
        }
        else if ((pRz >= 20) && (pRz >= *precValueRZ) && (pRz < 600)) {
            k = k - 3;
        }

        else if ((pRz < -5) && (pRz <= *precValueRZ) && (pRz > -20)) {
            k = k + 1;
        }
        else if ((pRz <= -20) && (pRz <= *precValueRZ) && (pRz > -600)) {
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

    //Mémorisation de la valeur pRz de la souris 3D
    *precValueRZ = pRz;



}

/*--------------------------------------------------------------------------
* Fonction : Recentrer()
*
* Description : Recentrer l'objet 3D
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::Recentrer()
{
    TranslationX = 0;
    TranslationY = 0;
    zoomZ = 0;
    updateGL();
    *compteurTX = 0;
    *compteurTY = 0;
    *compteurTZ = 0;
}

/*--------------------------------------------------------------------------
* Fonction : BloquerScene()
*
* Description : Recentrer l'objet 3D et le vérouiller au centre
*
* Arguments : Aucun
*
* Valeur retournée : Aucune
*--------------------------------------------------------------------------*/
void My3DScene::BloquerScene()
{
    TranslationX = 0;
    TranslationY = 0;
    updateGL();
    *compteurTX = 0;
    *compteurTZ = 0;
}

//------------------------------------------------------------------------------
//--- Constructors -------------------------------------------------------------
//------------------------------------------------------------------------------
My3DScene::My3DScene()
{
    init();
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    this->TranslationX = 0;
    this->TranslationY = 0;
    this->zoomZ = 0;
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
}




