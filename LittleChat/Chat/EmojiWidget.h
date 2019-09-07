#pragma once

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QMovie>
#include "ui_EmojiWidget.h"

enum EmojiName
{
	EMOJI_LAUGH,
	EMOJI_SMILE,
	EMOJI_UNHAPPY,
	EMOJI_ANGRY,
	EMOJI_CRY,
	EMOJI_TITTER,
	EMOJI_SWEAT,
	EMOJI_DIZZY,
	EMOJI_BYEBYE
};

const int EMOJI_COUNT = 9;
const int EMOJI_ROWCOUNT = 3;


class EmojiWidget : public QWidget
{
	Q_OBJECT

public:
	EmojiWidget(QWidget *parent = Q_NULLPTR);
	~EmojiWidget();

	void initUi();
	void addEmojiItem(const QString& emojiname);
	
signals:
	void emojiClicked(int emojiname);

private slots:
	void on_tableWidget_cellPressed(int row, int column);

private:
	Ui::EmojiWidget ui;
	QList<QString> m_emojiList;
};
