#include "main_window.h"
#include "./ui_main_window.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Simple Countdown");

    connect(ui->alwaysOnTop, &QCheckBox::stateChanged, [this](int state) {
        setWindowFlag(Qt::WindowStaysOnTopHint, state == Qt::Checked);
        show();
    });

    ui->alwaysOnTop->click();
    ui->alwaysOnTop->click();

    connect(ui->startStop, &QPushButton::clicked, [this]() {
        if (ui->countdown->isRunning())
            ui->countdown->stop();
        else
            ui->countdown->start({ 0, ui->minSpinBox->value(), ui->secSpinBox->value() });
    });

    connect(ui->countdown, &CountdownLabel::started, [this]() {
        updateControls(true);
    });

    connect(ui->countdown, &CountdownLabel::finished, [this]() {
        updateControls(false);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateControls(bool isRunning)
{
    ui->minSpinBox->setEnabled(!isRunning);
    ui->secSpinBox->setEnabled(!isRunning);

    ui->startStop->setText(isRunning ? "Stop" : "Start");
}
