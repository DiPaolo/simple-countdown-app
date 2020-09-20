#include "main_window.h"
#include "./ui_main_window.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_timeoutSound(":/sounds/alarm-clock-01.wav", this)
{
    ui->setupUi(this);

    setWindowTitle("Simple Countdown");

    connect(ui->startStop, &QPushButton::clicked, [this]() {
        if (ui->countdown->isRunning())
            ui->countdown->stop();
        else
        {
            m_timeoutSound.stop();
            ui->countdown->start({ 0, ui->minSpinBox->value(), ui->secSpinBox->value() });
        }
    });

    connect(ui->countdown, &CountdownLabel::started, [this]() {
        updateControls(true);
    });

    connect(ui->countdown, &CountdownLabel::finished, [this](bool canceled) {
        if (!canceled)
            m_timeoutSound.play();
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
