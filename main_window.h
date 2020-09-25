#ifndef WIDGET_H
#define WIDGET_H

#include <QSound>
#include <QWidget>

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
    void updateControls(bool isRunning);

private:
    Ui::Widget *ui;

    const int m_maxMins = 59;
    const int m_maxSecs = 59;
};
#endif // WIDGET_H
