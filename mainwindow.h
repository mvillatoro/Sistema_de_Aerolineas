#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "iostream"
#include "QString"
#include "qpalette.h"
#include "qimage.h"
#include "qtextedit.h"
#include "qlabel.h"
#include "qwidget.h"
#include "qcombobox.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include <QDialog>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <iostream>
#include <QPainter>
#include <QtGui>
#include <QtCore>
#include <qdialog.h>
#include "TinyXml/tinyxml.h"
#include "mapwidget.h"
#include "grafoaeropuerto.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

    TiXmlDocument documento;
    TiXmlDocument conexiones;
    QMainWindow *ingresar;
    QMainWindow *crearCon;
    QMainWindow *UserAdmin;
    QMainWindow *AdminLogIn;
    QMainWindow *box;
    QLineEdit *ciudad;
    QLineEdit *aeropuerto;
    QLineEdit *passF;
    QLineEdit *VdV;
    QTextEdit *detalle;
    QComboBox *PaisesOrigen;
    QComboBox *PaisesDestino;
    QComboBox * c02;
    QComboBox * c01;
    QString ciudadN;
    QString AeropuertoN;
    QString Lx;
    QString Ly;
    QString aux1;
    QString aux2;
    QString aux3;
    QString aux4;
    QLabel *imagen;
    GrafoAeropuerto *ga;

    MapWidget *map;

    QPushButton *mostrarCrearConexion;

  //  int xi, yi, xf, yf;
    int LxAux;
    int LyAux;
    int codigoDeAero;
    bool esAdmin;


    void mousePressEvent(QMouseEvent *ev);
    void GenerarMundo();
    void crearAeropueto(int x, int y);
    void VentanaIngresar();
    void leerXML();
    void escrXML(QString ciudad, QString nombre,QString x, QString y);
    void crearUA();
    void crearAdminLI();
    void actualizarLista();
    void dibujarLinea(int xi, int yi, int xf, int yf);

private slots:
    void on_pushButton_clicked();
    void on_boton_clicked();
    void on_salir_clicked();
    void on_limpiar_clicked();
    void on_agregar_clicked();
    void on_ok_clicked();
    void on_crear_clicked();
    void on_Destinos_clicked();
    void on_salirCon_clicked();
    void on_crearCon_clicked();
    void on_admin_clicked();
    void on_user_clicked();
    void on_cambiar_clicked();
    void on_LIok_clicked();
    void on_LIno_clicked();
    void checkContra(QString contra);
    void on_c01_clicked();
    void on_generarBoleto_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
