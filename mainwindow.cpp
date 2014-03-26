#include "mainwindow.h"
#include "ui_mainwindow.h"

//CONSTRUCTOR
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    documento = TiXmlDocument("documento.xml");
    conexiones = TiXmlDocument("conexiones.xml");
    GenerarMundo();
    ga = new GrafoAeropuerto();
    leerXML();
    showMaximized();
    crearUA();
}

//DES-TRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
}

//ESCRIBE XML
void MainWindow::escrXML(QString ciudad, QString nombre, QString x, QString y)
{
    documento.LoadFile();

    TiXmlElement *element=new TiXmlElement("posicion");
    element->SetAttribute("Pais",ciudad.toStdString().c_str());
    element->SetAttribute("Aeropuerto",nombre.toStdString().c_str());
    element->SetAttribute("posX", LxAux);
    element->SetAttribute("posY", LyAux);

    documento.LinkEndChild(element);
    documento.SaveFile();


}

//LEE XML
void MainWindow::leerXML()
{
    documento.LoadFile();
    TiXmlNode *patr=documento.FirstChild();
    ga = new GrafoAeropuerto();

     while(patr)
     {
         QString codigo = QString::fromUtf8(patr->ToElement()->Attribute("Pais"));
         QString ciudad = QString::fromUtf8(patr->ToElement()->Attribute("Aeropuerto"));
         int x = atoi(patr->ToElement()->Attribute("posX"));
         int y =  atoi(patr->ToElement()->Attribute("posY"));


         ga->insertar_nodo(codigo,x,y);
         crearAeropueto(x+5 ,y+5);

         patr=patr->NextSibling();
    }
}

//AL CLIKEAR CREA UN PUNTITO
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
   if(this->esAdmin != true)
       return;

    if(ev->x() > 10 && ev->x() < 1410)
    {
        if(ev->y() > 50 && ev->y() < 800)
        {
            crearAeropueto(ev->x(),ev->y());
            this->setEnabled(false);
            VentanaIngresar();
        }
    }
}

//GENERA EL PUNTITO DEL AEROPUERTO
void MainWindow::crearAeropueto(int x, int y)
{
    QPixmap punto(":/Images/punto.png");
    imagen=new QLabel(this) ;
    imagen->setPixmap(punto);
    imagen->setScaledContents(true);
    imagen->setGeometry(x-5,y-5,10,10);
    imagen->raise();
    imagen->show();
}

//GENERA TODO EL MAIN WINDOW
void MainWindow::GenerarMundo()
{
    QPushButton *generarBoleto;
    QPushButton *cambiar = new QPushButton(this);

    detalle = new QTextEdit(this);
    detalle->setGeometry(1430,160,150,200);
    detalle->setEnabled(false);
    detalle->show();

    generarBoleto = new QPushButton(this);
    generarBoleto->setGeometry(1430,400,100,23);
    generarBoleto->setText("Generar Boleto");
    generarBoleto->show();

    mostrarCrearConexion = new QPushButton(this);
    cambiar->setText("Pasar a...");
    cambiar->setGeometry(1435,700,150,23);
    cambiar->show();

    //Muesta el mapa

    map = new MapWidget(this);
    map->generarMapa(this);

    //Muestra los Combobox

    c01 = new QComboBox(this);
    c02 = new QComboBox(this);

    c01->setGeometry(1430,60,100,20);
    c01->show();

    c02->setGeometry(1430,130,100,20);
    c02->show();

    actualizarLista();
    on_c01_clicked();

    connect(mostrarCrearConexion, SIGNAL(released()), this, SLOT(on_crear_clicked()));
    connect(cambiar, SIGNAL(released()), this, SLOT(on_cambiar_clicked()));
    connect(c01, SIGNAL(activated(QString)), this, SLOT(on_c01_clicked()));
    connect(generarBoleto, SIGNAL(released()), this, SLOT(on_generarBoleto_clicked()));
}

