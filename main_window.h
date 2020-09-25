#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPoint>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void updateControls(bool isRunning);

private:
    Ui::Widget *ui;

    const int m_maxMins = 59;
    const int m_maxSecs = 59;

    QPoint m_lastDragPos;
};
#endif // WIDGET_H
