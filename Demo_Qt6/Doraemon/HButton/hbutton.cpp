#include "hbutton.h"
#include <QPainter>
#include <QPainterPath>

HButton::HButton(QWidget *parent)
    : QAbstractButton(parent)
{
    this->setCheckable(true);
    this->setIconSize(QSize(20, 20));
    // 开启鼠标悬停检测，否则 underMouse() 不准
    this->setAttribute(Qt::WA_Hover, true);
}


// 把两张 SVG 塞进同一个 QIcon
void HButton::setIcons(const QString &normalPath, const QString &checkedPath)
{
    QIcon dualIcon;
    // 贴上 QIcon::Off 标签（没选中时用这张）
    dualIcon.addFile(normalPath, QSize(), QIcon::Normal, QIcon::Off);

    // 贴上 QIcon::On 标签（选中时用这张）
    dualIcon.addFile(checkedPath, QSize(), QIcon::Normal, QIcon::On);

    // 交给父类保管
    this->setIcon(dualIcon);
}

void HButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 画背景
    QColor bgColor(Qt::transparent);
    if (!isEnabled()) {
        bgColor = QColor(0, 0, 0, 20);// 禁用
    } else if (isDown()) {
        bgColor = QColor(213, 213, 213);// 按下
    } else if (isChecked()) {
        bgColor = QColor(0, 0, 0,0);// 选中
    } else if (underMouse()) {
        bgColor = QColor(225, 225, 225);// 仅悬停
    }

    p.setBrush(bgColor);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect(), roundRadius, roundRadius);

    //设置圆角裁剪区域
    QPainterPath path;
    path.addRoundedRect(rect(), roundRadius, roundRadius);
    p.setClipPath(path);

    // 图标绘制
    if (!icon().isNull()) {
        QRect iconRect(0, 0, iconSize().width(), iconSize().height());
        iconRect.moveCenter(rect().center());

        // 告诉 QIcon：当前按钮是可用还是禁用
        QIcon::Mode mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;

        // 告诉 QIcon：当前按钮是选中 (On) 还是没选中 (Off)
        QIcon::State state = isChecked() ? QIcon::On : QIcon::Off;

        // QIcon 会根据传的 state 自动翻出对应的 SVG 画上去
        icon().paint(&p, iconRect, Qt::AlignCenter, mode, state);
    }
}
