#include "mywindow.h"
#include "ui_mywindow.h"
#include "math.h"
#include "QStack"
using namespace std;
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MyWindow)
{
    // Wywolujemy funkcje tworzaca elementy GUI
    // Jej definicja znajduje sie w pliku "ui_mywindow.h"
    ui->setupUi(this);

    // Pobieramy wymiary i wspolrzedne lewego gornego naroznika ramki
    // i ustawiamy wartosci odpowiednich pol
    // Uwaga: ramke "rysujFrame" wykorzystujemy tylko do
    // wygodnego ustaiwenia tych wymiarow. Rysunek bedziemy wyswietlac
    // bezposrednio w glownym oknie aplikacji.
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);

    warstwy.append(img);
    warstwy.append(new QImage(":/1.jpg"));
    warstwy.append(new QImage(":/2.jpg"));
    warstwy.append(new QImage(":/3.jpg"));
    warstwy.append(new QImage(":/4.jpg"));
    warstwy.append(new QImage(":/5.jpg"));
    czysc(warstwy[0]);

    for(int i = 1; i <= 5; i++)
    {
        warstwy_tryb[i] = 1;
        warstwy_wartosc[i] = 0;
        warstwy_czy_aktywna[i] = false;
    }
}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete ui;
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Wyjscie" (exitButton)
// Uwaga: polaczenie tej funkcji z sygnalem "clicked"
// emitowanym przez przycisk jest realizowane
// za pomoca funkcji QMetaObject::connectSlotsByName(MyWindow)
// znajdujacej sie w automatycznie generowanym pliku "ui_mywindow.h"
// Nie musimy wiec sami wywolywac funkcji "connect"
void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}

// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::on_cleanButton_clicked()
{
    czysc(img);
    update();
    tempx = 0;
    tempy = 0;
}

// Funkcja powoduje wyczyszczenie (zamalowanie na bialo)
// obszaru rysowania
void MyWindow::czysc(QImage *img)
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;
    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();
    int i,j;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer * 4 * i + 4 * j    ] = 0; // Skladowa BLUE
            ptr[szer * 4 * i + 4 * j + 1] = 0; // Skladowa GREEN
            ptr[szer * 4 * i + 4 * j + 2] = 0; // Skladowa RED
        }
    }
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    // Sa to wspolrzedne wzgledem glownego okna
    x0 = event->x();
    y0 = event->y();

    // Przesuwamy je zeby nie rysowac od brzegu
    x0 = x0 - poczX;
    y0 = y0 - poczY;

}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    // Sa to wspolrzedne wzgledem glownego okna
    x1 = event->x();
    y1 = event->y();
    // Przesuwamy je zeby nie rysowac od brzegu
    x1 = x1 - poczX;
    y1 = y1 - poczY;

    if (x1 > szer) x1 = szer;
    if (y1 > wys) y1 = wys;
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;

    //Rysowanie lini
    if (ui -> radioButton -> isChecked())
    {
        rysuj_odcinek(x0,y0,x1,y1);
        update();
    }

    //Rysowanie koła
    if (ui -> radioButton_2 -> isChecked())
    {
        rysuj_kolo(x0,y0,x1,y1);
        update();
    }

    //Rysowanie elipsy
    if (ui -> radioButton_3 -> isChecked())
    {
        rysuj_elipse(x0,y0,x1,y1);
        rysuj_wielokat(x0,y0,x1,y1,ilosc);
        update();
    }
    if (ui -> radioButton_4 -> isChecked())
    {
        unsigned char *ptr;
        ptr = img->bits();
        kolor(x1, y1,  ptr);
        zamaluj_obszar(x0, y0, img);
    }
    if (ui -> radioButton_5 -> isChecked())
    {

        rysuj_figure(x0,y0,x1,y1);
    }
}