//GENERA EL CAMINO MAS CORTO, LO MUESTRA VISUALMENTE
void MainWindow::on_generarBoleto_clicked()
{
    if(c02->currentText()==0)
        return;

    aux1 = c01->currentText();
    aux2 = c02->currentText();

    conexiones.LoadFile();
    TiXmlNode *patr0=conexiones.FirstChild();

     while(patr0)
     {
         QString Origen = QString::fromUtf8(patr0->ToElement()->Attribute("Origen"));
         QString Destino = QString::fromUtf8(patr0->ToElement()->Attribute("Destino"));
         QString Costo = QString::fromUtf8(patr0->ToElement()->Attribute("Costo"));

        if(Origen == aux1 && Destino== aux2|| Destino == aux1  && Origen==aux2)
        {
            aux3 = Costo;
            break;
        }
        else
        {
            aux3 = "No Existe";
        }
         patr0=patr0->NextSibling();
    }


     detalle->setText(aux1 + " a " + aux2 + " = " + aux3 );
    detalle->show();

    documento.LoadFile();
    TiXmlNode *patr=documento.FirstChild();

     while(patr)
     {
         QString codigo = QString::fromUtf8(patr->ToElement()->Attribute("Pais"));
         QString ciudad = QString::fromUtf8(patr->ToElement()->Attribute("Aeropuerto"));
         int x = atoi(patr->ToElement()->Attribute("posX"));
         int y =  atoi(patr->ToElement()->Attribute("posY"));

         if(codigo == aux1)
         {
            map->xi = x;
            map->yi = y;
            break;
         }
         if(codigo == aux2)
         {
             map->xf = x;
             map->yf = y;
             break;
         }
         patr=patr->NextSibling();
    }
    if(map->xi == 0)
     map->update();

}

//LLENA EL CB ORIGEN DE CON LOS AEROPUERTOS
void MainWindow::actualizarLista()
{
    documento.LoadFile();
    TiXmlNode *patr=documento.FirstChild();

    while(patr)
    {
        QString country = QString::fromUtf8(patr->ToElement()->Attribute("Pais"));
        c01->addItem(country);
        patr=patr->NextSibling();
    }
}

//VENTANA DE NUEVO AEROPUERTO
void MainWindow::VentanaIngresar()
{
    ingresar = new QMainWindow();
    ingresar->setGeometry(675,200,250,100);

    QLabel *nomb = new QLabel(ingresar);
    QLabel *val = new QLabel(ingresar);
    ciudad = new QLineEdit(ingresar);
    aeropuerto = new QLineEdit(ingresar);
    QPushButton *salir = new QPushButton(ingresar);
    QPushButton *limpiar = new QPushButton(ingresar);
    QPushButton *agregar = new QPushButton(ingresar);


    nomb->setText("Nombre de Ciudad");
    val->setText("Nombre de Aeropuerto");
    agregar->setText("Agregar");
    limpiar->setText("Limpiar");
    salir->setText("Salir");


    ciudad->setGeometry(125,10,100,20);
    aeropuerto->setGeometry(125,35,100,20);
    nomb->setGeometry(10,10,100,20);
    val->setGeometry(10,35,150,20);
    agregar->setGeometry(10,60,70,25);
    limpiar->setGeometry(85,60,70,25);
    salir->setGeometry(160,60,70,25);



    connect(salir, SIGNAL(released()), this, SLOT(on_salir_clicked()));
    connect(limpiar, SIGNAL(released()), this, SLOT(on_limpiar_clicked()));
    connect(agregar, SIGNAL(released()), this, SLOT(on_agregar_clicked()));


    ingresar->show();
}

