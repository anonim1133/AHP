#include "ahpwindow.h"
#include "ui_ahpwindow.h"

AhpWindow::AhpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AhpWindow)
{
    ui->setupUi(this);
	memset(macierz_preferencji, 1, sizeof macierz_preferencji);
	memset(macierz_kryteriow, 0, sizeof macierz_kryteriow);
}

AhpWindow::~AhpWindow()
{
    delete ui;
}

void AhpWindow::openFile(){
	QStringList file_names = QFileDialog::getOpenFileNames(this, tr("Otwórz..."));

	qint8 i = 0;

	foreach (QString file_name, file_names){
		qint8 j = 0,k = 0;
		QString str;

		QFile file(file_name);
		if (!file.open (QIODevice::ReadOnly))
			QMessageBox::critical(this, "Blad podczas otwierania pliku", "Upewnij sie, czy plik istnieje",
								  QMessageBox::Ok | QMessageBox::Default);
			QTextStream stream( &file );

			str = stream.readLine();
			QStringList wlasciwosci = str.split(";");
			macierz_kryteriow_wlasciwosci[i][0] = wlasciwosci.at(0);
			macierz_kryteriow_wlasciwosci[i][1] = wlasciwosci.at(1);
			macierz_kryteriow_wlasciwosci[i][2] = wlasciwosci.at(2);

			while( !stream.atEnd() ) {
				str = stream.readLine();

				str = str.simplified();
				str.replace( " ", "" );

				QStringList wartosci = str.split(",");

				foreach (QString var, wartosci) {
					macierz_kryteriow[i][j][k] = var.toInt();
					k++;
				}

				j++;
			}
			file.close();
		i++;
	}

}

int *AhpWindow::oblicz(int wynik[]){
	//normalizacja
	//Wyrazy w kolumnie dzielić przez sumę wartości w kolumnie
	qreal c[6][5] = {0};
	qDebug() <<"Obliczam macierz preferencji"<<endl;
	for(short i = 0; i < 5; i++)
		for(short j = 0; j < 5; j++)
			c[0][i] += macierz_preferencji[j][i];
	qDebug() <<"Obliczam macierz preferencji 2/2"<<endl;
	for(short i = 0; i < 5; i++)
		for(short j = 0; j < 5; j++)
			macierz_preferencji[i][j] = macierz_preferencji[i][j]/c[0][j];

	qDebug() <<"Obliczam macierz krtyteriow"<<endl;
	for(short a = 0; a < 5; a++){
		for(short i = 0; i < 5; i++)
			for(short j = 0; j < 5; j++)
				c[a+1][i] += macierz_kryteriow[a][j][i];

		for(short i = 0; i < 5; i++)
			for(short j = 0; j < 5; j++)
				macierz_kryteriow[a][i][j] = macierz_kryteriow[a][i][j]/c[a][j];
	}
	qDebug() <<"Obliczam macierz krtyteriow"<<endl;
	//wektory

	qreal w_p[5] = {0};
	qreal r[5] = {0};
	qreal w_k[5][5];

	memset(w_k, 0, sizeof w_k);

	qDebug() <<"Obliczam wektor pref"<<endl;
	for(short i = 0; i < 5; i++)
		for(short j = 0; j < 5; j++)
			w_p[i] += macierz_preferencji[i][j];

	for(short i = 0; i < 5; i++)
		w_p[i] = w_p[i]/5;

	qDebug() <<"Obliczam wektor kryt"<<endl;
	for(short a = 0; a < 5; a++)
		for(short i = 0; i < 5; i++)
			for(short j = 0; j < 5; j++)
				w_k[a][i] += macierz_kryteriow[a][i][j];

	for(short a = 0; a < 5; a++)
		for(short i = 0; i < 5; i++)
			w_k[a][i] = w_k[a][i]/5;

	//badanie spójności

	bool niespojna = false;
	qreal lambda = 0, ri = 0, ci = 0, cr = 0, prog = 0.15;
	ri = 1.11;

{//badanie spójności dla macierzy preferencji
	lambda = 0; ci = 0; cr = 0;
	for(short j = 0; j<5; j++)
		lambda += c[0][j]*w_p[j];

	ci = (lambda/5)/4;
	cr = ci/ri;

	if(cr>prog){
		niespojna = true;
		qDebug()<<"Macierz preferencji niespojna"<<endl;


		QString blad;
		blad.append("Macierz preferencji niespojna");

		QMessageBox::critical(this, "Macierz niespójna", blad,
							  QMessageBox::Ok | QMessageBox::Default);
		r[0] = -1;
		r[1] = -1;
		r[2] = -1;
		r[3] = -1;
		r[4] = -1;

	}else qDebug() << endl;
}

	if(!niespojna){ //Jeżeli nie jest niespójna
		//badanie spójności dla macierzy kryteriów
		for(short i = 1; i<6; i++){
			lambda = 0; ci = 0; cr = 0;
			for(short j = 0; j<5; j++)
				lambda += c[i][j]*w_k[i-1][j];

			ci = (lambda/5)/4;
			cr = ci/ri;
		if(cr>prog){
				qDebug()<<"Macierz "<<i<<"niespójna"<<endl;


				QString blad;
				blad.append("Macierz ");
				blad.append(QString("%1").arg(i));
				blad.append(" niespójna.");

				QMessageBox::critical(this, "Macierz niespójna", blad,
									  QMessageBox::Ok | QMessageBox::Default);

				niespojna = true;
				break;
			}
		}
	}

	if(!niespojna){ //Jeżeli żadna nie jest niespójna; wszystkie są spójne
		//wyznaczanie najlepszego wariantu
		//musi zwrócić indeks
		qDebug() <<"wyznaczanie najlepszego wariantu"<<endl;
		for(short i = 0; i < 5; i++)
			for(short j = 0; j < 5; j++)
				r[i] += w_p[j] * w_k[j][i];

		qDebug() <<"sortowanie..."<<endl;
		qreal max = 0;
		int poz = 0;
		int wi = 0;
		bool minus = false;

		while(1){
			max = 0;
			poz = 0;

			for(short i = 0; i < 5; i++)
				if(r[i] > max){
					max = r[i];
					poz = i;
				}

			wynik[wi++] = poz;
			r[poz] = -1;

			minus = false;
			for(short i = 0; i < 5; i++)
				if(r[i] > -1) minus = true;

			if(minus == false) break;
		}
		qDebug() <<"... i po"<<endl;

	}else{
		qDebug() <<"Ustawiam wynik na -1"<<endl;
		for(short i=0; i<5; i++)
			wynik[i] = -1;
	}

	qDebug() <<"Zwracam wyniki"<<endl;
	int* p;
	p = wynik;
	return p;
}

