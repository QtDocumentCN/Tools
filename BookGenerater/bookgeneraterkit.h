#ifndef BOOKGENERATERKIT_H
#define BOOKGENERATERKIT_H

#include <QObject>

class BookGeneraterKit : public QObject
{
	Q_OBJECT
public:
	explicit BookGeneraterKit(QString docCnPath, QObject *parent = nullptr);

public:
	bool generaterSummary();

signals:

public slots:

private:
	QString m_DocCnPath;
	QString m_SummaryPath;
};

#endif // BOOKGENERATERKIT_H
