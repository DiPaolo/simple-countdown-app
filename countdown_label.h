#ifndef COUNTDOWN_LABEL_H
#define COUNTDOWN_LABEL_H

#include <QLabel>
#include <QSoundEffect>
#include <QTime>
#include <QTimer>

namespace Ui {
class CountdownLabel;
}

class CountdownLabel : public QLabel
{
    Q_OBJECT

public:
    explicit CountdownLabel(QWidget *parent = nullptr);
    ~CountdownLabel();

    bool isRunning() const;

signals:
    void started();
    void finished(bool canceled);

private:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void start(const QTime &time);
    void stop(bool canceled = true);

private:
    Ui::CountdownLabel *ui;

    QTime m_timer;
    QTimer m_updateTimer;
    QSoundEffect m_timeoutSound;

    int m_requiredMsec = 0;
    int m_curSecLeft = 0;

    QColor m_curColor = Qt::black;
};

#endif // COUNTDOWN_LABEL_H
