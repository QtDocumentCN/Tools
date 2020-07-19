#ifndef BOOKGENERATERKIT_H
#define BOOKGENERATERKIT_H

#include <QObject>

class QTextStream;

class BookGeneraterKit : public QObject
{
	Q_OBJECT
public:
	explicit BookGeneraterKit(QString docCnPath, QObject *parent = nullptr);

public:
	bool generaterSummary();

private:
	void _generaterFile(QTextStream&);
	void _generaterHeader(QTextStream&);
	void _generaterBody(QTextStream&);

signals:

public slots:

private:
	QString m_DocCnPath;
	QString m_SummaryPath;
};

#endif // BOOKGENERATERKIT_H
