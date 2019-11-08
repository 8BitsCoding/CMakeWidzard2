#include "CMakeWidzard2.h"
#include <QtWidgets/QApplication>

// git test2

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMakeWidzard2 w;
	w.show();
	return a.exec();
}
