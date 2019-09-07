#include "LoginPage/LoginWindow.h"
#include "HomePage/HomePage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LoginWindow login;
	login.show();
	return a.exec();

	/*HomePage home;
	LoginWindow login;
	if (login.exec() == QDialog::Accepted)
	{
		home.show();
		return a.exec();
	}
	else
	{
		return 0;
	}*/
}
