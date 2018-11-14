#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //deklaracja timera
    t = new QTimer(this);
    //polaczenie sygnalu ze slotem
    connect(t, SIGNAL(timeout()),this, SLOT(timer_animation()));

    szer = ui->frame->width();
    wys = ui->frame->height();

    poczX = ui->frame->x();
    poczY = ui->frame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    tmp_img = new QImage(szer,wys,QImage::Format_RGB32);

    //szescian [x,y,z][wierzcholki]
    texture = new QImage(":/tex/texture.jpg");
    resetSzescian();
    geoResetMacierzy();

}


void MainWindow::resetSzescian()
{

    szescian[0][0] = 200;
    szescian[1][0] = 200;
    szescian[2][0] = 0;

    szescian[0][1] = 300;
    szescian[1][1] = 200;
    szescian[2][1] = 0;

    szescian[0][2] = 200;
    szescian[1][2] = 300;
    szescian[2][2] = 0;

    szescian[0][3] = 300;
    szescian[1][3] = 300;
    szescian[2][3] = 0;

    //

    szescian[0][4] = 200;
    szescian[1][4] = 200;
    szescian[2][4] = 60;

    szescian[0][5] = 300;
    szescian[1][5] = 200;
    szescian[2][5] = 60;

    szescian[0][6] = 200;
    szescian[1][6] = 300;
    szescian[2][6] = 60;

    szescian[0][7] = 300;
    szescian[1][7] = 300;
    szescian[2][7] = 60;
}

//funkcja wyznaczająca tablice do teksturowania tzn wyznacza wsp trójkątów
void MainWindow::ustawTr(int pkt0, int pkt1, int pkt2, int pkt3, int wsp_tr0[2][3], int wsp_tr1[2][3])
{
    wsp_tr0[0][0] = szescian[0][pkt0];
    wsp_tr0[1][0] = szescian[1][pkt0];

    wsp_tr0[0][1] = szescian[0][pkt1];
    wsp_tr0[1][1] = szescian[1][pkt1];

    wsp_tr0[0][2] = szescian[0][pkt2];
    wsp_tr0[1][2] = szescian[1][pkt2];

    wsp_tr1[0][0] = szescian[0][pkt1];
    wsp_tr1[1][0] = szescian[1][pkt1];

    wsp_tr1[0][1] = szescian[0][pkt2];
    wsp_tr1[1][1] = szescian[1][pkt2];

    wsp_tr1[0][2] = szescian[0][pkt3];
    wsp_tr1[1][2] = szescian[1][pkt3];
}

void MainWindow::swap(int &l1, int &l2)
{
    int tmp = l1;
    l1 = l2;
    l2 = tmp;
}

