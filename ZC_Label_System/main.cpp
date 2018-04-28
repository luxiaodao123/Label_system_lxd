#include "ZC_Label_System.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ZC_Label_System w;
	w.show();
	return a.exec();
}
