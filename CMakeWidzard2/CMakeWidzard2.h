#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMakeWidzard2.h"

class CMakeWidzard2 : public QMainWindow
{
	Q_OBJECT

public:
	CMakeWidzard2(QWidget *parent = Q_NULLPTR);

	void InsertFlagItem(const QString&, const QString&);
	void insertNewIncludeDirectory(const QString&);

private slots:
	void on_actionExport_triggered();
	void on_AddBtn_clicked();
	void on_RemoveBtn_clicked();
	void on_addincludeBtn_clicked();
	void on_includeList_itemChanged(QListWidgetItem* item);

private:
	Ui::CMakeWidzard2Class ui;
};