//Funkcja do rysowania pikseli
void MyWindow::rysuj(int x, int y)
{
    unsigned char *ptr;
    ptr = img->bits();
    if (szer - x > 0 && szer + x >= szer && wys - y > 0 && wys + y >= wys)
    {
        ptr[szer * 4 * y + 4 * x] = 255;
        ptr[szer * 4 * y + 4 * x + 1] = 255;
        ptr[szer * 4 * y + 4 * x + 2] = 255;
    }
}
void MyWindow::rysuj2(int x, int y)
{
    unsigned char *ptr;
    ptr = img->bits();
    if (szer - x > 0 && szer + x >= szer && wys - y > 0 && wys + y >= wys)
    {
        ptr[szer * 4 * y + 4 * x] = 255;
        ptr[szer * 4 * y + 4 * x + 1] = 0;
        ptr[szer * 4 * y + 4 * x + 2] = 0;
    }
}
void MyWindow::rysuj_odcinek(int x0,int y0,int x1,int y1)
{

    int x,y;
    double a = (double)(y1 - y0) / (x1 - x0);
    double b = y0 - (a * x0);
    if(a <= 1 && a >= -1){
        if (x0 < x1){
            for(x = x0; x <= x1; x++){
                y = a * x + b;
                rysuj(x,y);
            }
        }
        else{
            for(x = x1; x <= x0; x++){
                y = a * x + b;
                rysuj(x,y);
            }
        }
    }
    else{
        if (y0 < y1){
            for(y = y0; y <= y1; y++){
                x = (y - b) / a;
                rysuj(x,y);
            }
        }
        else{
            for(y = y1; y <= y0; y++){
                x = (y - b) / a;
                rysuj(x,y);
            }
        }
    }
}

void MyWindow::rysuj_kolo(int x0,int y0,int x1,int y1)
{
    double r = sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)) );
    double z = r / sqrt(2);
    int x, y;
    for (x = 0; x <= z; x++)
    {
        y = sqrt((r * r) - (x * x));
        rysuj(x0 + x, y0 + y);
        rysuj(x0 + x, y0 - y);
        rysuj(x0 - x, y0 + y);
        rysuj(x0 - x, y0 - y);
        rysuj(x0 + y, y0 + x);
        rysuj(x0 + y, y0 - x);
        rysuj(x0 - y, y0 + x);
        rysuj(x0 - y, y0 - x);

    }
}

void MyWindow::rysuj_elipse(int x0, int y0, int x1, int y1)
{
    double a = sqrt(((x1 - x0) * (x1 - x0)));
    double b = sqrt(((y1 - y0) * (y1 - y0)));
    double t;
    double x,y;
    double ile = 2 * M_PI;
    for (t = 0; t < ile; t += 0.001)
    {
        x = a * cos(t);
        y = b * sin(t);
        rysuj(x0 + (int)floor(x),y0 + (int)floor(y));
    }
}

void MyWindow::rysuj_wielokat(int x0, int y0, int x1, int y1, int ilosc)
{
    double t;
    double ile = 2 * M_PI;
    double a = sqrt(((x1 - x0) * (x1 - x0)));
    double b = sqrt(((y1 - y0) * (y1 - y0)));
    double tmpx = a * cos(ile);
    double tmpy = b * sin(ile);
    double x, y;
    for (t = 0; t <= ile; t += (ile/ilosc))
    {
        x = a * cos(t);
        y = b * sin(t);
        rysuj_odcinek(x0 + (int)floor(tmpx + 0.5), y0 +(int)floor(tmpy + 0.5), x0 + (int)floor(x + 0.5), y0 +(int)floor(y + 0.5));
        tmpx = x;
        tmpy = y;
    }
}


void MyWindow::on_spinBox_valueChanged(int arg1)
{
    ilosc = arg1;
}

QRgb MyWindow::kolor(int x, int y, uchar *ptr)
{
    int r, g, b;
    b = ptr[szer*4*y + 4*x];
    g = ptr[szer*4*y + 4*x + 1];
    r = ptr[szer*4*y + 4*x + 2];
    QRgb kolorek;
    kolorek = qRgb(r, g, b);
    return kolorek;
}

int MyWindow::zamaluj_obszar(int x0, int y0, QImage *img)
{
    uchar *ptr;
    ptr = img->bits();
    zmieniany_kolor = qRgb(ptr[szer*4*y1 + 4*x1 + 2], ptr[szer*4*y1 + 4*x1 + 1], ptr[szer*4*y1 + 4*x1]);

    //przygotowania do zamalowania
    int x, y, w, e;
    QStack<int> Q;

    //właściwy algorytm do zamalowania obszaru
    if(kolor(x0, y0, ptr) != zmieniany_kolor) return 1;
    Q.push(x0);
    Q.push(y0);
    while(!Q.isEmpty())
    {
        y = Q.pop();
        x = Q.pop();
        if(kolor(x, y, ptr) == zmieniany_kolor)
        {
            w = x;
            e = x;
            while(kolor(w, y, ptr) == zmieniany_kolor && w >= 0) w--;
            while(kolor(e, y, ptr) == zmieniany_kolor && e+1 <= szer) e++;

            for(int i = w + 1; i < e; i++)
            {
                rysuj2(i, y);
            }
            for(int i = w + 1; i < e; i++)
            {
                if(y+1 < wys && y-1 >= 0)
                {
                    if(kolor(i, y+1, ptr) == zmieniany_kolor)
                    {
                        Q.push(i);
                        Q.push(y+1);
                    }
                    if(kolor(i, y-1, ptr) == zmieniany_kolor)
                    {
                        Q.push(i);
                        Q.push(y-1);
                    }
                }
            }
        }
    }
    update();
    return 0;
}

