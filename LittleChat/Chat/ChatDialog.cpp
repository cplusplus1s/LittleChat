#include "ChatDialog.h"
#include <QKeyEvent>
#include <QRegExp>

ChatDialog::ChatDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_networkMng = GlooxManager::createGlooxMng();

	initUi();

	connect(m_emojiWidget, SIGNAL(emojiClicked(int)), this, SLOT(onEmojiClicked(int)));
}

ChatDialog::~ChatDialog()
{
}

void ChatDialog::initUi()
{
	ui.inputTextEdit->installEventFilter(this);

	m_emojiWidget = new EmojiWidget();
	m_emojiWidget->move(ui.emojiButton->pos() - QPoint(0, m_emojiWidget->height()));
}

bool ChatDialog::eventFilter(QObject *target, QEvent *event)
{
	if (target == ui.inputTextEdit)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Return)
			{
				if (keyEvent->modifiers()&Qt::ControlModifier)
				{
					//ui.inputTextEdit->moveCursor(QTextCursor::NextRow);
					//ui.inputTextEdit->append("");
					send();
					ui.inputTextEdit->clear();
				}
				else
				{
					//send();
					//ui.inputTextEdit->setPlainText("");
				}
			}
			/*if (keyEvent->key() == Qt::Key_Return && (keyEvent->modifiers()&Qt::ControlModifier))
			{
				ui.inputTextEdit->moveCursor(QTextCursor::NextRow);
			}*/
		}
	}
	return QDialog::eventFilter(target, event);
}

void ChatDialog::closeEvent(QCloseEvent *event)
{
	//static_cast<ChatWindow*>(this->parent())->removeChatDialog(m_contactId);
	m_emojiWidget->close();
	QDialog::closeEvent(event);
}

void ChatDialog::mousePressEvent(QMouseEvent *event)
{
	if ((!m_emojiWidget->rect().contains(event->pos())) && !m_emojiWidget->isHidden())
	{
		m_emojiWidget->hide();
	}
	QDialog::mousePressEvent(event);
}

void ChatDialog::send()
{
	Q_ASSERT(!m_contactId.isEmpty());
	m_networkMng->sendMessage(m_contactId.toStdString(), ui.inputTextEdit->toPlainText().toStdString());
	outputMessage(ui.inputTextEdit->toPlainText(), QString::fromStdString(m_networkMng->getId()));
}

void ChatDialog::outputMessage(const QString& msg, const QString& id)
{
	ui.outputTextEdit->append(id + ": ");

	QRegExp emojiRx("\\[emoji:(\\d+)\\]");
	int curPos = 0;
	int textStartPos = 0;
	while (-1 != (curPos = emojiRx.indexIn(msg, curPos)))
	{
		ui.outputTextEdit->insertPlainText(msg.mid(textStartPos, curPos - textStartPos));
		insertEmojiToOutput(emojiRx.cap(1).toInt());
		curPos += emojiRx.matchedLength();
		textStartPos = curPos;
	}
	ui.outputTextEdit->insertPlainText(msg.mid(textStartPos));
}

void ChatDialog::insertEmojiToOutput(int emojino)
{
	QImage img;
	img.load(":/gif/Resources/emoji_" + QString::number(emojino) + ".gif");
	QTextDocument *document = ui.outputTextEdit->document();
	document->addResource(QTextDocument::ImageResource, QUrl("emoji" + QString::number(emojino)), QVariant(img));
	QTextCursor textCursor = ui.outputTextEdit->textCursor();
	textCursor.insertImage("emoji" + QString::number(emojino));
}

const QString& ChatDialog::getContactId() const
{
	return m_contactId;
}

void ChatDialog::setContactId(const QString& id)
{
	m_contactId = id;
}

void ChatDialog::onEmojiClicked(int emojiname)
{
	ui.inputTextEdit->insertPlainText("[emoji:" + QString::number(emojiname) + "]");
}

void ChatDialog::on_emojiButton_clicked()
{
	if (m_emojiWidget->isHidden())
	{
		m_emojiWidget->show();
	}
	else
	{
		m_emojiWidget->hide();
	}
}
