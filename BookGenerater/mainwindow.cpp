#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bookgeneraterkit.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(selectCnFolder()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::selectCnFolder()
{
	QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
	QString docCnPath = QFileDialog::getExistingDirectory(NULL, "test", desktopPath);
	docCnPath = QFileInfo(docCnPath).absoluteFilePath();
	if (!docCnPath.isEmpty() && docCnPath.endsWith("QtDocumentCN") )
	{
		BookGeneraterKit kit(docCnPath, this);
		kit.generaterSummary();
	}
	else
	{
		QMessageBox::information(NULL, "Warrning", "Please Slect QtDocument Folder");
	}
}