void MainWindow::zamalujSciany()
{
    //okreslenie scian z ktorych pkt sie sklada
    int tab_sciany_z[6][8];

    // kierunek sciany w stosunku do obserwatora - obecnie widoczne sciany 1
    //wyznaczenie powierzchni widocznych - algorytm wyznaczenia zwrotu/kierunku ścian (czyli jeżeli widzimy ścianę to ma zwrot w jedną stronę a jeżeli przesłania ją coś innego jest tak jakby z tylu to ma zwrot w drugą strone
    //sciana 0 przod: 0, 1, 2, 3  //1 - widoczna - kierunek zwrotu
    tab_sciany_z[0][0] = 0;
    tab_sciany_z[0][1] = 1;
    tab_sciany_z[0][2] = 3;
    tab_sciany_z[0][3] = 2;
    tab_sciany_z[0][4] = 1; // zwrot danej sciany 1

    //sciana 1 tyl  : 4, 5, 6, 7
    tab_sciany_z[1][0] = 4;
    tab_sciany_z[1][1] = 5;
    tab_sciany_z[1][2] = 7;
    tab_sciany_z[1][3] = 6;
    tab_sciany_z[1][4] = 0;

    //sciana 2 lewa : 0, 4, 2, 6  1
    tab_sciany_z[2][0] = 0;
    tab_sciany_z[2][1] = 4;
    tab_sciany_z[2][2] = 6;
    tab_sciany_z[2][3] = 2;
    tab_sciany_z[2][4] = 0;

    //sciana 3 prawa: 1, 5, 3. 7
    tab_sciany_z[3][0] = 1;
    tab_sciany_z[3][1] = 5;
    tab_sciany_z[3][2] = 7;
    tab_sciany_z[3][3] = 3;
    tab_sciany_z[3][4] = 1;

    //sciana 4 gora : 0, 1, 4, 5  1
    tab_sciany_z[4][0] = 0;
    tab_sciany_z[4][1] = 1;
    tab_sciany_z[4][2] = 5;
    tab_sciany_z[4][3] = 4;
    tab_sciany_z[4][4] = 1;

    //sciana 5 spod : 2, 3, 6, 7
    tab_sciany_z[5][0] = 2;
    tab_sciany_z[5][1] = 3;
    tab_sciany_z[5][2] = 7;
    tab_sciany_z[5][3] = 6;
    tab_sciany_z[5][4] = 0;

//kolory scian zamiast teksturowania
//    tab_sciany_z[0][5] = 255;
//    tab_sciany_z[0][6] = 0;
//    tab_sciany_z[0][7] = 0;
//    tab_sciany_z[1][5] = 0;
//    tab_sciany_z[1][6] = 255;
//    tab_sciany_z[1][7] = 0;
//    tab_sciany_z[2][5] = 0;
//    tab_sciany_z[2][6] = 0;
//    tab_sciany_z[2][7] = 255;
//    tab_sciany_z[3][5] = 255;
//    tab_sciany_z[3][6] = 255;
//    tab_sciany_z[3][7] = 0;
//    tab_sciany_z[4][5] = 255;
//    tab_sciany_z[4][6] = 0;
//    tab_sciany_z[4][7] = 255;
//    tab_sciany_z[5][5] = 0;
//    tab_sciany_z[5][6] = 255;
//    tab_sciany_z[5][7] = 255;


//wyznaczanie scian ktore trzeba zateksturowac
    //metoda wyznaczenia kierunku pkt
    //tablica w ktorej przechowywane sa indeksy scian do zateksturowania
    QVector<int> tab;
    qDebug() << "@@@@@@@@@@@@@@@@@@";
    for(int i = 0; i < 6; i++)
    {
        if(i == ktora_sciana) i++;
        else
        {
            int wynik1;
            //dla obrotu po osi x
            if(ktora_sciana == 4)
            {
                if(szescian[0][tab_sciany_z[i][0]] - szescian[0][tab_sciany_z[i][1]] <= 0 &&
                        szescian[0][tab_sciany_z[i][2]] - szescian[0][tab_sciany_z[i][3]] >= 0 )
                    wynik1 = 1;
                else wynik1 = 0;
            }
            //dla obrotu po osi y
            if(ktora_sciana == 2)
            {
                tab_sciany_z[0][4] = 0;
                tab_sciany_z[1][4] = 1;
                if(szescian[1][tab_sciany_z[i][1]] - szescian[1][tab_sciany_z[i][2]] >= 0 &&
                        szescian[1][tab_sciany_z[i][3]] - szescian[1][tab_sciany_z[i][0]] <= 0 )
                    wynik1 = 1;
                else wynik1 = 0;
            }
            //dla obrotu po osi z
            if(ktora_sciana == 0)
            {
                if (szescian[1][tab_sciany_z[i][1]] - szescian[1][tab_sciany_z[i][2]] >= 0 &&
                        szescian[1][tab_sciany_z[i][3]] - szescian[1][tab_sciany_z[i][0]] <= 0)
                    wynik1 = 1;
                else wynik1 = 0;
            }

    //        if (szescian[1][tab_sciany_z[i][0]] - szescian[1][tab_sciany_z[i][1]] <= 0 &&
    //        szescian[1][tab_sciany_z[i][1]] - szescian[1][tab_sciany_z[i][2]] <= 0 &&
    //        szescian[1][tab_sciany_z[i][2]] - szescian[1][tab_sciany_z[i][3]] >= 0 &&
    //        szescian[1][tab_sciany_z[i][3]] - szescian[1][tab_sciany_z[i][0]] >= 0 )
    //            wynik2 = 1;
    //        else wynik2 = 0;

    //        if (        szescian[2][tab_sciany_z[i][0]] - szescian[2][tab_sciany_z[i][1]] <= 0 &&
    //                szescian[2][tab_sciany_z[i][1]] - szescian[2][tab_sciany_z[i][2]] <= 0 &&
    //                szescian[2][tab_sciany_z[i][2]] - szescian[2][tab_sciany_z[i][3]] >= 0 &&
    //                szescian[2][tab_sciany_z[i][3]] - szescian[2][tab_sciany_z[i][0]] >= 0)
    //            wynik3 = 1;
    //        else wynik3 = 0;

            //qDebug() << "wynik1: " << wynik1 << " wynik2: " << wynik2 << " wynik3: " << wynik3;
            //jezeli kierunek wierzcholkow sciany jest taki sam jak ustalony na poczatku to dodaj ja do teksturowania
            if(tab_sciany_z[i][4] == wynik1)
            {
                qDebug() << "tak, " << i << " wynik1: " << wynik1;
                tab.append(i);
            }

        }
    }
    tab.append(ktora_sciana);


    //teksturowanie
    int wsp_tr0[2][3], wsp_tr1[2][3];
    int n = tab.size();
    if(n > 3) n = 3;
    for(int i = 0; i < n; i++)
    {
        //wyznacza 3 pkt aby zdefiniowac trojkat do teksturowania z scian ktore bedą teksturowane
        ustawTr(tab_sciany_z[tab[i]][0], tab_sciany_z[tab[i]][1], tab_sciany_z[tab[i]][3], tab_sciany_z[tab[i]][2], wsp_tr0, wsp_tr1);
//        teksturowanie(wsp_tr0, tab_sciany_z[tab[i]][5], tab_sciany_z[tab[i]][6], tab_sciany_z[tab[i]][7]);
//        teksturowanie(wsp_tr1, tab_sciany_z[tab[i]][5], tab_sciany_z[tab[i]][6], tab_sciany_z[tab[i]][7]);
        teksturowanie2(wsp_tr0, 0);
        teksturowanie2(wsp_tr1, 1);
    }




}

