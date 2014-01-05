#ifndef OKNOWYNIKOW_H
#define OKNOWYNIKOW_H

#include <QMainWindow>

namespace Ui {
	class oknoWynikow;
}

class oknoWynikow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit oknoWynikow(QWidget *parent = 0);
		void pokazWynik(QString zdjecie, QString nazwa, QString opis);
		~oknoWynikow();

	private:
		Ui::oknoWynikow *ui;
};

#endif // OKNOWYNIKOW_H
