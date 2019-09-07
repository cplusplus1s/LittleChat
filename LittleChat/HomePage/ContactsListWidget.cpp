#include "ContactsListWidget.h"

#include <QAction>
#include <QMouseEvent>

ContactsListWidget::ContactsListWidget(QListWidget *parent)
	: QListWidget(parent)
{
	setFocusPolicy(Qt::NoFocus);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	initUi();
}

ContactsListWidget::~ContactsListWidget()
{
	delete m_blankMenu;
	delete m_contactMenu;
	delete m_groupMenu;
	delete m_groupNameEdit;
}

void ContactsListWidget::initUi()
{
	m_blankMenu = new QMenu();
	m_contactMenu = new QMenu();
	m_groupMenu = new QMenu();
	m_groupNameEdit = new QLineEdit();

	QAction *addGroup = new QAction("Add group", this);
	QAction *delGroup = new QAction("Delete group", this);
	QAction *addContact = new QAction("Add contact", this);
	QAction *delContact = new QAction("Delete contact", this);
	QAction *editName = new QAction("Rename", this);

	m_groupNameEdit->addAction(editName);
	m_groupNameEdit->hide();
	m_groupNameEdit->setPlaceholderText("Unnamed");

	m_blankMenu->addAction(addGroup);
	m_groupMenu->addAction(delGroup);
	m_groupMenu->addAction(editName);
	m_groupMenu->addAction(addContact);
	m_contactMenu->addAction(delContact);

	connect(addGroup, SIGNAL(triggered()), this, SLOT(onAddGroup()));
	connect(delGroup, SIGNAL(triggered()), this, SLOT(onDelGroup()));
	connect(addContact, SIGNAL(triggered()), this, SLOT(onAddContact()));
	connect(delContact, SIGNAL(triggered()), this, SLOT(onDelContact()));
	connect(editName, SIGNAL(triggered()), this, SLOT(onEditName()));
}

void ContactsListWidget::mousePressEvent(QMouseEvent *event)
{
	QListWidget::mousePressEvent(event);

	if (m_groupNameEdit->isVisible() && !(m_groupNameEdit->rect().contains(event->pos())))
	{
		if (NULL != m_groupNameEdit->text())
		{
			m_currentItem->setText(m_groupNameEdit->text());
		}
		m_groupNameEdit->setText("");
		m_groupNameEdit->hide();
	}

	m_currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));

	if (Qt::LeftButton == event->button() && NULL != m_currentItem && m_currentItem == m_groupMap.value(m_currentItem))
	{
		if (m_isHideMap.value(m_currentItem))
		{

			foreach(QListWidgetItem *subItem, m_groupMap.keys())
			{
				if (m_currentItem != subItem)
				{
					subItem->setHidden(false);
				}
			}
			m_isHideMap.insert(m_currentItem, false);
			m_currentItem->setIcon(QIcon(":/LoginWindow/Resources/down.ico"));
		}
		else
		{
			foreach(QListWidgetItem *subItem, m_groupMap.keys())
			{
				if (m_currentItem != subItem)
				{
					subItem->setHidden(true);
				}
			}
			m_isHideMap.insert(m_currentItem, true);
			m_currentItem->setIcon(QIcon(":/LoginWindow/Resources/right.ico"));
		}
	}
}

void ContactsListWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QListWidget::contextMenuEvent(event);

	if (NULL == m_currentItem)
	{
		m_blankMenu->exec(QCursor::pos());
		return;
	}

	if (m_currentItem == m_groupMap.value(m_currentItem))
	{
		m_groupMenu->exec(QCursor::pos());
	}
	else
	{
		m_contactMenu->exec(QCursor::pos());
	}
}

void ContactsListWidget::onAddGroup()
{
	QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/LoginWindow/Resources/right.ico"), "Unnamed");
	newItem->setSizeHint(QSize(this->width(), 25));
	this->addItem(newItem);
	m_groupMap.insert(newItem, newItem);
	m_isHideMap.insert(newItem, true);
	m_groupNameEdit->raise();
	m_groupNameEdit->setText("Unnamed");
	m_groupNameEdit->selectAll();
	m_groupNameEdit->setGeometry(this->visualItemRect(newItem).left() + 15, this->visualItemRect(newItem).top() + 1, this->visualItemRect(newItem).width(), this->visualItemRect(newItem).height() - 2);
	m_groupNameEdit->show();
	m_groupNameEdit->setFocus();
	m_currentItem = newItem;
}

void ContactsListWidget::onDelGroup()
{
	foreach(QListWidgetItem *item, m_groupMap.keys(m_currentItem))
	{
		m_groupMap.remove(item);
		delete item;
	}
	m_isHideMap.remove(m_currentItem);
}

void ContactsListWidget::onEditName()
{
	/*m_groupNameEdit->raise();
	m_groupNameEdit->setGeometry(this->visualItemRect(m_currentItem).left() + 15, this->visualItemRect(m_currentItem).top() + 1, this->visualItemRect(currentItem).width(), this->visualItemRect(currentItem).height() - 2);
	m_groupNameEdit->setText(m_currentItem->text());
	m_groupNameEdit->show();
	m_groupNameEdit->selectAll();
	m_groupNameEdit->setFocus();*/
}

void ContactsListWidget::onAddContact()
{
	ContactsListWidget *contact = new ContactsListWidget();
	//contact->profilePath = ":/LoginWindow/Resources/profile.png";
	//contact->name->setText("Tester");
	//contact->sign->setText("Hello, world");
	QList<QListWidgetItem*> subItems = m_groupMap.keys(m_currentItem);
	QListWidgetItem *newItem = new QListWidgetItem();
	this->insertItem(row(m_currentItem) + subItems.count(), newItem);
	this->setItemWidget(newItem, contact);
	m_groupMap.insert(newItem, m_currentItem);
	if (m_isHideMap.value(m_currentItem))
	{
		newItem->setHidden(true);
	}
	else
	{
		newItem->setHidden(false);
	}
}

void ContactsListWidget::onDelContact()
{
	m_groupMap.remove(m_currentItem);
	delete m_currentItem;
}

void ContactsListWidget::onEditNameFinished()
{
	if (NULL != m_groupNameEdit->text())
	{
		m_currentItem->setText(m_groupNameEdit->text());
	}
	m_groupNameEdit->setText("");
	m_groupNameEdit->hide();
}
