#include "widget.h"
#include "./ui_widget.h"
#include <QIcon>

Widget::Widget(QWidget *parent)
    : HWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 名字列表
    this->btnsName = {
        "主界面", "好友", "音乐", "占位", "占位", "占位", "占位", "占位", "菜单"
    };

    // 图标路径模板
    this->btnImgName = {
        ":/images/images/chat-%1.svg",
        ":/images/images/group-%1.svg",
        ":/images/images/disc-%1.svg",
        ":/images/images/bell-%1.svg",
        ":/images/images/bell-%1.svg",
        ":/images/images/bell-%1.svg",
        ":/images/images/bell-%1.svg",
        ":/images/images/bell-%1.svg",
        ":/images/images/menu-%1.svg"
    };

    this->initWindow();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWindow()
{
    // 头像设置,头像不需要悬停/选中状态，直接传一个Icon进去就行
    // ui->avatarHButton->setMinimumSize(35,35);
    // ui->avatarHButton->setMaximumSize(35,35);
    ui->avatarHButton->setIcon(QIcon(":/images/images/cat.jpg"));
    ui->avatarHButton->setIconSize(ui->avatarHButton->size());// 自动填满

    // 2. 初始化原生按钮组
    btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true); // 开启互斥：点亮一个，其他自动熄灭

    // 将散装的按钮放进一个 List，严格和 btnsName / btnImgName 顺序对应！
    sideButtons = {
        ui->chatHButton,
        ui->buddyHButton,
        ui->musicHButton,
        ui->HButon_2,
        ui->HButon_3,
        ui->HButon_4,
        ui->HButon_5,
        ui->HButon_6,
        ui->menuHButton
    };

    // 3. 循环初始化所有按钮
    for(int i = 0; i < sideButtons.count(); i++){
        HButton *btn = sideButtons[i];

        // 拼装双态路径
        // 注意参数顺序：一般是 "line" 是正常状态，"fill" 是点击后的实心状态
        QString normalPath = this->btnImgName[i].arg("line");
        QString checkedPath = this->btnImgName[i].arg("fill");

        btn->setIcons(normalPath, checkedPath);
        btn->setToolTip(this->btnsName[i]);

        // 【最精髓的一步】把按钮加进组，并赋予它一个 ID (0, 1, 2...)
        btnGroup->addButton(btn, i);
    }

    // // 4. 一键打通页面切换逻辑！
    // // 监听按钮组的点击信号，直接拿到刚刚赋予的 ID，丢给 StackedWidget
    // connect(btnGroup, &QButtonGroup::idClicked, this, [=](int id){
    //     if (ui->stackedWidget && id >= 0 && id < ui->stackedWidget->count()) {
    //         ui->stackedWidget->setCurrentIndex(id);
    //     }
    // });

    // // 5. 初始默认选中第一个 (主界面)
    // if (!sideButtons.isEmpty()) {
    //     sideButtons.first()->setChecked(true);
    //     if(ui->stackedWidget) {
    //         ui->stackedWidget->setCurrentIndex(0);
    //     }
    // }
}