//BOTON DE CREAR CONEXION/ARISTA
void MainWindow::on_crear_clicked()
{
    this->setEnabled(false);

    crearCon = new QMainWindow();
    crearCon->setGeometry(675,250,250,250);\
    crearCon->show();

    QLabel *ant1 = new QLabel(crearCon);
    QLabel *ant2 = new QLabel(crearCon);
    QLabel *tota = new QLabel(crearCon);
    VdV = new  QLineEdit(crearCon);

    ant1->setText("Pais de Origen");
    ant2->setText("Pais Destino");
    tota->setText("Valor de Vuelo");


    ant1->setGeometry(30,25,150,23);
    ant2->setGeometry(30,80,150,23);
    tota->setGeometry(30,150,150,23);
    VdV->setGeometry(30,170,150,23);

    ant1->show();
    ant2->show();
    tota->show();
    VdV->show();

    QPushButton *cancelar = new QPushButton(crearCon);
    QPushButton *crearConexion = new QPushButton(crearCon);

    cancelar->setText("Cancelar");
    crearConexion->setText("Crear Conexion");

    cancelar->setGeometry(30,200,100,23);
    crearConexion->setGeometry(130,200,100,23);

    cancelar->show();
    crearConexion->show();

    PaisesOrigen = new QComboBox(crearCon);
    PaisesDestino = new QComboBox(crearCon);

    PaisesOrigen->setGeometry(30,50,100,23);
    PaisesDestino->setGeometry(30,100,100,23);


    documento.LoadFile();
    TiXmlNode *patr=documento.FirstChild();

    while(patr)
    {

        QString country = QString::fromUtf8(patr->ToElement()->Attribute("Pais"));
        QString Aeropuerto = QString::fromUtf8(patr->ToElement()->Attribute("Aeropuerto"));
        //int x = atoi(patr->ToElement()->Attribute("posX"));
        //int y =  atoi(patr->ToElement()->Attribute("posY"));

        patr=patr->NextSibling();

        PaisesOrigen->addItem(country);

    }



    PaisesOrigen->show();
    PaisesDestino->show();
    on_Destinos_clicked();

    connect(PaisesOrigen, SIGNAL(activated(QString)), this, SLOT(on_Destinos_clicked()));
    connect(cancelar, SIGNAL(released()), this, SLOT(on_salirCon_clicked()));
    connect(crearConexion, SIGNAL(released()), this, SLOT(on_crearCon_clicked()));
}

//LLENA EL CB DE DESTINOS EN CREAR CONEXION
void MainWindow::on_Destinos_clicked()
{
    PaisesDestino = new QComboBox(crearCon);
    PaisesDestino->setGeometry(30,100,100,23);

    documento.LoadFile();
    TiXmlNode *patr=documento.FirstChild();

    while(patr)
    {
        QString country = QString::fromUtf8(patr->ToElement()->Attribute("Pais"));

        if(PaisesOrigen->currentText() != country)
            PaisesDestino->addItem(country);
        patr=patr->NextSibling();
    }
    PaisesDestino->show();
}

//CIERRA LA VENTANA DE CREAR CONEXION/ARISTA
void MainWindow::on_salirCon_clicked()
{
    crearCon->close();
    this->setEnabled(true);
}

//AGREGA LA CONEXION/ARISTA AL XML
void MainWindow::on_crearCon_clicked()
{
   conexiones.LoadFile();
   TiXmlElement *element=new TiXmlElement("conexion");
   element->SetAttribute("Origen",PaisesOrigen->currentText().toStdString().c_str());
   element->SetAttribute("Destino",PaisesDestino->currentText().toStdString().c_str());
   element->SetAttribute("Costo", VdV->text().toStdString().c_str());
   conexiones.LinkEndChild(element);
   conexiones.SaveFile();

   ga->insertar_arista(PaisesOrigen->currentText(),PaisesDestino->currentText(),VdV->text().toDouble());

   crearCon->close();
   this->setEnabled(true);
}

//CIERRA EL MAINWINDOW
void MainWindow::on_pushButton_clicked()
{
    this->close();
}

//NO HACE UNA M****
void MainWindow::on_boton_clicked()
{

}

//ELIMINA UN PUNTITO EQUIVOCADO
void MainWindow::on_salir_clicked()
{
    this->imagen->deleteLater();
    this->setEnabled(true);
    ingresar->close();
}

//LIMPIA LA VENTANA DE NUEVO AEROPUERTO
void MainWindow::on_limpiar_clicked()
{
    this->ciudad->setText("");
    this->aeropuerto->setText("");
}

//CIERRA EL BOX DE CONFIRMACION DE CREAR AEROPUERTO
void MainWindow::on_ok_clicked()
{
    box->close();
    this->setEnabled(true);
    ingresar->close();
}

//SELECCION ENTRE USER Y MASTER
void MainWindow::crearUA()
{
    this->setEnabled(false);
    UserAdmin = new QMainWindow(this);
    UserAdmin->setGeometry(650,200,300,200);
    UserAdmin->show();

    QPushButton *user = new QPushButton(UserAdmin);
    QPushButton *admin = new QPushButton(UserAdmin);

    user->setText("Usuario");
    admin->setText("Master");

    user->setGeometry(50,20,200,70);
    admin->setGeometry(50,90,200,70);

    user->show();
    admin->show();

    connect(user, SIGNAL(released()), this, SLOT(on_user_clicked()));
    connect(admin, SIGNAL(released()), this, SLOT(on_admin_clicked()));
}

