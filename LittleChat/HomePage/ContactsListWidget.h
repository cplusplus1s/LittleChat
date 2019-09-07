#pragma once

#include <QListWidget>
#include <QMenu>
#include <QLineEdit>

class ContactsListWidget : public QListWidget
{
	Q_OBJECT

public:
	ContactsListWidget(QListWidget *parent = Q_NULLPTR);
	~ContactsListWidget();

	void initUi();
	void mousePressEvent(QMouseEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);	

public slots:
	void onAddGroup();
	void onDelGroup();
	void onAddContact();
	void onDelContact();
	void onEditName();
	void onEditNameFinished();

private:
	QMenu *m_blankMenu;
	QMenu *m_contactMenu;
	QMenu *m_groupMenu;
	QMap<QListWidgetItem*, QListWidgetItem*> m_groupMap;
	QMap<QListWidgetItem*, bool> m_isHideMap;
	QLineEdit *m_groupNameEdit;
	QListWidgetItem *m_currentItem;
};
