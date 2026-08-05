<!--
SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.

SPDX-License-Identifier: GPL-3.0-or-later
-->

# AT-SPI Completion Report for com.deepin.gomoku

## 扫描情况

### 扫描范围与方法
- **仓库**: com.deepin.gomoku (五子棋)
- **分支**: master
- **扫描方法**: 手动源码分析（代码结构扫描 + libclang AST 分析方式）
- **扫描时间**: 2026-08-05

### 仓库代码结构
com.deepin.gomoku 是一个基于 Qt6/DTK6 的五子棋游戏，主要 UI 层次结构：

```
GomokuMainWindow (DMainWindow)
├── DTitlebar
├── QGraphicsView (CheckerboardView)
│   └── CheckerboardScene (QGraphicsScene)
│       ├── CheckerboardItem (QGraphicsItem) — 棋盘背景
│       ├── PlayingScreen (QGraphicsItem) — 对局信息显示
│       ├── BTStartPause (ButtonItem → QGraphicsItem) — 开始/暂停按钮
│       ├── BTReplay (ButtonItem → QGraphicsItem) — 新游戏按钮
│       ├── BTMusicControl (ButtonItem → QGraphicsItem) — 音乐控制按钮
│       └── ChessItem[] (QGraphicsItem) — 15×15 棋子阵列
├── ExitDialog (QDialog) — 退出确认弹窗
│   ├── Closepopup (DWidget) — 关闭按钮
│   ├── ExitLabel (DLabel) — 提示文字
│   ├── CancelButton (QWidget) — 取消按钮
│   └── ExitButton (QWidget) — 退出按钮
├── Selectchess (QDialog) — 选择棋子颜色弹窗
│   ├── Closepopup (DWidget) — 关闭按钮
│   ├── Selectinfo (DLabel) — 提示文字
│   ├── Selectbutton[x2] (QPushButton) — 单选按钮
│   ├── Chessselected[x2] (DWidget) — 棋子展示
│   └── Determinebutton (DWidget) — 确定按钮
└── Resultpopup (DWidget) — 游戏结果弹窗
    ├── Closepopup (DWidget) — 关闭按钮
    ├── Resultinfo (DLabel) — 结果文字
    ├── Buttonrest (DWidget) — 休息一下按钮
    └── Buttonagain (DWidget) — 再来一局按钮
```

### AT-SPI 组件缺失清单

扫描发现整个项目中 **没有任何地方调用 `setAccessibleName()` 或 `setObjectName()`**，所有 Qt/DTK 控件均无 AT-SPI 可访问名称。具体缺失项：

| 序号 | 所属文件/类 | 控件 | 预期 accessibleName |
|------|-------------|------|-------------------|
| 1 | GomokuMainWindow | 主窗口 | GomokuMainWindow |
| 2 | GomokuMainWindow | 棋盘视图 (QGraphicsView) | CheckerboardView |
| 3 | ExitDialog | 退出弹窗本身 | ExitDialog |
| 4 | ExitDialog | 关闭按钮 | ExitDialogCloseButton |
| 5 | ExitDialog | 提示标签 | ExitDialogLabel |
| 6 | ExitDialog | 取消按钮 | ExitDialogCancelButton |
| 7 | ExitDialog | 退出按钮 | ExitDialogExitButton |
| 8 | Selectchess | 选棋弹窗本身 | SelectChessDialog |
| 9 | Selectchess | 关闭按钮 | SelectChessCloseButton |
| 10 | Selectchess | 提示标签 | SelectChessInfoLabel |
| 11 | Selectchess | 白色棋子单选按钮 | SelectChessWhiteRadioButton |
| 12 | Selectchess | 黑色棋子单选按钮 | SelectChessBlackRadioButton |
| 13 | Selectchess | 白色棋子展示 | SelectChessWhitePiece |
| 14 | Selectchess | 黑色棋子展示 | SelectChessBlackPiece |
| 15 | Selectchess | 确定按钮 | SelectChessOKButton |
| 16 | Resultpopup | 结果弹窗本身 | ResultPopup |
| 17 | Resultpopup | 关闭按钮 | ResultPopupCloseButton |
| 18 | Resultpopup | 结果标签 | ResultPopupLabel |
| 19 | Resultpopup | 休息一下按钮 | ResultPopupRestButton |
| 20 | Resultpopup | 再来一局按钮 | ResultPopupPlayAgainButton |

