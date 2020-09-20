#include "countdown_label.h"
#include "ui_countdown_label.h"

#include <QDebug>
#include <QChar>
#include <QPainter>
#include <QResizeEvent>

CountdownLabel::CountdownLabel(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CountdownLabel)
{
    ui->setupUi(this);

    connect(&m_updateTimer, &QTimer::timeout, [this]() {
        m_curSecLeft = std::max(m_requiredMsec - m_timer.elapsed(), 0) / 1000;

        if (isRunning() && m_curSecLeft <= 15)
            m_curColor = Qt::red;

        if (isRunning() && m_curSecLeft <= 10)
            QApplication::beep();

        update();

        if (isRunning() && m_curSecLeft <= 0)
            stop(false);
    });

    update();
}

CountdownLabel::~CountdownLabel()
{
    delete ui;
}

bool CountdownLabel::isRunning() const
{
    return (m_requiredMsec > m_timer.elapsed());
}

void CountdownLabel::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    const int timeLeftSecs = m_curSecLeft;
    const int timeLeftMins = timeLeftSecs / 60;
    const auto str = QString("%1:%2").arg(timeLeftMins, 2, 10, QChar('0')).arg((int)(timeLeftSecs % 60), 2, 10, QChar('0'));
//    qDebug() << timeLeftSecs << " is running " << isRunning();

    QRect r(event->rect());

    p.setPen(m_curColor);
    QFontMetrics fm(p.font());
//    const double scaleFactor = fm.horizontalAdvance("0") / (double)fm.height();
    qreal sx = (double)r.width() / fm.horizontalAdvance(str);
    qreal sy = (double)r.height() / fm.height();
//    qreal sy = sx / scaleFactor;
//    p.save();
    p.translate(r.center());
    p.scale(sx, sy);
    p.translate(-r.center());
    p.drawText(r, str, Qt::AlignHCenter | Qt::AlignVCenter);

}

void CountdownLabel::start(const QTime &time)
{
    m_curColor = Qt::black;

    m_requiredMsec = (time.minute() * 60 + time.second()) * 1000;
    update();
    m_timer.start();
    m_updateTimer.start(1000);
    emit started();
}

void CountdownLabel::stop(bool canceled)
{
    m_updateTimer.stop();
    m_timer = QTime();
    m_requiredMsec = 0;
    emit finished(canceled);
}
