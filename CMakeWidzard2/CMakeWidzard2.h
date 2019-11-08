#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMakeWidzard2.h"

class CMakeWidzard2 : public QMainWindow
{
	Q_OBJECT

public:
	CMakeWidzard2(QWidget *parent = Q_NULLPTR);

private:
	Ui::CMakeWidzard2Class ui;
};
