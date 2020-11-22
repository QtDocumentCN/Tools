#ifndef HEXOADDTITLE_H
#define HEXOADDTITLE_H

#include <QObject>
#include <QString>

class HexoAddTitle : public QObject
{
	Q_OBJECT
public:
	explicit HexoAddTitle(const QString& docCnPath, QObject *parent = nullptr);

public:
	void addTitle();

signals:

private:
	void initPath();


private:
	QString m_docCnPath;
	QString m_newPath;
};

#endif // HEXOADDTITLE_H
