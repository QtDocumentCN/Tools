#include "bookgeneraterkit.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QTextStream>

namespace
{
	const QString SUMMART_FILE_PATH = QString::fromLatin1("/Book/src/SUMMARY.md");
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
		out<<" "<<endl;
	}
	else
	{
	}

	temFile.close();


}
