#ifndef HEXOADDTITLE_H
#define HEXOADDTITLE_H

#include <QObject>
#include <QString>
#include <QFileInfo>

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

	void seekTitle();
	void ensureTitle(const QFileInfo& fileInfo);


private:
	QString m_docCnPath;
	QString m_newPath; //拷贝出来的文件夹
};

#endif // HEXOADDTITLE_H
