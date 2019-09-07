#include "AddFriendDialog.h"

AddFriendDialog::AddFriendDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle("AddFriend");
	QPixmap pixmap = QPixmap(":/LoginWindow/Resources/addcontact_background.jpg").scaled(this->size());
	QPalette mainpalette(this->palette());
	mainpalette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(mainpalette);
}

AddFriendDialog::~AddFriendDialog()
{
}

void AddFriendDialog::on_addButton_clicked()
{
	if (NULL == ui.contactIdEdit->text())
	{
		QDialog::reject();
	}
	else
	{
		static_cast<HomePage*>(this->parent())->addContact(ui.contactIdEdit->text());
		QDialog::accept();
	}
}

void AddFriendDialog::on_cancelButton_clicked()
{
	QDialog::reject();
}
