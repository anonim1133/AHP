#ifndef AHPWINDOW_H
#define AHPWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

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
};

#endif // AHPWINDOW_H
