#include "ahpwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AhpWindow w;
	w.show();
	return a.exec();
}
