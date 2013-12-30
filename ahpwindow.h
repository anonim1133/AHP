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

private:
    Ui::AhpWindow *ui;

    qreal macierz_preferencji[5][5];

	QStringList macierz_wyboru_nazwa;
	qreal macierz_wyboru[5][5][5];


};

#endif // AHPWINDOW_H
