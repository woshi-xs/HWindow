# QFrame分割线设置

在 Qt（Qt Designer / .ui 文件）中，分割线本质上是一个经过特定属性配置的 `QFrame` 控件。

## 1. 核心属性对比表

| 属性项 (Property)    | 垂直分割线 (Vertical Line)          | 水平分割线 (Horizontal Line)        | 作用说明                           |
|:----------------- |:------------------------------ |:------------------------------ |:------------------------------ |
| **`frameShape`**  | `QFrame::Shape::VLine`         | `QFrame::Shape::HLine`         | **核心属性**，决定线条的方向               |
| **`frameShadow`** | `QFrame::Shadow::Plain`        | `QFrame::Shadow::Plain`        | 纯色扁平线，无 3D 凹凸效果（匹配 `.ui` 实际设置） |
| **`minimumSize`** | `width: 1`, `height: 0`        | `width: 0`, `height: 1`        | 限制固定方向的最小尺寸（如细线设为 1px）         |
| **`maximumSize`** | `width: 1`, `height: 16777215` | `width: 16777215`, `height: 1` | 固定厚度为 1px，另一方向允许无限拉伸扩展         |
| **`styleSheet`**  | `color: palette(mid);`       | `color: palette(mid);`       | 用 `QPalette::Mid` 画线，随系统深浅色变化 |

> **注意：** 对于 `QFrame` 的线条形状（`HLine`/`VLine`），在样式表中使用 **`color`** 属性来改变线条颜色，而不是 `background-color`。`palette(mid)` 引用调色板角色，不要写成固定的 `rgb(...)`。1 像素的 `Plain` 线放不下 `Raised`/`Sunken` 的明暗双边。

## 2. C++ 代码动态创建示例

```cpp
// 1. 创建水平分割线
QFrame *hLine = new QFrame(this);
hLine->setFrameShape(QFrame::HLine);
hLine->setFrameShadow(QFrame::Plain);
hLine->setFixedHeight(1);
hLine->setStyleSheet("color: palette(mid);");

// 2. 创建垂直分割线（对应你的 ui 实际配置）
QFrame *vLine = new QFrame(this);
vLine->setFrameShape(QFrame::VLine);
vLine->setFrameShadow(QFrame::Plain);
vLine->setFixedWidth(1);
vLine->setStyleSheet("color: palette(mid);");
```