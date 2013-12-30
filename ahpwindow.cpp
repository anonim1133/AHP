#include "ahpwindow.h"
#include "ui_ahpwindow.h"

AhpWindow::AhpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AhpWindow)
{
    ui->setupUi(this);
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