void MainWindow::teksturowanie2(int wsp_Tr[2][3], int ktory)
{
    double u, v, w;
    unsigned char *ptr1, *ptr2;
    ptr1 = img->bits();
    ptr2 = texture->bits();

    int tAx, tAy, tBx, tBy, tCx, tCy, Ax, Ay, Bx, By, Cx, Cy;

    tAx = wsp_Tr[0][0]; tAy = wsp_Tr[1][0];
    tBx = wsp_Tr[0][1]; tBy = wsp_Tr[1][1];
    tCx = wsp_Tr[0][2]; tCy = wsp_Tr[1][2];

    if(ktory == 0)
    {
        Ax = 0;            Ay = 0;
        Bx = tex_szer;     By = 0;
        Cx = 0;            Cy = tex_wys;
    }
    else
    {
        Ax = tex_szer;      Ay = 0;
        Bx = 0;             By = tex_wys;
        Cx = tex_szer;      Cy = tex_wys;
    }


    for(int i = 0; i < wys; i++)
    {
        for(int j = 0; j < szer; j++)
        {
            //wyliczanie wsp barycentrycznych - sprawdzanie czy pkt i,j należy do obszaru teksturowania
            v = (((double)j - tAx)*(tCy - tAy) - ((double)i - tAy)*(tCx - tAx)) / ((tBx - tAx)*(tCy - tAy) - (tBy - tAy)*(tCx - tAx));
            w = ((tBx - tAx)*((double)i - tAy) - (tBy - tAy)*((double)j - tAx)) / ((tBx - tAx)*(tCy - tAy) - (tBy - tAy)*(tCx - tAx));
            u = 1 - v - w;
            //sprawdzenie czy sprawdzany pkt nalezy do obszaru teksturowania
            if(v < 0 || v > 1 || w < 0 || w > 1 || u < 0 || u > 1)
            {

            }
            else
            {

                //wyliczenie miejsca docelowego dla koloru tekstury
                double y1 = u * (double)Ax + v * (double)Bx + w * (double)Cx;
                double x1 = u * (double)Ay + v * (double)By + w * (double)Cy;

                //interpolacja dwuliniowa
                int n1, n2, n3, n4;
                n1 = tex_szer*4*(int)(x1) + 4*(int)(y1);
                n2 = tex_szer*4*(int)(x1+1) + 4*(int)(y1+1);
                n4 = tex_szer*4*(int)(x1) + 4*(int)(y1+1);
                n3 = tex_szer*4*(int)(x1+1) + 4*(int)(y1);

                double a = x1 - (int)x1;
                double b = y1 - (int)y1;

                int kolor_b = b * ((1 - a) * ptr2[n1    ] + a * ptr2[n2    ]) + (1 - b) * ((1 - a) * ptr2[n4    ] + a * ptr2[n3    ]);
                int kolor_g = b * ((1 - a) * ptr2[n1 + 1] + a * ptr2[n2 + 1]) + (1 - b) * ((1 - a) * ptr2[n4 + 1] + a * ptr2[n3 + 1]);
                int kolor_r = b * ((1 - a) * ptr2[n1 + 2] + a * ptr2[n2 + 2]) + (1 - b) * ((1 - a) * ptr2[n4 + 2] + a * ptr2[n3 + 2]);

                ptr1[szer*4*i  + 4*j    ] = kolor_b; // Skladowa BLUE
                ptr1[szer*4*i  + 4*j + 1] = kolor_g; // Skladowa GREEN
                ptr1[szer*4*i  + 4*j + 2] = kolor_r; // Skladowa RED

            }
        }
    }

}


