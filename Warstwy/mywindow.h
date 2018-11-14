// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji
// Szkielet tego pliku jest tworzony przez QtCreator
// Mozemy do niego dodac deklaracje wlasnych pol i metod

#ifndef MYWINDOW_H
#define MYWINDOW_H

// Dolaczamy plik naglowkowy klasy QMainWindow,
// Klasa QMainWindow posiada swoj wlasny layout.
// latwo mozna do niej dodac pasek menu, widzety dokujace,
// pasek narzedzi i pasek statusu. Na srodku okna
// wyswietlanego przez QMainWindow znajduje sie obszar,
// ktory mozna wypelnic roznymi widgetami.
#include <QMainWindow>

// QPainter to klasa umozliwiajaca niskopoziomowe rysowanie
// na elementach GUI
#include <QPainter>

// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>

// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>

namespace Ui {
    class MyWindow;
}

// MyWindow jest podklasa klasy QMainWindow.
class MyWindow : public QMainWindow
{
    // Q_OBJECT jest to makro, ktore musi sie znajdowac
    // we wszystkich klasach definiujacych wlasne sygnaly i sloty
    // W naszej klasie nie jest ono potrzebne,
    // ale QtCreator dodaje je automatycznie do kazdej klasy.
    Q_OBJECT

public:
    // Typowa deklaracja konstruktora w Qt.
    // Parametr "parent" okresla rodzica komponenetu.
    // W przypadku naszej klasy parametr ten wskazuje na null
    // co oznacza, ze komponenet nie ma rodzica, jest to
    // komponenet najwyzszego poziomu
    explicit MyWindow(QWidget *parent = 0);

    // Deklaracja destruktora
    ~MyWindow();

private:
    // QtCreator pozwala na tworzenie GUI za pomoca graficznego kreatora.
    // Skladniki interfejsu i ich wlasciwosci zapisane sa wowczas
    // w pliku XML "nazwa_klasy.ui"
    // Do poszczegolnych elementow GUI odwolujemy sie za pomoca zmiennej "ui"
    Ui::MyWindow *ui;

    // Pole przechowujace obrazek
    QImage *img;
    QVector<QImage*> warstwy;
    bool warstwy_czy_aktywna[6];
    int warstwy_wartosc[6];
    int warstwy_tryb[6];

    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    double alfa = 100;
    int szer;
    int wys;
    int poczX;
    int poczY;
    int x0, y0, x1, y1;
    int tempx0, tempy0;
    int tempx = 0, tempy = 0;
    int ilosc = 3;
    int kolorr = 0;
    int kolorg = 0;
    int kolorb = 0;
    int h,s,v;
    QRgb zmieniany_kolor;
    // Deklaracje funkcji
    void czysc(QImage *img);
    void rysuj(int x, int y);
    void rysuj2(int x, int y);
    void rysuj_odcinek(int x0, int y0, int x1, int y1);
    void rysuj_kolo(int x0, int y0, int x1, int y1);
    void rysuj_elipse(int x0, int y0, int x1, int y1);
    void rysuj_wielokat(int x0, int y0, int x1, int y1, int ilosc);
    QRgb kolor(int x, int y, uchar *ptr);
    int zamaluj_obszar(int x0, int y0, QImage *img);
    void scanline(int x0, int y0, QImage *img);
    void rysuj_figure(int x0, int y0, int x1, int y1);
    void maluj_rgb();
    void hsvtorgb(int hue, double saturation, double value);
    void blending();
      int tryby_kolor(int n, int a, int b);
    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_spinBox_valueChanged(int arg1);
    void on_verticalSlider_3_valueChanged(int value);
    void on_verticalSlider_2_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
    void on_verticalSlider_4_valueChanged(int value);
    void on_verticalSlider_5_valueChanged(int value);
    void on_verticalSlider_6_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);
    void on_checkBox_toggled(bool checked);
    void on_checkBox_2_toggled(bool checked);
    void on_checkBox_3_toggled(bool checked);
    void on_checkBox_4_toggled(bool checked);
    void on_checkBox_5_toggled(bool checked);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_comboBox_Warstwa_5_currentIndexChanged(int index);
    void on_comboBox_Warstwa_6_currentIndexChanged(int index);
    void on_comboBox_Warstwa_7_currentIndexChanged(int index);
    void on_comboBox_Warstwa_8_currentIndexChanged(int index);
    void on_comboBox_Warstwa_9_currentIndexChanged(int index);
};

#endif // MYWINDOW_H
