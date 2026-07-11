#ifndef HBUTTON_H
#define HBUTTON_H

#include <QAbstractButton>

class HButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit HButton(QWidget *parent = nullptr);

    // 双态图标，帮我们把两张图塞进同一个 QIcon 里
    void setIcons(const QString &normalPath, const QString &checkedPath);

    void setRoundRadius(unsigned int radius) { this->roundRadius = radius; update(); }

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    unsigned int roundRadius = 4;
};

#endif // HBUTTON_H