//teksturowanie jednolitym kolorem
void MainWindow::teksturowanie(int wsp_tTr[2][3], int r, int g, int b)
{
    double u, v, w;
    unsigned char *ptr1;
    ptr1 = img->bits();

    int tAx, tAy, tBx, tBy, tCx, tCy;



    tAx = wsp_tTr[0][0]; tAy = wsp_tTr[1][0];
    tBx = wsp_tTr[0][1]; tBy = wsp_tTr[1][1];
    tCx = wsp_tTr[0][2]; tCy = wsp_tTr[1][2];

    for(int i = 0; i < wys; i++)
    {
        for(int j = 0; j < szer; j++)
        {
            v = (((double)j - tAx)*(tCy - tAy) - ((double)i - tAy)*(tCx - tAx)) / ((tBx - tAx)*(tCy - tAy) - (tBy - tAy)*(tCx - tAx));
            w = ((tBx - tAx)*((double)i - tAy) - (tBy - tAy)*((double)j - tAx)) / ((tBx - tAx)*(tCy - tAy) - (tBy - tAy)*(tCx - tAx));
            u = 1 - v - w;
            //qDebug() << v << " " << w << " " << u;
            if(v < 0 || v > 1 || w < 0 || w > 1 || u < 0 || u > 1)
            {

            }
            else
            {
                ptr1[szer*4*i  + 4*j    ] = b; // Skladowa BLUE
                ptr1[szer*4*i  + 4*j + 1] = g; // Skladowa GREEN
                ptr1[szer*4*i  + 4*j + 2] = r; // Skladowa RED
            }
        }
    }

    update();
}

// Funkcja "odmalowujaca" komponent
void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX, poczY, *img);

}

void MainWindow::czysc(QImage *img)
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
            ptr[szer*4*i + 4*j    ] = 0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
    update();
}

void MainWindow::przepiszObraz(QImage *img1, QImage *img2)
{
    unsigned char *ptr1, *ptr2;
    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr1 = img1->bits();
    ptr2 = img2->bits();
    int i,j;
    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr2[szer*4*i + 4*j    ] = ptr1[szer*4*i + 4*j    ]; // Skladowa BLUE
            ptr2[szer*4*i + 4*j + 1] = ptr1[szer*4*i + 4*j + 1]; // Skladowa GREEN
            ptr2[szer*4*i + 4*j + 2] = ptr1[szer*4*i + 4*j + 2]; // Skladowa RED
        }
    }
}

