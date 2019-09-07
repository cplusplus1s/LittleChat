#include "EmojiWidget.h"

EmojiWidget::EmojiWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initUi();
}

EmojiWidget::~EmojiWidget()
{
}

void EmojiWidget::initUi()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	ui.tableWidget->setFocusPolicy(Qt::NoFocus);

	QString emojiPath = ":/gif/Resources/emoji_%1.gif";
	for (int i = 0; i < EMOJI_COUNT; i++)
	{
		addEmojiItem(emojiPath.arg(i));
	}
}

void EmojiWidget::addEmojiItem(const QString& emojiname)
{
	int row = m_emojiList.size() / ui.tableWidget->rowCount();
	int col = m_emojiList.size() % ui.tableWidget->columnCount();

	QTableWidgetItem* item = new QTableWidgetItem();
	ui.tableWidget->setItem(row, col, item);

	QMovie *movie = new QMovie();
	movie->setScaledSize(QSize(18, 18));
	movie->setFileName(emojiname);
	movie->start();
	QLabel *label = new QLabel();
	label->setMovie(movie);
	ui.tableWidget->setCellWidget(row, col, label);
	m_emojiList.push_back(emojiname);
}

void EmojiWidget::on_tableWidget_cellPressed(int row, int column)
{
	emit emojiClicked(row*EMOJI_ROWCOUNT + column);
}
