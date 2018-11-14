#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QDebug>
#include <QtAlgorithms>

#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //timer do animacji
    QTimer *t;
    //szescian [x,y,z][8 pkt]
    int szescian[3][8];
    //macierze do przekształcen
    double obrotTab[4][4];
    double skalowanieTab[4][4];
    double pochylenieTab[4][4];
    double przesuniecieTab[4][4];
    double odwr_wynikowaTab[4][4];
    double wynikowaTab[4][4];

private slots:
    void paintEvent(QPaintEvent*);
    void czysc(QImage *img);
    void geoResetMacierzy();
    void mnozenieMacierzy(double A[4][4], double W[4][4]);

    void przeksztalcWspSzesciana(); //funkjca ktora wyznacza macierz przeksztalcen, wylicza nowe zmodyfikowane pkt i wpisuje je z powrotem do szescianu
    void przepiszObraz(QImage *img1, QImage *img2);

    void zapalPiksel(unsigned char *ptr, int x, int y);
    void rysujSzescian(); // funkcja rysujaca szescian tylko z danych wspolrzednych
    void rysujLinie(int n1, int n2, QImage *img);
    void resetSzescian();
    void przeksztalcWspNa2D(int n); //przeksztalca wsp w przestrzeni 3d na 2d, wykonuje rzutowanie
    void teksturowanie(int wsp_tTr[2][3], int r, int g, int b); //teksturowanie kolorem
    void teksturowanie2(int wsp_Tr[2][3], int ktory); //teksturowanie obrazkiem
    void ustawTr(int pkt0, int pkt1, int pkt2, int pkt3, int wsp_tr0[2][3], int wsp_tr1[2][3]); //wyznacza tablice do teksturowania z danych pkt
    void zamalujSciany(); //
    void swap(int &l1, int &l2);
    void on_skal_Slider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_obrotX_Slider_valueChanged(int value);

    void on_obrotY_Slider_valueChanged(int value);

    void on_obrotZ_Slider_valueChanged(int value);

    void on_przesunX_Slider_valueChanged(int value);

    void on_przesunY_Slider_valueChanged(int value);

    void on_przesunZ_Slider_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_pochylX_Slider_valueChanged(int value);

    void on_pochylY_Slider_valueChanged(int value);

    void on_pochylZ_Slider_valueChanged(int value);
    void on_pushButton_3_clicked();
    void timer_animation();

public slots:


private:
    Ui::MainWindow *ui;

    //bool czyPrzezRuch = false;
    int szer, tex_szer = 300;
    int wys, tex_wys = 300;
    int poczX;
    int poczY;
    int x0, y0, x1, y1;
    //kat do animacji
    int kat = 0;
    //do ukrywania scian
    int ktora_sciana = 4;

    QImage *img, *tmp_img, *texture;
};

#endif // MAINWINDOW_H
