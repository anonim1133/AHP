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
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Otwórz..."));
}