void MainWindow::zapalPiksel(unsigned char *ptr, int x, int y)
{
    if(szer - x > 0 && szer + x >= szer && wys - y > 0 && wys + y >= wys)
    {
        ptr[szer*4*y + 4*x] = 255; // Skladowa BLUE
        ptr[szer*4*y + 4*x + 1] = 255; // Skladowa GREEN
        ptr[szer*4*y + 4*x + 2] = 255; // Skladowa RED
    }
}

void MainWindow::rysujLinie(int n1, int n2, QImage *img)
{
    double x0 = szescian[0][n1];
    double y0 = szescian[1][n1];

    double x1 = szescian[0][n2];
    double y1 = szescian[1][n2];

    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;
    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();
    double y, z, a, b;
    if((x1 - x0) > 0) // rysowana linia od lewej do prawej
    {
        a = (y1-y0)/(x1-x0);
        b = y1 - a*x1;
        for(double x = x0; x < x1; ++x)
        {
            y = a*x + b;
            z = a*(x+1) + b; //obliczanie funkcji w przód aby sprawdzić czy nie ma za dużego przeskoku aby wypełnić pustą przestrzeń
            //zapalPiksel(ptr, x, y);
            //if((y - z) >= 0)
            for(int k = (int)floor(z+0.5); k <= (int)floor(y + 0.5) ; ++k)
                zapalPiksel(ptr, x, k);

            for(int k = (int)floor(y+0.5); k <= (int)floor(z + 0.5) ; ++k)
                zapalPiksel(ptr, x, k);

        }
    }
    else if((x1 - x0) < 0) //rysowana linia od prawej do lewej
    {
        a = (y0-y1)/(x0-x1);
        b = y0 - a*x0;
        for(int x = x1; x < x0; ++x)
        {
            y = a*x + b;
            z = a*(x+1) + b;
            //czy rysowana od gory do dołu lub na odwrót - poprawa dokladnosci przy duzych katach

            for(int k = (int)floor(z+0.5); k <= (int)floor(y + 0.5); ++k)
                zapalPiksel(ptr, x, k);

            for(int k = (int)floor(y+0.5); k <= (int)floor(z + 0.5); ++k)
                zapalPiksel(ptr, x, k);
        }
    }
    else //dla odcinkow pionowych
    {
        // czy od gory do dolu
        for(int y=y0; y <= y1; ++y)
            zapalPiksel(ptr, (int)floor(x0+0.5), y);
        for(int y=y0; y >= y1; --y)
            zapalPiksel(ptr, (int)floor(x0+0.5), y);
    }
    update();
}

void MainWindow::rysujSzescian()
{
    czysc(img);



    for(int i = 0; i < 8; i++)
    {
        przeksztalcWspNa2D(i);
    }

//    for(int i = 0; i < 8; i++)
//    {
//        for(int j = 0; j < 8; j++)
//        {
//            rysujLinie(szescian[0][i], szescian[1][i], szescian[1][j], szescian[1][j], img);
//        }
//    }
    //0:


    if(ui->checkBox_2->isChecked())
    {
        rysujLinie(0, 1, img); rysujLinie(0, 2, img); rysujLinie(0, 4, img);
        //1:
        rysujLinie(1, 3, img); rysujLinie(1, 5, img);
        //2:
        rysujLinie(2, 3, img); rysujLinie(2, 6, img);
        //3:
        rysujLinie(3, 7, img);

        //4:
        rysujLinie(4, 5, img); rysujLinie(4, 6, img);
        //5:
        rysujLinie(5, 7, img);
        //6:
        rysujLinie(6, 7, img);
        //7:
    }


    if (ui->checkBox->isChecked())
        zamalujSciany();

    update();
}


//funkcja przeliczajaca wspolrzedne z 3d na 2d
void MainWindow::przeksztalcWspNa2D(int n)
{
    double d = 200; //mozna tym wspolczynnikiem dowolnie manipulowac - odleglosc obserwatora od sceny
    double wspolczynnik = 1 + ((double)szescian[2][n] / d);
    //qDebug() << n << ": " << wspolczynnik;
    szescian[0][n] = szescian[0][n] / wspolczynnik;
    szescian[1][n] = szescian[1][n] / wspolczynnik;
}

