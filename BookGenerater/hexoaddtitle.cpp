#include "hexoaddtitle.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

namespace
{
	const QString strDesktopName = QString::fromUtf8("Qt中文文档");
	const QString strTitlePrefix = QString::fromUtf8("Qt中文文档-");
	const QString strSrc = QString::fromLatin1("Src");
}
HexoAddTitle::HexoAddTitle(const QString& docCnPath, QObject *parent) : QObject(parent), m_docCnPath(docCnPath)
{
	m_docCnPath += (QDir::separator() + strSrc);




	initPath();
}

void HexoAddTitle::addTitle()
{
	QFileInfo fileInfo(m_docCnPath);
	QDir dir(m_docCnPath);


	QFileInfoList m_fileInfoList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
	foreach (const QFileInfo& fileInfo, m_fileInfoList)
	{
		qDebug()<<fileInfo.absoluteFilePath();
	}
}

// 1.一点点的拷贝到桌面文件夹
void HexoAddTitle::initPath()
{
	QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	desktopPath += (QDir::separator() + strDesktopName);
	QDir dir(desktopPath);
	if (dir.exists())
	{
		dir.rmpath(desktopPath);
	}
	else
	{
		dir.mkdir(desktopPath);
	}


	m_newPath = desktopPath;
}
