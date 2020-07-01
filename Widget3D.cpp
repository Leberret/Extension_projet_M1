/**
 * @Authors: LE FUR Anthony / LE BERRE Thomas
 * @Company: ISEN Yncr�a Ouest
 * @Email: anthony.le-fur@isen-ouest.yncrea.fr / thomas.le-berre@isen-ouest.yncrea.fr
 * @Last Modified: 30-Apr-2020
 */

#include "DICOM_3Dmouse.h"
#include "Scene3D.h"
#include "Widget3D.h"


/*--------------------------------------------------------------------------
* Fonctions : DoubleClics()
*
* Description : Appel SaveAs si les 2 boutons de la souris 3D sont
* press� enssemble ou non
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::DoubleClics3D() {
    //Condition si souris 3D d�sactiv�e ou en mode interfae 2D
    if (mode3D == 0)
        return;

    //Condition de double clics
    if ((clicD == 1) && (clicG == 1)) {
        SaveAs3D();
        clicD = 0;
        clicG = 0;
    }
    else
        return;
}

/*--------------------------------------------------------------------------
* Fonctions : ClicDroit3D()
*
* Description : Appel la fonction bloquer si le bouton gauche de la souris 
* 3D est press�
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::ClicDroit3D() {
    //Condition si souris d�sactiv�e ou en mode interface 3D
    if (mode3D == 0)
        return;

    int clicg = FixeClic; //vaut 1 au 1er clic et 0 au 2e clic sur bouton droit

    //Condition si clic sur bouton droit de la souris 3D
    if (clicg == 1)
        bloquer();
    else
        return;
}

/*--------------------------------------------------------------------------
* Fonctions : ClicGauche3D()
*
* Description : Appel la fonction centrage si le bouton droit de la souris
* 3D est press�
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::ClicGauche3D() {
    //Condition si souris en mode interface 2D
    if (mode3D == 0)
        return;

    //Conditon si le bouton cliqu�
    if ((clicG==1)&&(clicD==0)){
        centrage();
    }
    else { //Au deuxi�me clic
        return;
    }
}

/*--------------------------------------------------------------------------
* Fonctions : SaveAs()
*
* Description : Permet de screenshoter l'interafce de reconstruction 3D
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::SaveAs3D() {
    qApp->beep(); // Signal the screenshoot

        //Initialisation de la hauteur des images
    int tailleLimite_Y;


    //R�cup�ration des coordon�es du container contenant la Scene 3D
    QPoint coord = container->pos();
    int container_x = coord.x();
    int container_y = coord.y();


    // Prise du screenshoot
    QPixmap pixmap3D = QPixmap::grabWindow(this->winId(), container_x, container_y, -1, -1);

    //Fen�tre d'enregistrement
    QString filePath3D = QFileDialog::getSaveFileName(this, tr("Enregistrer sous"), "../Screenshot3D_1.png", tr("Images (*.png *.xpm *.jpg)"));

    //Sauvegarde de l'image
    pixmap3D.save(filePath3D);

}

/*--------------------------------------------------------------------------
* Fonctions : closeEvent()
*
* Description : Permet de lib�rer la m�moire lors de la fermeture de la fen�tre
*
* Arguments : event : �venement de fermeture de la fen�tre
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::closeEvent(QCloseEvent* event)
{
    this->deleteLater();
    event->accept();

}

/*--------------------------------------------------------------------------
* Fonctions : centrage()
*
* Description : Appel de la fonction de recentrage de l'objet 3D dans la 
* classe My3DScene
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::centrage() {
    Visualisation3D->Recentrer();
}

/*--------------------------------------------------------------------------
* Fonctions : bloquer()
*
* Description : Appel de la fonction de recentrage et de bloquage de l'objet 3D dans la
* classe My3DScene
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::bloquer() {
    Visualisation3D->BloquerScene();
}

/*--------------------------------------------------------------------------
* Fonctions : Actu3D()
*
* Description : Appel de la fonction de mouse3DMove de la classe My3DScene
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::Actu3D() {
   Visualisation3D->mouse3DMove();
}

/*--------------------------------------------------------------------------
* Fonctions : AIDE3D()
*
* Description : Affiche une fen�tre expliquant les diversses actions de la
* souris 3D
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
void Widget3D::AIDE3D()
{
    QMessageBox aide;
    aide.setWindowTitle("Aide utilisation logiciel avec Souris 3D");
    QString n = "\n";
    aide.setWindowIcon(QIcon("icon.png"));
    aide.setIcon(QMessageBox::Information);
    aide.setText("Centrer la camera et l'objet :" + n +
        "   -> Presser sur le bouton de gauche de votre souris 3D." + n +
        " Realiser une capture d'ecran :" + n +
        "   -> Presser simultanement des deux boutons lateraux de votre souris 3D." + n +
        " Bloquer l'objet en position centrale : " + n +
        "   -> Presser sur le bouton de droite de votre souris 3D");
    aide.exec();
}

/*--------------------------------------------------------------------------
* Fonctions : Widget3D()
*
* Description : Construction de la fen�tre 3D
*
* Arguments : aucun
*
* Valeur retourn�e : aucune
*--------------------------------------------------------------------------*/
Widget3D::Widget3D()
{
    //Initialisation des �l�ments
    Visualisation3D = new My3DScene();
    Layout = new QGridLayout();
    menu = new QMenuBar();//Initialisation Barre de menus
    Fichier = new QMenu("&Fichier");//Init menu fichier
    Affichage = new QMenu("&Affichage");//Init menu affichage


    //Actions li�es aux diff�rents menus
    Fichier->addAction("Enregistrer sous", this, SLOT(SaveAs3D()));
    Affichage->addAction("Recentrer", this, SLOT(centrage()));

    //Conversion de la Scene3d en QWidget et fixation de sa taille
    QHBoxLayout* container = new QHBoxLayout;
    container->addWidget(Visualisation3D);
    QWidget* w = new QWidget;
    w->setLayout(container);
    //Ajout des composants � leurs entit�s
    menu->addMenu(Fichier);
    menu->addMenu(Affichage);    
    menu->addAction("Aide", this, SLOT(AIDE3D()));
    Fichier->setStyleSheet("color: white;"
        "background-color:rgb(30,30,30);"
        "selection-color: black;"
        "border-radius: 0px;"
        "selection-background-color: rgb(230,230,230);");
    Affichage->setStyleSheet("color: white;"
        "background-color:rgb(30,30,30);"
        "selection-color: black;"
        "border-radius: 0px;"
        "selection-background-color: rgb(230,230,230);");
    menu->setStyleSheet("color: black;"
        "background-color:rgb(230,230,230);"
        "selection-color: black;"
        "border-radius: 0px;"
        "selection-background-color:rgb(30,30,30) ;");
    Layout->setMenuBar(menu);
    Layout->addWidget(w);

    //Appel des fonctions toutes les 10ms
    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(Actu3D()));
    connect(timer, SIGNAL(timeout()), this, SLOT(DoubleClics3D()));
    connect(timer, SIGNAL(timeout()), this, SLOT(ClicDroit3D()));
    connect(timer, SIGNAL(timeout()), this, SLOT(ClicGauche3D()));

    timer->start(10);

    //param�tres du widget
    setLayout(Layout);
    setStyleSheet("background-color:white;");
    //setFixedSize(1000, 800);
    setWindowState(windowState() | Qt::WindowMaximized);//Fenetre en plein ecran

    setWindowIcon(QIcon("icon.png"));
    setWindowTitle("Interface de reconstruction 3D des IRM");//titre fenetre

    show();
}