void AhpWindow::cena2bateria(int value){
	macierz_preferencji[2][1] = value;
	macierz_preferencji[1][2] = (qreal)1/(qreal)value;
}

void AhpWindow::cena2aparat(int value){
	macierz_preferencji[2][0] = value;
	macierz_preferencji[0][2] = (qreal)1/(qreal)value;
}
void AhpWindow::cena2wyswietlacz(int value){
	macierz_preferencji[2][4] = value;
	macierz_preferencji[4][2] = (qreal)1/(qreal)value;
}
void AhpWindow::cena2rozmiar(int value){
	macierz_preferencji[2][3] = value;
	macierz_preferencji[3][2] = (qreal)1/(qreal)value;
}

void AhpWindow::bateria2aparat(int value){
	macierz_preferencji[1][0] = value;
	macierz_preferencji[0][1] = (qreal)1/(qreal)value;
}
void AhpWindow::bateria2wyswietlacz(int value){
	macierz_preferencji[1][4] = value;
	macierz_preferencji[4][1] = (qreal)1/(qreal)value;
}
void AhpWindow::bateria2rozmiar(int value){
	macierz_preferencji[1][3] = value;
	macierz_preferencji[3][1] = (qreal)1/(qreal)value;
}

void AhpWindow::aparat2wyswietlacz(int value){
	macierz_preferencji[0][4] = value;
	macierz_preferencji[4][0] = (qreal)1/(qreal)value;
}
void AhpWindow::aparat2rozmiar(int value){
	macierz_preferencji[0][3] = value;
	macierz_preferencji[3][0] = (qreal)1/(qreal)value;
}

void AhpWindow::wyswietlacz2rozmiar(int value){
	macierz_preferencji[4][3] = value;
	macierz_preferencji[3][4] = (qreal)1/(qreal)value;
}

void AhpWindow::on_pushButton_clicked()
{

	//wylaczyc przycisk "Oblicz", aż do czasu wczytania nowych danych.
	//wylaczyc slidery na czas dzialania funkcji
	//sprawdzic czy dane sa wczytane

	qDebug() <<"Wejscie"<<endl;

	int wynik[5];
	oblicz(wynik);

	qDebug() <<"wyjscie"<<endl;

	if(wynik[0] == -1 || wynik[1] == -1 || wynik[2] == -1 || wynik[3] == -1 || wynik[4] == -1 ) qDebug() << "onpusz -> Macierz niespojna"<<endl;
	else {
		int w = wynik[0];

		qDebug() << "Wszystko gra, wyświetlam wyniki."<<endl;

		for(short i = 0; i < 5; i++)
			qDebug() <<macierz_kryteriow_wlasciwosci[wynik[i]][0]<<"I: "<<i<<" wynik:"<< wynik[i]<<endl;

		oknoWynikow* okno = new oknoWynikow(this);
		okno->show();
		okno->pokazWynik(macierz_kryteriow_wlasciwosci[w][1], macierz_kryteriow_wlasciwosci[w][0], macierz_kryteriow_wlasciwosci[w][2]);
	}

	qDebug() << "Wyswietlam"<<endl;
	oknoWynikow* okno = new oknoWynikow(this);
	okno->show();

	okno->pokazWynik(macierz_kryteriow_wlasciwosci[1][1], macierz_kryteriow_wlasciwosci[1][0], macierz_kryteriow_wlasciwosci[1][2]);
	qDebug() << "Juz nie"<<endl;
}
