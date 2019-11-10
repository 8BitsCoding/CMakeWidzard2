#include "CMakeWidzard2.h"
#include <QtCore/qdebug.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "CMakeLists.h"


CMakeWidzard2::CMakeWidzard2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.flagsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	ui.sourcesTable->horizontalHeader()->setStretchLastSection(true);
	ui.sourcesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
}

void CMakeWidzard2::on_actionExport_triggered()
{
	QString dir = QFileDialog::getExistingDirectory(this, "Directory to save", QDir::currentPath(), QFileDialog::ShowDirsOnly);
	
	if (dir.length() == 0) {
		QMessageBox::critical(this, "Failed to get dir", "Failed to get directory to save", QMessageBox::Ok);
		return;
	}

	auto filePath = QDir(dir).filePath("CMakeLists.txt");

	QFile file(filePath);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	PrepareCMakeListVariables();

	QTextStream stream(&file);

	stream << cmakeListResult << endl;

	file.close();
}


void CMakeWidzard2::InsertFlagItem(const QString& key, const QString& value)
{
	int row = ui.flagsTable->rowCount();
	ui.flagsTable->insertRow(row);
	auto KeyColumn = new QTableWidgetItem(key);
	auto valueColumn = new QTableWidgetItem(value);
	ui.flagsTable->setItem(row,0,KeyColumn);
	ui.flagsTable->setItem(row, 0, valueColumn);
}

void CMakeWidzard2::on_AddBtn_clicked()
{
	InsertFlagItem("<key>", "<value>");
}

void CMakeWidzard2::on_RemoveBtn_clicked()
{
	ui.flagsTable->removeRow(ui.flagsTable->currentRow());
}

void CMakeWidzard2::on_addincludeBtn_clicked()
{
	insertNewIncludeDirectory("<Path>");
}

void CMakeWidzard2::insertNewIncludeDirectory(const QString& dir)
{
	QListWidgetItem* newItem = new QListWidgetItem(dir);
	newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);

	ui.includeList->addItem(newItem);
}

void CMakeWidzard2::on_includeList_itemChanged(QListWidgetItem* item)
{
	if (item->text().length() == 0) {
		ui.includeList->takeItem(ui.includeList->row(item));
	}
}

void CMakeWidzard2::on_addsourceBtn_clicked()
{
	addSource("<Target>", "<sources>");
}

void CMakeWidzard2::addSource(const QString& target, const QString& sources)
{
	int row = ui.sourcesTable->rowCount();
	ui.sourcesTable->insertRow(row);

	auto targetColumn = new QTableWidgetItem(target);
	auto sourcesColumn = new QTableWidgetItem(sources);

	ui.sourcesTable->setItem(row, 0, targetColumn);
	ui.sourcesTable->setItem(row, 0, sourcesColumn);
}

void CMakeWidzard2::on_removesourceBtn_clicked()
{
	ui.sourcesTable->removeRow(ui.sourcesTable->currentRow());
}

void CMakeWidzard2::currentTabChanged(int tab)
{
	qDebug() << "current tab index" << tab << endl;

	if (tab == 4) {
		// Make CMake file
		PrepareCMakeListVariables();
	}
}

void CMakeWidzard2::PrepareCMakeListVariables()
{
	CMakeLists cmakelists;

	// project tab
	QString projectName = ui.ProjectNamelineEdit->text();

	cmakelists.SetProjectName(projectName);

	// flags tab
	auto flagsCount = ui.flagsTable->rowCount();
	for (int rowIndex = 0; rowIndex < flagsCount; rowIndex++) {
		auto keyItem = ui.flagsTable->item(rowIndex, 0);
		auto valueItem = ui.flagsTable->item(rowIndex, 1);

		QString flagsKey = keyItem->text();
		QString flasvalye = valueItem->text();
		cmakelists.AddCMakeFlags(flagsKey, flasvalye);
	}

	// preprocessor tab
	if (ui.definesEdit->toPlainText().size() > 0) {
		QStringList defines = ui.definesEdit->toPlainText().split(QRegExp("\\| \\;|\\n"));
		for (int index = 0; index < defines.length(); index++) {
			qDebug() << defines.at(index) << endl;
			cmakelists.AddDefine(defines.at(index));
		}
	}

	// directory tab
	// 1. include dir(QListWidget)
	for (int row = 0; row < ui.includeList->count(); row++) {
		auto item = ui.includeList->item(row);	// QListWidgetItem
		QString includeDir = item->text();
		cmakelists.AddIncludeDirectory(includeDir);
	}
	// 2. sources(QtableWidget)
	for (int row = 0; row < ui.sourcesTable->rowCount(); row++) {
		auto target = ui.sourcesTable->item(row, 0);
		auto sources = ui.sourcesTable->item(row, 1);

		cmakelists.AddSource(target->text(), sources->text());
	}

	// preview tab
	QString previewCMakeList_txt = cmakelists.GenerateCMakeLists();

	ui.previewText->clear();
	ui.previewText->appendPlainText(previewCMakeList_txt);

	cmakeListResult = previewCMakeList_txt;
}