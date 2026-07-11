#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringList>
#include <QButtonGroup>

#include "HWindow/hwindow.h"
#include "HButton/hbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public HWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void initWindow();

private:
    Ui::Widget *ui;

    QButtonGroup *btnGroup;
    QList<HButton*> sideButtons; // 把UI里的按钮装进来，方便循环遍历

    QStringList btnsName;
    QStringList btnImgName;
};
#endif // WIDGET_H
