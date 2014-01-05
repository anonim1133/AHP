#include "oknowynikow.h"
#include "ui_oknowynikow.h"

oknoWynikow::oknoWynikow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::oknoWynikow)
{
	ui->setupUi(this);
}

oknoWynikow::~oknoWynikow()
{
	delete ui;
}

void oknoWynikow::pokazWynik(QString zdjecie, QString nazwa, QString opis){
	zdjecie.prepend("img/");

	qDebug(zdjecie.toAscii());

	QImage myImage;
	myImage.load(zdjecie);

	ui->label_zdjecie->setPixmap(QPixmap::fromImage(myImage));

	ui->label_nazwa->setText(nazwa);

	ui->label_opis->setText(opis);
}
