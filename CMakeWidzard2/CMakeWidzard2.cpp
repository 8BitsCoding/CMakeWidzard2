#include "CMakeWidzard2.h"

CMakeWidzard2::CMakeWidzard2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.flagsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void CMakeWidzard2::on_actionExport_triggered()
{
	QString projectName = ui.ProjectNamelineEdit->text();
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