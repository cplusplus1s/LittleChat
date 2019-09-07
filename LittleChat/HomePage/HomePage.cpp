#include "HomePage.h"
#include "ContactWidget.h"
#include "AccountInfo.h"

HomePage::HomePage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_networkMng = GlooxManager::createGlooxMng();
	m_networkMng->registerUiListener(this);
	m_chatWindow = new ChatWindow();

	connect(this, SIGNAL(contactListRefresh()), this, SLOT(onContactListRefresh()));

	initUi();
}

HomePage::~HomePage()
{
}

void HomePage::closeEvent(QCloseEvent *event)
{
	emit homepageQuit();
	m_chatWindow->close();
	QWidget::closeEvent(event);
}

void HomePage::initUi()
{
	setWindowIcon(QIcon(":/LoginWindow/Resources/logo.ico"));
	setWindowTitle("Chat");
	setFixedSize(this->width(), this->height());
	QPixmap pixmap = QPixmap(":/LoginWindow/Resources/homepage_background.jpg").scaled(this->size());
	QPalette mainpalette(this->palette());
	mainpalette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette(mainpalette);

	m_treeWidget = new QTreeWidget(ui.contactTab);
	m_treeWidget->setGeometry(ui.contactTab->rect());
	m_treeWidget->setHeaderHidden(true);

	connect(m_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(createMucDialog(QTreeWidgetItem*, int)));
	/*m_treeWidget = new QTreeWidget(ui.contactTab);
	m_treeWidget->setGeometry(ui.contactTab->rect());
	m_treeWidget->setHeaderHidden(true);

	QTreeWidgetItem *group = new QTreeWidgetItem(m_treeWidget);
	group->setText(0, "Friends");*/

	//refreshContactsList();

	/*QTreeWidgetItem *contact1 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget1 = new ContactWidget();
	contactWidget1->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact1, 0, contactWidget1);
	QTreeWidgetItem *contact2 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget2 = new ContactWidget();
	contactWidget2->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact2, 0, contactWidget2);

	QTreeWidgetItem *contact3 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget3 = new ContactWidget();
	contactWidget3->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact3, 0, contactWidget3);

	QTreeWidgetItem *contact4 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget4 = new ContactWidget();
	contactWidget4->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact4, 0, contactWidget4);

	QTreeWidgetItem *contact5 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget5 = new ContactWidget();
	contactWidget5->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact5, 0, contactWidget5);

	QTreeWidgetItem *contact6 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget6 = new ContactWidget();
	contactWidget6->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact6, 0, contactWidget6);

	QTreeWidgetItem *contact7 = new QTreeWidgetItem(group);
	ContactWidget *contactWidget7 = new ContactWidget();
	contactWidget7->setFixedSize(350, 100);
	m_treeWidget->setItemWidget(contact7, 0, contactWidget7);*/
}

void HomePage::onContactListRefresh()
{
	//如果在构造函数中创建了Qt控件，不用写show()函数就能显示，而在构造函数以外动态创建Qt控件记得加上show()
	m_treeWidget->clear();

	const AccountInfo::GroupsMap &gMap = m_networkMng->getGoupsMap();
	AccountInfo::GroupsMap::const_iterator git;
	for (git = gMap.begin(); git != gMap.end(); git++)
	{
		QTreeWidgetItem *group = new QTreeWidgetItem(m_treeWidget);
		group->setText(0, QString::fromStdString(git->first));
		std::list<AccountInfo::ContactInfo*>::const_iterator cit;
		for (cit = git->second.begin(); cit != git->second.end(); cit++)
		{
			QTreeWidgetItem *contact = new QTreeWidgetItem(group);
			ContactWidget *contactWidget = new ContactWidget();
			contactWidget->setFixedSize(350, 100);
			contactWidget->setName(QString::fromStdString((*cit)->getId()));
			contactWidget->setOnlineState(0 == (*cit)->getPresence());
			contactWidget->setId(QString::fromStdString((*cit)->getId()));
			//contactWidget->installEventFilter(this);
			m_treeWidget->setItemWidget(contact, 0, contactWidget);
		}
	}

	m_treeWidget->expandAll();
	m_treeWidget->show();
}

void HomePage::createMucDialog(QTreeWidgetItem *item, int column)
{
	if (m_chatWindow->isHidden())
	{
		m_chatWindow->show();
	}
	ContactWidget* contactWidget = static_cast<ContactWidget*>(m_treeWidget->itemWidget(item, column));
	m_chatWindow->addChatDialog(contactWidget->getId());
}

void HomePage::addContact(QString shortId)
{
	//printf("addContact %s\n",contactId.toStdString().c_str());
	m_networkMng->subscribe(shortId.toStdString() + JID_TAIL);
}

void HomePage::onLogin()
{
	ui.nameLabel->setText(QString::fromStdString(m_networkMng->getId()));
	
	//VCard功能正常后移动到onVCardReceive()中
	QImage *img = new QImage();
	img->load(":/LoginWindow/Resources/profile.png");
	//*img = img->scaled(ui.profileLabel->width(), ui.profileLabel->height());
	ui.profileLabel->setPixmap(QPixmap::fromImage(*img));
}

void HomePage::onVCardReceived()
{
	ui.nameLabel->setText(QString::fromStdString(m_networkMng->getId()));
}

void HomePage::onItemSubscribed()
{

}

void HomePage::onItemAdded()
{

}

void HomePage::onItemRemoved()
{

}

void HomePage::onItemUpdated()
{
	emit contactListRefresh();
}

void HomePage::onRosterUpdated()
{
	emit contactListRefresh();
}

void HomePage::onRosterPresence()
{
	emit contactListRefresh();
}

void HomePage::onSubscriptionRequest(const std::string& id)
{

}

void HomePage::onMessageReceived(const std::string& msg, const std::string& id)
{

}

void HomePage::on_addButton_clicked()
{
	AddFriendDialog dialog(this);
	dialog.exec();
}
