#include "LoginWindow.h"
#include "LoginInterface.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_curIndex = -1;
	m_databaseMng = LoginInfoManager::CreateLoginInfoManager();
	m_networkMng = GlooxManager::createGlooxMng();
	m_networkMng->registerUiListener(this);

	InitUi();

	m_homePage = new HomePage();
	m_homePage->setAttribute(Qt::WA_DeleteOnClose);
	connect(m_homePage, SIGNAL(homepageQuit()), this, SLOT(close()));

	connect(this, SIGNAL(switchToHomePage()), this, SLOT(onSwitchToHomePage()));

	if (SyncDatabase())
	{
		LoadComboBox();
		m_curIndex = 0;
		ui.usernameComboBox->setCurrentIndex(m_curIndex);

		if (m_loginInfoList.at(m_curIndex)->GetAutologin())
		{
			on_loginPushButton_clicked();
		}
	}

}

bool LoginWindow::SyncDatabase()
{
	if (m_databaseMng->ReadUsers(m_loginInfoList))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LoginWindow::UpdateDatabase()
{
	LoginInfoManager::UserLoginInfo userInfo;
	userInfo.SetUsername(ui.usernameComboBox->currentText());
	userInfo.SetPassword(ui.pwLineEdit->text());
	userInfo.SetAutologin(ui.autologinCheckBox->isChecked());
	userInfo.SetRememberpw(ui.rememberCheckBox->isChecked());
	m_databaseMng->WriteUser(userInfo);
}

void LoginWindow::RefreshCurUserInfo()
{
	InitUi();

	if (m_loginInfoList.at(m_curIndex)->GetRememberpw())
	{
		ui.rememberCheckBox->setChecked(true);
		ui.pwLineEdit->setText((m_loginInfoList.at(m_curIndex))->GetPassword());

		if (m_loginInfoList.at(m_curIndex)->GetAutologin())
		{
			ui.autologinCheckBox->setChecked(true);
		}
		else
		{
			ui.autologinCheckBox->setChecked(false);
		}
	}
	else
	{
		ui.rememberCheckBox->setChecked(false);
		ui.autologinCheckBox->setChecked(false);
	}
}

void LoginWindow::InitUi()
{
	setWindowIcon(QIcon(":/LoginWindow/Resources/logo.ico"));
	setWindowTitle("Chat");
	setFixedSize(this->width(),this->height());
	QPixmap pixmap = QPixmap(":/LoginWindow/Resources/main_background.jpg").scaled(this->size());
	QPalette mainpalette(this->palette());
	mainpalette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(mainpalette);

	QPalette palette;
	palette.setColor(QPalette::WindowText, Qt::white);
	ui.autologinCheckBox->setPalette(palette);
	ui.rememberCheckBox->setPalette(palette);

	ui.pwLineEdit->clear();
	ui.autologinCheckBox->setChecked(false);
	ui.rememberCheckBox->setChecked(false);
	ui.pwLineEdit->setEchoMode(QLineEdit::Password);
	ui.usernameComboBox->setEditable(true);
}

void LoginWindow::LoadComboBox()
{
	ui.usernameComboBox->clear();
	QList<LoginInfoManager::UserLoginInfo*>::iterator it;
	for (it = m_loginInfoList.begin(); it != m_loginInfoList.end(); ++it)
	{
		ui.usernameComboBox->addItem((*it)->GetUsername());
	}
}

void LoginWindow::on_usernameComboBox_currentIndexChanged(int index)
{
	m_curIndex = index;
	if (-1 != m_curIndex)
	{
		RefreshCurUserInfo();
	}
}

void LoginWindow::on_usernameComboBox_editTextChanged(const QString &text)
{
	ui.pwLineEdit->clear();
	ui.autologinCheckBox->setChecked(false);
	ui.rememberCheckBox->setChecked(false);
}

void LoginWindow::on_autologinCheckBox_stateChanged(int state)
{
	if (Qt::Checked == state)
	{
		ui.rememberCheckBox->setCheckState(Qt::Checked);
	}
}

void LoginWindow::on_rememberCheckBox_stateChanged(int state)
{
	if (Qt::Unchecked == state)
	{
		ui.autologinCheckBox->setCheckState(Qt::Unchecked);
	}
}

void LoginWindow::on_loginPushButton_clicked()
{
	QString username = ui.usernameComboBox->currentText();
	QString password = ui.pwLineEdit->text();

	if (username.isEmpty())
	{
		QMessageBox msg;
		msg.setText("Username cannot be empty!");
		msg.exec();
		return;
	}
	else if (password.isEmpty())
	{
		QMessageBox msg;
		msg.setText("Please input password!");
		msg.exec();
		return;
	}
	else
	{
		/*if (LoginInterface::login(username.toStdString(), password.toStdString()))
		{
			UpdateDatabase();
			QMessageBox msg;
			msg.setText("Succeed to login!");
			msg.exec();
			SyncDatabase();
			LoadComboBox();
			return;
		}
		else
		{
			QMessageBox msg;
			msg.setText("Invalid username or password!");
			msg.exec();
			return;
		}*/
		m_networkMng->login(username.toStdString(), password.toStdString());
	}
}

void LoginWindow::onSwitchToHomePage()
{
	m_homePage->show();
	this->hide();
}

void LoginWindow::onLogin()
{
	if (!isHidden())
	{
		UpdateDatabase();
		SyncDatabase();
		LoadComboBox();
		//这里不可以直接m_homePage->show()或this->hide()
		//否则会报错Cannot send events to objects owned by a different thread，Qt不允许这样做
		//更不可以在这里m_homePage = new HomePage()
		//否则会报错Widgets must be created in the GUI thread
		//也是Qt的限制
		//所以此处使用Qt的信号机制，可以方便地跨线程
		emit(switchToHomePage());
	}
}

void LoginWindow::onVCardReceived()
{

}

void LoginWindow::onItemSubscribed()
{

}

void LoginWindow::onItemAdded()
{

}

void LoginWindow::onItemRemoved()
{

}

void LoginWindow::onItemUpdated()
{

}

void LoginWindow::onRosterUpdated()
{
	
}

void LoginWindow::onRosterPresence()
{

}

void LoginWindow::onSubscriptionRequest(const std::string& id)
{

}

void LoginWindow::onMessageReceived(const std::string& msg, const std::string& id)
{

}
