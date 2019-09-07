#include "ContactWidget.h"
#include <QLayout>

ContactWidget::ContactWidget(QWidget *parent)
	: QWidget(parent)
{
	initUi();
}

ContactWidget::~ContactWidget()
{
	delete m_profile;
	delete m_name;
	delete m_sign;
	delete m_state;
}

void ContactWidget::initUi()
{
	m_profile = new QLabel(this);
	m_name = new QLabel(this);
	m_sign = new QLabel(this);
	m_state = new QLabel(this);

	refreshContact();

	QHBoxLayout *hLay1 = new QHBoxLayout();
	hLay1->addWidget(m_name);
	hLay1->addWidget(m_state);
	QVBoxLayout *vLay1 = new QVBoxLayout();
	vLay1->addLayout(hLay1);
	vLay1->addWidget(m_sign);
	QHBoxLayout *hLay2 = new QHBoxLayout();
	hLay2->addWidget(m_profile);
	hLay2->addLayout(vLay1);
	setLayout(hLay2);
}


void ContactWidget::refreshContact()
{
	QImage *img = new QImage();
	img->load(":/LoginWindow/Resources/profile.png");
	setProfile(img);

	setName("Unnamed");
	setOnlineState(false);
	setSign("...");
}

void ContactWidget::setProfile(QImage *img)
{
	*img = img->scaled(m_profile->width(), m_profile->width());
	m_profile->setPixmap(QPixmap::fromImage(*img));
}

void ContactWidget::setName(QString name)
{
	m_name->setText(name);
}

void ContactWidget::setSign(QString sign)
{
	m_sign->setText(sign);
}

void ContactWidget::setOnlineState(bool online)
{
	if (online)
	{
		QPalette palette;
		palette.setColor(QPalette::WindowText, Qt::green);
		m_state->setPalette(palette);
		m_state->setText("(online)");
	}
	else
	{
		QPalette palette;
		palette.setColor(QPalette::WindowText, Qt::red);
		m_state->setPalette(palette);
		m_state->setText("(offline)");
	}
}

void ContactWidget::setId(const QString& id)
{
	m_id = id;
}

const QString& ContactWidget::getId() const
{
	return m_id;
}
