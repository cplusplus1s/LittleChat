#include "ChatWindow.h"

ChatWindow::ChatWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_networkMng = GlooxManager::createGlooxMng();
	m_networkMng->registerUiListener(this);

	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
	initUi();
	connect(ui.chatTab, SIGNAL(tabCloseRequested(int)), this, SLOT(onChatDialogClose(int)));
	connect(this, SIGNAL(newMessage(QString, QString)), this, SLOT(addChatDialogWithMsg(QString, QString)));
}

ChatWindow::~ChatWindow()
{
}

void ChatWindow::initUi()
{
	setWindowIcon(QIcon(":/LoginWindow/Resources/logo.ico"));
	setWindowTitle("Chat");
	setFixedSize(this->width(), this->height());
	ui.chatTab->clear();
	ui.chatTab->setTabsClosable(true);
}

void ChatWindow::addChatDialog(const QString& id)
{
	ChatDialog *dialog = new ChatDialog(this);
	dialog->setContactId(id);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	int curIndex = ui.chatTab->addTab(dialog, id);
	ui.chatTab->setCurrentIndex(curIndex);

	QMutexLocker locker(&m_mutex);
	m_chatDialogs[id] = dialog;
}

void ChatWindow::removeChatDialog(const QString& id)
{
	QMutexLocker locker(&m_mutex);

	QString tempId = id;
	QMap<QString, QDialog*>::iterator it;
	it = m_chatDialogs.find(id);
	if (it != m_chatDialogs.end())
	{
		delete it.value();
		m_chatDialogs.erase(it);
	}

	int count = ui.chatTab->count();
	if (0 == count)
	{
		this->hide();
	}

	m_networkMng->eraseMessageSession(tempId.toStdString());
}

int ChatWindow::chatDialogCount() const
{
	return ui.chatTab->count();
}

void ChatWindow::onChatDialogClose(int index)
{
	static_cast<ChatDialog*>(ui.chatTab->widget(index))->close();
	removeChatDialog(static_cast<ChatDialog*>(ui.chatTab->widget(index))->getContactId());
	ui.chatTab->removeTab(index);
}

void ChatWindow::addChatDialogWithMsg(QString id, QString msg)
{
	this->show();
	ChatDialog *dialog = new ChatDialog(this);
	dialog->setContactId(id);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	int curIndex = ui.chatTab->addTab(dialog, id);
	ui.chatTab->setCurrentIndex(curIndex);

	QMutexLocker locker(&m_mutex);
	m_chatDialogs[id] = dialog;

	dialog->outputMessage(msg, id);
}

void ChatWindow::onLogin()
{

}

void ChatWindow::onVCardReceived()
{

}

void ChatWindow::onItemSubscribed()
{

}

void ChatWindow::onItemAdded()
{

}

void ChatWindow::onItemRemoved()
{

}

void ChatWindow::onItemUpdated()
{

}

void ChatWindow::onRosterUpdated()
{

}

void ChatWindow::onRosterPresence()
{

}

void ChatWindow::onMessageReceived(const std::string& msg, const std::string& id)
{
	printf("ChatWindow: onMessageReceived\n");
	QMutexLocker locker(&m_mutex);
	QMap<QString, QDialog*>::const_iterator it;
	it = m_chatDialogs.find(QString::fromStdString(id));
	if (it != m_chatDialogs.end())
	{
		static_cast<ChatDialog*>(it.value())->outputMessage(QString::fromStdString(msg), QString::fromStdString(id));
	}
	else
	{
		emit newMessage(QString::fromStdString(id), QString::fromStdString(msg));
	}
}