void MainWindow::geoResetMacierzy()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            obrotTab[i][j] = 0;
            pochylenieTab[i][j] = 0;
            skalowanieTab[i][j] = 0;
            przesuniecieTab[i][j] = 0;
        }
        obrotTab[i][i] = 1;
        pochylenieTab[i][i] = 1;
        skalowanieTab[i][i] = 1;
        przesuniecieTab[i][i] = 1;
    }
}

void MainWindow::mnozenieMacierzy(double A[4][4], double W[4][4])
{
    double s;
    double C[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            s = 0;
            for(int k = 0; k < 4; k++) s += A[k][j] * W[i][k];
            C[i][j] = s;
        }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            W[i][j] = C[i][j];
    }
}

//funkcja rysujaca szescian ktora wylicza z macierzy wierzcholki a nastepnie wywoluje fk rysujszescain
void MainWindow::przeksztalcWspSzesciana()
{
    resetSzescian();

    //macierz 4x4 bo wykorzystujemy wsp jednorodne
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            wynikowaTab[i][j] = 0;
        wynikowaTab[i][i] = 1;
    }


    mnozenieMacierzy(przesuniecieTab, wynikowaTab);
    mnozenieMacierzy(obrotTab, wynikowaTab);
    mnozenieMacierzy(pochylenieTab, wynikowaTab);
    mnozenieMacierzy(skalowanieTab, wynikowaTab);

//    for(int i = 0; i < 4; i++){
//        for(int j = 0; j < 4; j++)
//            qDebug() << wynikowaTab[i][j];
//        qDebug() << " ";
//    }


    //przesuniecie calego obrazka aby przekszlcenia wykonywa względem punktu 0,0,0
    int przesuniecie_i = 250 - przesuniecieTab[0][3];
    int przesuniecie_j = 250 - przesuniecieTab[1][3];
    int przesuniecie_k = 30 - przesuniecieTab[2][3];


    //int przesuniecie_k = 0;

    int przzz = 250;
    int przzzz = 30;
    for(int i = 0; i < 8; i++)
    {
         double x1 = (szescian[0][i] - przesuniecie_i)*wynikowaTab[0][0] + (szescian[1][i] - przesuniecie_j)*wynikowaTab[0][1] + (szescian[2][i] - przesuniecie_k)*wynikowaTab[0][2] + przzz;
         double y1 = (szescian[0][i] - przesuniecie_i)*wynikowaTab[1][0] + (szescian[1][i] - przesuniecie_j)*wynikowaTab[1][1] + (szescian[2][i] - przesuniecie_k)*wynikowaTab[1][2] + przzz;
         double z1 = (szescian[0][i] - przesuniecie_i)*wynikowaTab[2][0] + (szescian[1][i] - przesuniecie_j)*wynikowaTab[2][1] + (szescian[2][i] - przesuniecie_k)*wynikowaTab[2][2] + przzzz;

//         qDebug() << "x = " << x1;
//         qDebug() << "y = " << y1;
         //qDebug() << "z = " << z1;

         int x = (int)floor(0.5 + x1);
         int y = (int)floor(0.5 + y1);
         int z = (int)floor(0.5 + z1);

         szescian[0][i] = x;
         szescian[1][i] = y;
         szescian[2][i] = z;
    }
    rysujSzescian();
}




MainWindow::~MainWindow()
{
    //mThread->exit(0);
    delete ui;
}

void MainWindow::on_skal_Slider_valueChanged(int value)
{

    skalowanieTab[0][0] = (double)value / 100;
    skalowanieTab[0][0] = 1 / skalowanieTab[0][0];
    skalowanieTab[1][1] = skalowanieTab[0][0];
    skalowanieTab[2][2] = skalowanieTab[0][0];
    //qDebug() << mThread->skalowanieTab[0][0];
    przeksztalcWspSzesciana();
}



