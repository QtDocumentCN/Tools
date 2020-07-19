#include "bookgeneraterkit.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>


/*
 * //example
 *
# Summary

- [简介](./BookInfo.md)
	- [A]()
		- [QAbstractSocket](./Src/A/QAbstractSocket/QAbstractSocket.md)
		- [QAbstractAnimation](./Src/A/QAbstractAnimation/QAbstractAnimation.md)
		- [QAbstractAudioOutput](./Src/A/QAbstractAudioOutput/QAbstractAudioOutput.md)
		- [QAbstractAudioDeviceInfo](./Src/A/QAbstractAudioDeviceInfo/QAbstractAudioDeviceInfo.md)
		- [QAbstractAxis](./Src/A/QAbstractAxis/QAbstractAxis.md)
		- [QAbstractAudioInput](./Src/A/QAbstractAudioInput/QAbstractAudioInput.md)
		- [QAbstractBarSeries](./Src/A/QAbstractBarSeries/QAbstractBarSeries.md)
	- [B]()
		- [Best_Practice_Guides](./Src/B/Best_Practice_Guides/Best_Practice_Guides.md)
	- [C]()
		- [Container_Classes](./Src/C/Container_Classes/Container_Classes.md)
		- [QCheckBox](./Src/C/QCheckBox/QCheckBox.md)
		- [QComboBox](./Src/C/QComboBox/QComboBox.md)
*/

namespace
{
	const QString SUMMART_FILE_PATH = QString::fromLatin1("/Book/src/SUMMARY.md");
	QString Demo = QString::fromLatin1("- [%1](%2)");
	const QString BookInfo = QString::fromLatin1("./BookInfo.md");
}

BookGeneraterKit::BookGeneraterKit(QString docCnPath, QObject *parent)
								: QObject(parent)
								, m_DocCnPath(docCnPath)
{
	m_SummaryPath = docCnPath + SUMMART_FILE_PATH;
}

bool BookGeneraterKit::generaterSummary()
{
	QTemporaryFile temFile;
	temFile.setAutoRemove(true);
	if (temFile.open())
	{
		QTextStream out(&temFile);
		out.setCodec("UTF-8");
		_generaterFile(out);
	}
	else
	{
	}

	QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	temFile.close();
	desktopPath += "/123.md";
	temFile.copy(desktopPath);
}

void BookGeneraterKit::_generaterFile(QTextStream &out)
{
	_generaterHeader(out);
	_generaterBody(out);
}

void BookGeneraterKit::_generaterHeader(QTextStream &out)
{
	out<<"# Summary"<<endl;
	out<<endl;
	QString title = Demo.arg(QString::fromUtf8("简介")).arg(BookInfo);
	out<<title<<endl;
}

void BookGeneraterKit::_generaterBody(QTextStream &out)
{
	QString mdPath = m_DocCnPath + QString::fromLatin1("/Src");
	QDir dir(mdPath);
	QFileInfoList fileInfoList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);

	foreach(const QFileInfo& fileInfo, fileInfoList)
	{
		QString parentFile = fileInfo.fileName();
		parentFile = Demo.arg(parentFile).arg("");

		out << QString::fromLatin1("	")<<parentFile<<endl;

		qDebug()<<fileInfo.absoluteFilePath()<<endl;

		QString parentFilePath = fileInfo.absoluteFilePath();

		QDir codeDir(fileInfo.absoluteFilePath());
		QFileInfoList codeFileInfoList = codeDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);

		//这里便利A下面的所有的文件夹
		foreach (const QFileInfo& codefileInfo, codeFileInfoList)
		{
//			qDebug()<<"		"<<codefileInfo.baseName()<<endl;
			QString baseName = codefileInfo.baseName();
			QString mdName = parentFilePath + "/" + baseName + "/" + baseName + QString::fromLatin1(".md");
			if (QFile(mdName).exists())
			{
				QString mdBaseName = QFileInfo(mdName).baseName();

				mdName = mdName.remove(m_DocCnPath);
				mdName = "." + mdName;

				QString outMdName = Demo.arg(mdBaseName).arg(mdName);

				out << "		"<<outMdName<<endl;
			}
		}
	}
}