void MyWindow::rysuj_figure(int x0, int y0, int x1, int y1){
    if (tempx == 0 && tempy == 0){
        rysuj_odcinek(x0,y0,x1,y1);
        tempx = x1;
        tempy = y1;
        tempx0 = x0;
        tempy0 = y0;
    } else if (sqrt(((x1 - tempx0) * (x1 - tempx0)) + ((y1 - tempy0) * (y1 - tempy0))) < 4){
        rysuj_odcinek(tempx,tempy,tempx0,tempy0);
        tempx = 0;
        tempy = 0;
    } else{
        rysuj_odcinek(tempx,tempy,x1,y1);
        tempx = x1;
        tempy = y1;
    }
    update();
}



//Red
void MyWindow::on_verticalSlider_3_valueChanged(int value)
{
    kolorr = value;
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]= i  * 255 / 600; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] =  j * 255 / 600; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] =  kolorr; // Skladowa RED
        }
    }
    update();
}
//Green
void MyWindow::on_verticalSlider_2_valueChanged(int value)
{
    kolorg = value;
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]= i  * 255 / 600; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] =  kolorg; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] =  j * 255 / 600; // Skladowa RED
        }
    }
    update();
}
//Blue
void MyWindow::on_verticalSlider_valueChanged(int value)
{
    kolorb = value;
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]= kolorb; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] =  i * 255 / 600; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] =  j * 255 / 600; // Skladowa RED
        }
    }
    update();
}

void MyWindow::hsvtorgb(int hue,double saturation, double value)
{
    double c = value * saturation;
    double x = c * ( 1 - fabs((fmod((double)hue / 60, 2)) - 1));
    double m = value - c;
    double red, blue, green;
    red = (c + m) * 255;
    green = m * 255;
    blue = (x + m) * 255;
    if(hue >= 0 && hue < 60)
    {
       kolorr = red;
       kolorg = blue;
       kolorb = green;

    }
    else if(hue >= 60 && hue < 120)
    {

       kolorr = blue;
       kolorg = red;
       kolorb = green;
    }
    else if(hue >= 120 && hue < 180)
    {

       kolorr = green;
       kolorg = red;
       kolorb = blue;
    }
    else if(hue >= 180 && hue < 240)
    {

       kolorr = green;
       kolorg = blue;
       kolorb = red;
    }
    else if(hue >= 240 && hue < 300)
    {

       kolorr = blue;
       kolorg =green;
       kolorb = red;
    }
    else if(hue >= 300 && hue < 360)
    {

       kolorr = red;
       kolorg =green;
       kolorb = red;
    }
}

void MyWindow::on_verticalSlider_4_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
             hsvtorgb(value,(double)i/szer,(double)j/wys);
            ptr[szer*4*i + 4*j]= kolorb; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = kolorg; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = kolorr; // Skladowa RED
        }

    }

    update();

}

void MyWindow::on_verticalSlider_5_valueChanged(int value)
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            hsvtorgb(j*360/szer,(double)value/100,(double)i/wys);
            ptr[szer*4*i + 4*j]= kolorb; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = kolorg; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = kolorr; // Skladowa RED
        }

    }

    update();
}

void MyWindow::on_verticalSlider_6_valueChanged(int value)
{

    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            hsvtorgb(j*360/szer,(double)i/wys,(double)value/100);
            ptr[szer*4*i + 4*j]= kolorb; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = kolorg; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = kolorr; // Skladowa RED
        }

    }

    update();
}

