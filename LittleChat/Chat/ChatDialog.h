#pragma once

#include <QDialog>
#include "ui_ChatDialog.h"
#include "UiListener.h"
#include "GlooxManager.h"
#include "ChatWindow.h"
#include "EmojiWidget.h"

class ChatDialog : public QDialog
{
	Q_OBJECT

public:
	ChatDialog(QWidget *parent = Q_NULLPTR);
	~ChatDialog();

	void initUi();
	void outputMessage(const QString& msg, const QString& id);
	void send();
	void insertEmojiToOutput(int emojino);

	const QString& getContactId() const;
	void setContactId(const QString& id);

	bool eventFilter(QObject *target, QEvent *event);
	void closeEvent(QCloseEvent *event);
	void mousePressEvent(QMouseEvent *event);

public slots:
	void onEmojiClicked(int emojiname);
	void on_emojiButton_clicked();

private:
	Ui::ChatDialog ui;
	GlooxManager *m_networkMng;
	QString m_contactId;
	EmojiWidget *m_emojiWidget;
};