### 不适用 AT-SPI setAccessibleName 的项目

以下 QGraphicsItem 类不直接支持 setAccessibleName()（Qt QGraphicsItem 没有 QWidget 的 accessibility 机制）：

- CheckerboardItem（棋盘背景）
- PlayingScreen（对局详情画面）
- BTStartPause（开始/暂停按钮）
- BTReplay（新游戏按钮）
- BTMusicControl（音乐控制按钮）
- ChessItem（棋子）

这些需要自定义 QAccessibleInterface 实现，属于更高级的 AT-SPI 集成，暂未纳入本次补全范围。

## 补全详情

### 修改的文件和内容

| 文件 | 改动内容 |
|------|---------|
| `gomoku/src/widget/gomokumainwindow.cpp` | 添加 MainWindow 和 QGraphicsView 的 accessibleName |
| `gomoku/src/widget/exitdialog/exitdialog.cpp` | 添加 ExitDialog 及其子控件的 accessibleName |
| `gomoku/src/widget/exitdialog/exitlabel.cpp` | 添加退出提示标签的 accessibleName |
| `gomoku/src/widget/exitdialog/exitbutton.cpp` | 添加退出按钮的 accessibleName |
| `gomoku/src/widget/exitdialog/cancelbutton.cpp` | 添加取消按钮的 accessibleName |
| `gomoku/src/widget/selectchess/selectchess.cpp` | 添加 Selectchess 及其子控件的 accessibleName |
| `gomoku/src/widget/selectchess/selectinfo.cpp` | 添加选棋提示标签的 accessibleName |
| `gomoku/src/widget/selectchess/determinebutton.cpp` | 添加确定按钮的 accessibleName |
| `gomoku/src/widget/selectchess/selectbutton.cpp` | 添加单选按钮的 accessibleName |
| `gomoku/src/widget/selectchess/chessselected.cpp` | 添加棋子展示的 accessibleName |
| `gomoku/src/widget/resultpopup/resultpopup.cpp` | 添加 Resultpopup 及其子控件的 accessibleName |
| `gomoku/src/widget/resultpopup/closepopup.cpp` | 添加通用关闭按钮的 accessibleName |
| `gomoku/src/widget/resultpopup/resultinfo.cpp` | 添加结果标签的 accessibleName |
| `gomoku/src/widget/resultpopup/buttonagain.cpp` | 添加再来一局按钮的 accessibleName |
| `gomoku/src/widget/resultpopup/buttonrest.cpp` | 添加休息一下按钮的 accessibleName |

### 修改原则

1. 每个 QWidget/DWidget 子类在构造函数中添加 `setAccessibleName()` 调用
2. 对于容器类控件，同时包含子控件时，在子控件创建后立即设置
3. 命名规范：`<ParentWidget><Role>`, 如 `ExitDialogCloseButton`、`SelectChessOKButton`
4. 仅添加与 AT-SPI 相关的属性，不修改任何业务逻辑
5. 所有改动均通过本地编译验证

## 覆盖率

补全前：0%（没有任何 setAccessibleName/setObjectName 调用）
补全后：QWidget/DWidget 类覆盖率 ≥ 95%（所有交互式控件均设置了 accessibleName）
QGraphicsItem 类覆盖率：0%（等待 QAccessibleInterface 实现）

**总计**: 20 个 AT-SPI accessibleName 被添加，覆盖 15 个源文件。

## 构建验证

- ✅ CMake 配置成功
- ✅ 编译通过（Release 和 Debug 模式）
- ✅ 单元测试编译通过