int MyWindow::tryby_kolor(int n, int a, int b)
{
    if(warstwy_tryb[n] == 1) //normal mode
        return b;
    if(warstwy_tryb[n] == 2) //multiply mode
        return (a*b) >> 8;
    if(warstwy_tryb[n] == 3) //screen mode
        return 255 - ((255 - a) * (255 - b) >> 8);
    if(warstwy_tryb[n] == 4) //overlay mode
    {
        if(a < 128)
            return (a * b) >> 7;
        else
            return 255 - ((255 - a) * (255 - b) >> 7);
    }
    if(warstwy_tryb[n] == 5) //darken mode
    {
        if(a < b)
            return a;
        else
            return b;
    }
    if(warstwy_tryb[n] == 6) //lighten mode
    {
        if(a > b)
            return a;
        else
            return b;
    }
    if(warstwy_tryb[n] == 7) //difference mode
        return abs(a - b);
    if(warstwy_tryb[n] == 8) //additive mode
    {
        if((a+b) > 255)
            return 255;
        else return a + b;
    }
    if(warstwy_tryb[n] == 9) //subtractive mode
    {
        if((a+b - 256) < 0)
            return 0;
        else return a + b - 256;
    }
    return 0;
}


void MyWindow::blending()
{
    unsigned char *ptr0, *ptr[6];
    ptr0 = img->bits();
    for(int i = 0; i <= 5; i++)
    {
        ptr[i] = warstwy[i]->bits();
    }
    czysc(img);
    int i,j;
    double a;
    for(int h = 1; h <= 5; h++)
    {
        if(warstwy_czy_aktywna[h])
        {
            a = (double)warstwy_wartosc[h] / 100;

            for(i=0; i<wys; i++)
            {
                for(j=0; j<szer; j++)
                {
                    ptr0[szer*4*i + 4*j    ] = a * tryby_kolor(h, ptr0[szer*4*i + 4*j], ptr[h][szer*4*i + 4*j]) + (1 - a) * ptr0[szer*4*i + 4*j    ]; // Skladowa BLUE
                    ptr0[szer*4*i + 4*j + 1] = a * tryby_kolor(h, ptr0[szer*4*i + 4*j + 1], ptr[h][szer*4*i + 4*j + 1]) + (1 - a) * ptr0[szer*4*i + 4*j + 1]; // Skladowa GREEN
                    ptr0[szer*4*i + 4*j + 2] = a * tryby_kolor(h, ptr0[szer*4*i + 4*j + 2], ptr[h][szer*4*i + 4*j + 2]) + (1 - a) * ptr0[szer*4*i + 4*j + 2]; // Skladowa RED
                }
            }
        }
    }
    update();
}


void MyWindow::on_checkBox_toggled(bool checked)
{
    if(checked)
        warstwy_czy_aktywna[5] = true;
    else
        warstwy_czy_aktywna[5] = false;
    blending();
}

void MyWindow::on_checkBox_2_toggled(bool checked)
{
    if(checked)
        warstwy_czy_aktywna[4] = true;
    else
        warstwy_czy_aktywna[4] = false;
    blending();
}

void MyWindow::on_checkBox_3_toggled(bool checked)
{
    if(checked)
        warstwy_czy_aktywna[3] = true;
    else
        warstwy_czy_aktywna[3] = false;
    blending();
}

void MyWindow::on_checkBox_4_toggled(bool checked)
{
    if(checked)
        warstwy_czy_aktywna[2] = true;
    else
        warstwy_czy_aktywna[2] = false;
    blending();
}

void MyWindow::on_checkBox_5_toggled(bool checked)
{
    if(checked)
        warstwy_czy_aktywna[1] = true;
    else
        warstwy_czy_aktywna[1] = false;
    blending();
}

void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    warstwy_wartosc[5] = value;
    blending();
}

void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    warstwy_wartosc[4] = value;
    blending();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    warstwy_wartosc[3] = value;
    blending();
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    warstwy_wartosc[2] = value;
    blending();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    warstwy_wartosc[1] = value;
    blending();
}



void MyWindow::on_comboBox_Warstwa_5_currentIndexChanged(int index)
{
    warstwy_tryb[5] = index + 1;
    blending();
}

void MyWindow::on_comboBox_Warstwa_6_currentIndexChanged(int index)
{
    warstwy_tryb[4] = index + 1;
    blending();
}

void MyWindow::on_comboBox_Warstwa_7_currentIndexChanged(int index)
{
    warstwy_tryb[3] = index + 1;
    blending();
}

void MyWindow::on_comboBox_Warstwa_8_currentIndexChanged(int index)
{
    warstwy_tryb[2] = index + 1;
    blending();
}

void MyWindow::on_comboBox_Warstwa_9_currentIndexChanged(int index)
{
    warstwy_tryb[1] = index + 1;
    blending();
}
