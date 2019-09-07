#pragma once

#include <QDialog>
#include "ui_AddFriendDialog.h"
#include "HomePage.h"

class AddFriendDialog : public QDialog
{
	Q_OBJECT

public:
	AddFriendDialog(QWidget *parent = Q_NULLPTR);
	~AddFriendDialog();

public slots:
	void on_addButton_clicked();
	void on_cancelButton_clicked();

private:
	Ui::AddFriendDialog ui;
};
