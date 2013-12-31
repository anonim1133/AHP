#ifndef AHPWINDOW_H
#define AHPWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class AhpWindow;
}

class AhpWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit AhpWindow(QWidget *parent = 0);
    ~AhpWindow();

public slots:
	void openFile();

	qint8 oblicz();

	void cena2bateria(int value);
	void cena2aparat(int value);
	void cena2wyswietlacz(int value);
	void cena2rozmiar(int value);

	void bateria2aparat(int value);
	void bateria2wyswietlacz(int value);
	void bateria2rozmiar(int value);

	void aparat2wyswietlacz(int value);
	void aparat2rozmiar(int value);

	void wyswietlacz2rozmiar(int value);

private:
    Ui::AhpWindow *ui;

	qreal macierz_preferencji[5][5];

	QString macierz_kryteriow_wlasciwosci[5][3];
	qreal macierz_kryteriow[5][5][5];


};

#endif // AHPWINDOW_H
