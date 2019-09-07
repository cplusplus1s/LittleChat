#pragma once

#include <QWidget>
#include <QLabel>
#include <QImage>

class ContactWidget : public QWidget
{
	Q_OBJECT
private:
	QLabel *m_profile;
	QLabel *m_name;
	QLabel *m_sign;
	QLabel *m_state;

public:
	ContactWidget(QWidget *parent = Q_NULLPTR);
	~ContactWidget();

	void initUi();
	void refreshContact();

public:
	void setProfile(QImage *img);
	void setName(QString name);
	void setSign(QString sign);
	void setOnlineState(bool online);
	void setId(const QString& id);
	const QString& getId() const;
private:
	QString m_id;
};
