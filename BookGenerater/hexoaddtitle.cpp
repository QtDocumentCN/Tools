#include "hexoaddtitle.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>

namespace
{
	const QString strDesktopName = QString::fromUtf8("Qt中文文档");
	const QString strTitlePrefix = QString::fromUtf8("Qt中文文档-%1");
	const QString strSrc = QString::fromLatin1("Src");
	const QString strAuthor = QString::fromUtf8("张小飞");
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

	//遍历A-Z那一层
	QFileInfoList m_fileInfoList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
	foreach (const QFileInfo& fileInfo, m_fileInfoList)
	{

		QDir dirChar(fileInfo.absoluteFilePath()); // 遍历A这一层
		QFileInfoList fileInfoList = dirChar.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
		foreach (const QFileInfo& dirFileInfo, fileInfoList)
		{
			QDir dirCharFile(dirFileInfo.absoluteFilePath()); // 遍历A这一层
			QFileInfoList charFileList = dirCharFile.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
			foreach (const QFileInfo& charFileInfo, charFileList)
			{
				QString fileName = charFileInfo.fileName();
//				qDebug()<<fileName<<endl;
//				QFile::copy()
//				qDebug()<<charFileInfo.absoluteFilePath();
				QString newPath = m_newPath + QDir::separator() + fileName;
				newPath = QDir::toNativeSeparators(newPath);
//				qDebug()<<newPath<<endl;
				QFile::copy(charFileInfo.absoluteFilePath(), newPath);
			}

//			qDebug()<<fileInfo.absoluteFilePath();
		}

//		qDebug()<<fileInfo.absoluteFilePath();
	}

	seekTitle();


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
	if (!dir.exists())
	{
		dir.mkdir(desktopPath);
	}


	m_newPath = QDir::toNativeSeparators(desktopPath);
}

void HexoAddTitle::seekTitle()
{
	qDebug()<<"------being seekTitle"<<endl;
	QDir dir(m_newPath);

	QFileInfoList fileInfoList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);

	foreach (const QFileInfo& dirFileInfo, fileInfoList)
	{
//		qDebug()<<dirFileInfo.suffix()<<endl;
		if (dirFileInfo.suffix() == QString::fromLatin1("md"))
		{
			ensureTitle(dirFileInfo);
		}
	}

	qDebug()<<"------end seekTitle"<<endl;
}

//---
//title: Qt中文文档-QX11Info
//author: 张小飞
//top: false
//toc: true
//mathjax: true
//date: 2020-07-15 21:26:44
//tags:
//	- Qt中文文档
//	- Qt
//	- QX11Info
//categories:
//	- Qt中文文档
//	- Qt中文文档-X
//summary:
//---
void HexoAddTitle::ensureTitle(const QFileInfo &fileInfo)
{
	// 1.
	QString strFileName = fileInfo.baseName();

	QString strTitle = strTitlePrefix.arg(strFileName);

	QString strTime = fileInfo.birthTime().toString("yyyy-MM-dd hh:mm:ss");

	QChar ch1 = strFileName.at(0);
	QChar ch2 = strFileName.at(1);

	QString strCategories = QString::fromUtf8("- Qt中文文档-%1");
	if (ch1 == QChar('Q') && ch2 >= QChar('A') && ch2 <= QChar('Z'))
	{
		strCategories = strCategories.arg(ch2);
	}
	else
	{
		strCategories = strCategories.arg(QString::fromUtf8("综述"));
	}


	qDebug()<<QString::fromLatin1("title: %1").arg(strTitle)<<endl;
	qDebug()<<QString::fromLatin1("author: %1").arg(strAuthor)<<endl;
	qDebug()<<QString::fromLatin1("top: false")<<endl;
	qDebug()<<QString::fromLatin1("toc: true")<<endl;
	qDebug()<<QString::fromLatin1("mathjax: true")<<endl;
	qDebug()<<QString::fromLatin1("date: %1").arg(strTime)<<endl;

	//-tag
	qDebug()<<QString::fromLatin1("tags:")<<endl;
	qDebug()<<QString::fromLatin1("    %1").arg(QString::fromUtf8("- Qt中文文档"))<<endl;
	qDebug()<<QString::fromLatin1("    %1").arg(QString::fromLatin1("- Qt"))<<endl;

	//-categories

	qDebug()<<QString::fromLatin1("categories:")<<endl;
	qDebug()<<QString::fromLatin1("    %1").arg(QString::fromUtf8("- Qt中文文档"))<<endl;
	qDebug()<<QString::fromLatin1("    %1").arg(strCategories)<<endl;


	QFile file(fileInfo.absoluteFilePath());
	if (!file.open(QIODevice::ReadWrite))
		return;

	QTextStream out(&file);
	out.setCodec("UTF-8");

	QString strAllGB2312 = out.readAll();
	out.seek(0);

	out<<QString::fromLatin1("---")<<endl;
	out<<QString::fromLatin1("title: %1").arg(strTitle)<<endl;
	out<<QString::fromLatin1("author: %1").arg(strAuthor)<<endl;
	out<<QString::fromLatin1("top: false")<<endl;
	out<<QString::fromLatin1("toc: true")<<endl;
	out<<QString::fromLatin1("mathjax: true")<<endl;
	out<<QString::fromLatin1("date: %1").arg(strTime)<<endl;

	//-tag
	out<<QString::fromLatin1("tags:")<<endl;
	out<<QString::fromLatin1("    %1").arg(QString::fromUtf8("- Qt中文文档"))<<endl;
	out<<QString::fromLatin1("    %1").arg(QString::fromLatin1("- Qt"))<<endl;

	//-categories

	out<<QString::fromLatin1("categories:")<<endl;
	out<<QString::fromLatin1("    %1").arg(QString::fromUtf8("- Qt中文文档"))<<endl;
	out<<QString::fromLatin1("    %1").arg(strCategories)<<endl;

	out<<QString::fromLatin1("---")<<endl;

	out<<QString::fromLatin1("              ")<<endl;

	out<<strAllGB2312<<endl;

	out.flush();
	file.close();
}
