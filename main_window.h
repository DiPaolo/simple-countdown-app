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

    QSound m_timeoutSound;
};
#endif // WIDGET_H
