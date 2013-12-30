#include "ahpwindow.h"
#include "ui_ahpwindow.h"

AhpWindow::AhpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AhpWindow)
{
    ui->setupUi(this);
	memset(macierz_preferencji, 0, sizeof macierz_preferencji);
	memset(macierz_wyboru, 0, sizeof macierz_wyboru);
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

			macierz_wyboru_nazwa.append(stream.readLine());

			while( !stream.atEnd() ) {
				str = stream.readLine();

				str = str.simplified();
				str.replace( " ", "" );

				QStringList wartosci = str.split(",");

				foreach (QString var, wartosci) {
					macierz_wyboru[i][j][k] = var.toInt();
					k++;
				}

				j++;
			}
			file.close();
		i++;
	}

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