#include "main_window.h"
#include "./ui_main_window.h"

#include <QDebug>
#include <QIntValidator>
#include <QMouseEvent>
#include <QSettings>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Simple Countdown");
    setWindowFlag(Qt::FramelessWindowHint, true);

    connect(ui->alwaysOnTop, &QCheckBox::stateChanged, [this](int state) {
        setWindowFlag(Qt::WindowStaysOnTopHint, state == Qt::Checked);
        show();
    });

    ui->mins->setValidator(new QIntValidator(0, m_maxMins, ui->mins));
    ui->secs->setValidator(new QIntValidator(0, m_maxSecs, ui->secs));

    connect(ui->mins, &QLineEdit::textChanged, [this](const QString &text) {
        bool ok = false;
        const auto val = text.toInt(&ok);
        if (!ok)
            Q_ASSERT(false);
        else if (val > m_maxMins)
            ui->mins->setText(QString::number(m_maxMins));
    });

    connect(ui->secs, &QLineEdit::textChanged, [this](const QString &text) {
        bool ok = false;
        const auto val = text.toInt(&ok);
        if (!ok)
            Q_ASSERT(false);
        else if (val > m_maxSecs)
            ui->secs->setText(QString::number(m_maxSecs));
    });

    connect(ui->startStop, &QPushButton::clicked, [this]() {
        if (ui->countdown->isRunning())
            ui->countdown->stop();
        else
            ui->countdown->start({ 0, ui->mins->text().toInt(), ui->secs->text().toInt() });
    });

    connect(ui->countdown, &CountdownLabel::started, [this]() {
        updateControls(true);
    });

    connect(ui->countdown, &CountdownLabel::finished, [this]() {
        updateControls(false);
    });

    QSettings settings;
    restoreGeometry(settings.value("windowGeometry").toByteArray());
    ui->alwaysOnTop->setChecked(settings.value("alwaysOnTop").toBool());
    ui->mins->setText(settings.value("mins").toString());
    ui->secs->setText(settings.value("secs").toString());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_lastDragPos = event->globalPos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_lastDragPos.isNull())
        return;

    move(pos() + (event->globalPos() - m_lastDragPos));
    m_lastDragPos = event->globalPos();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_lastDragPos = QPoint();
}

void Widget::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("windowGeometry", saveGeometry());
    settings.setValue("alwaysOnTop", ui->alwaysOnTop->isChecked());
    settings.setValue("mins", ui->mins->text());
    settings.setValue("secs", ui->secs->text());

    QWidget::closeEvent(event);
}

void Widget::updateControls(bool isRunning)
{
    ui->mins->setEnabled(!isRunning);
    ui->secs->setEnabled(!isRunning);

    ui->startStop->setText(isRunning ? "Stop" : "Start");
}