void MainWindow::on_obrotX_Slider_valueChanged(int value)
{
    ktora_sciana = 2;
    double kat_radian = (value * M_PI) / 180;
    obrotTab[1][1] =  qCos(kat_radian);
    obrotTab[1][2] = -qSin(kat_radian);
    obrotTab[2][1] = qSin(kat_radian);
    obrotTab[2][2] = qCos(kat_radian);
    przeksztalcWspSzesciana();
}

void MainWindow::on_obrotY_Slider_valueChanged(int value)
{
    ktora_sciana = 4;
    double kat_radian = (value * M_PI) / 180;
    obrotTab[0][0] = qCos(kat_radian);
    obrotTab[0][2] = qSin(kat_radian);
    obrotTab[2][0] = -qSin(kat_radian);
    obrotTab[2][2] = qCos(kat_radian);
    przeksztalcWspSzesciana();
}

void MainWindow::on_obrotZ_Slider_valueChanged(int value)
{
    ktora_sciana = 0;
    double kat_radian = (value * M_PI) / 180;
    obrotTab[0][0] = qCos(kat_radian);
    obrotTab[0][1] = -qSin(kat_radian);
    obrotTab[1][0] = qSin(kat_radian);
    obrotTab[1][1] = qCos(kat_radian);
    przeksztalcWspSzesciana();
}

void MainWindow::on_przesunX_Slider_valueChanged(int value)
{
    przesuniecieTab[0][3] = -value;
    przeksztalcWspSzesciana();
}

void MainWindow::on_przesunY_Slider_valueChanged(int value)
{
    przesuniecieTab[1][3] = -value;
    przeksztalcWspSzesciana();
}

void MainWindow::on_przesunZ_Slider_valueChanged(int value)
{
    przesuniecieTab[2][3] = -value;
    przeksztalcWspSzesciana();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->obrotX_Slider->setValue(0);
    ui->obrotY_Slider->setValue(0);
    ui->obrotZ_Slider->setValue(0);

    ui->pochylX_Slider->setValue(0);
    ui->pochylY_Slider->setValue(0);
    ui->pochylZ_Slider->setValue(0);

    ui->przesunX_Slider->setValue(0);
    ui->przesunY_Slider->setValue(0);
    ui->przesunZ_Slider->setValue(0);

    ui->skal_Slider->setValue(100);
    ktora_sciana = 4;
    kat = 0;
    geoResetMacierzy();
    resetSzescian();
    rysujSzescian();
}

void MainWindow::on_pochylX_Slider_valueChanged(int value)
{
    pochylenieTab[0][2] = (double)value / 100;
    przeksztalcWspSzesciana();
}

void MainWindow::on_pochylY_Slider_valueChanged(int value)
{
    pochylenieTab[1][2] = (double)value / 100;
    przeksztalcWspSzesciana();
}

void MainWindow::on_pochylZ_Slider_valueChanged(int value)
{
    pochylenieTab[2][1] = (double)value / 100;
    przeksztalcWspSzesciana();
}

void MainWindow::on_pushButton_clicked()
{
    //started w milisekunadch
    t->start(50);
}

void MainWindow::on_pushButton_3_clicked()
{
    //stopped
    t->stop();
}

void MainWindow::timer_animation()
{
    if(kat < 360)
    {
        kat++;
    }
    else
    {
        kat = 0;
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            obrotTab[i][j] = 0;
        obrotTab[i][i] = 1;
    }
    if(ui->radioButton_Y->isChecked())
    {
        ktora_sciana = 4;
        double kat_radian = (kat * M_PI) / 180;
        obrotTab[0][0] = qCos(kat_radian);
        obrotTab[0][2] = qSin(kat_radian);
        obrotTab[2][0] = -qSin(kat_radian);
        obrotTab[2][2] = qCos(kat_radian);
    }
    else
    {
        ktora_sciana = 2;
        double kat_radian = (kat * M_PI) / 180;
        obrotTab[1][1] =  qCos(kat_radian);
        obrotTab[1][2] = -qSin(kat_radian);
        obrotTab[2][1] = qSin(kat_radian);
        obrotTab[2][2] = qCos(kat_radian);
    }
    przeksztalcWspSzesciana();
}