//CREACION EL LOGIN DE ADMIN
void MainWindow::crearAdminLI()
{
    UserAdmin->setEnabled(false);

    AdminLogIn = new QMainWindow();
    AdminLogIn->setGeometry(675,300,250,100);
    AdminLogIn->show();

    QLabel *testo = new QLabel(AdminLogIn);
    testo->setText("Contraseña");
    testo->setGeometry(5,10,100,23);
    testo->show();

    passF = new QLineEdit(AdminLogIn);
    passF->setGeometry(5,30,200,23);
    passF->show();

    QPushButton *acept = new QPushButton(AdminLogIn);
    QPushButton *cancel = new QPushButton(AdminLogIn);

    acept->setText("Aceptar");
    cancel->setText("Cancelar");

    acept->setGeometry(5,70,60,23);
    cancel->setGeometry(80,70,60,23);

    acept->show();
    cancel->show();

    connect(cancel, SIGNAL(released()), this, SLOT(on_LIno_clicked()));
    connect(acept, SIGNAL(released()), this, SLOT(on_LIok_clicked()));
}

//CIERRA EL LOGIN PARA ESCOGER ADMIN/USER
void MainWindow::on_LIno_clicked()
{
    this->UserAdmin->setEnabled(true);
    this->AdminLogIn->close();
}

//CHEKEA SI LA CONTRASEÑA ES CORRECTA
void MainWindow::checkContra(QString contra)
{
    if(contra == "mario")
    {
        esAdmin=true;
        this->setEnabled(true);
        AdminLogIn->close();
        UserAdmin->close();
        if(esAdmin == true)
        {
            mostrarCrearConexion->setText("Crear Nueva Conexion");
            mostrarCrearConexion->setGeometry(1435,750,150,23);
            mostrarCrearConexion->show();
        }
    }
}

//LLENA EL CB DESTINO EN CREACION DE BOLETO
void MainWindow::on_c01_clicked()
{
    c02 = new QComboBox(this);
    c02->setGeometry(1430,130,100,20);

    documento.LoadFile();
    TiXmlNode *patr=documento.FirstChild();
    while(patr)
    {
        QString country = QString::fromUtf8(patr->ToElement()->Attribute("Pais"));
        if(c01->currentText() != country)
            c02->addItem(country);
        patr=patr->NextSibling();
    }
    c02->show();
}

//BOTON DE ACEPTAR EN LOGIN
void MainWindow::on_LIok_clicked()
{
    checkContra(passF->text());
}

//SE CLIKEO EN USER
void MainWindow::on_user_clicked()
{
    esAdmin=false;
    this->setEnabled(true);
    mostrarCrearConexion->setVisible(false);
    UserAdmin->close();
}

// CREA VENTANA DE ISER/ADMIN
void MainWindow::on_cambiar_clicked()
{
    crearUA();
}

//CREA LA VENTANA LOGIN
void MainWindow::on_admin_clicked()
{
    crearAdminLI();
}

//AGREGA EL AEROPUERTP AL XML
void MainWindow::on_agregar_clicked()
{
    ciudadN = ciudad->text();
    AeropuertoN =  aeropuerto->text();
    LxAux = imagen->geometry().x();
    LyAux = imagen->geometry().y();

    Lx = LxAux;
    Ly = LyAux;


    escrXML(ciudadN,AeropuertoN, Lx, Ly);
    ga->insertar_nodo(ciudadN,Lx.toInt(),Ly.toInt());

    ingresar->close();


    box = new QMainWindow();
    QLabel *nota  = new QLabel(box);
    QPushButton *ok  = new QPushButton(box);
    nota->setText("Agregado!!!");
    box->setGeometry(675,200,120,60);
    box->show();
    ok->setText("Aceptar");
    nota->setGeometry(30,10,60,20);
    ok->setGeometry(30,30,60,20);
    ok->show();


    actualizarLista();

    connect(ok, SIGNAL(released()), this, SLOT(on_ok_clicked()));
}
