/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * This program is free software: you can redistribute it and/or modify
   * it under the terms of the GNU General Public License as published by
   * the Free Software Foundation, either version 3 of the License, or
   * any later version.
   *
   * This program is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   * GNU General Public License for more details.
   *
   * You should have received a copy of the GNU General Public License
   * along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */
#include "gomokumainwindow.h"
#include "constants.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <DWidgetUtil>
#include <DWidget>
#include <DTitlebar>
#include <DFrame>
#include <DDialog>

GomokuMainWindow::GomokuMainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    setContentsMargins(QMargins(0, 0, 0, 0));

    setWindowTitle(tr("deepin-gomoku"));

    initUI();
    initGame();

    Dtk::Widget::moveToCenter(this);
}

GomokuMainWindow::~GomokuMainWindow()
{
    delete mTitleBar;
}

//初始化界面
void GomokuMainWindow::initUI()
{
    //background
    QPixmap backgroundImage(":/resources/background.svg");
    DPalette palette;
    palette.setColor(DPalette::Background, Qt::transparent);
    palette.setBrush(QPalette::Background, QBrush(backgroundImage));
    setPalette(palette);

    mTitleBar = titlebar();
    mTitleBar->setFrameShape(DFrame::NoFrame);
    mTitleBar->installEventFilter(this);
//    //目前系统中没有游戏的图标，先这样设置
    mTitleBar->setIcon(QIcon(":/resources/logo.svg"));
    mTitleBar->setAutoFillBackground(true);
    mTitleBar->setAttribute(Qt::WA_TranslucentBackground);
    mTitleBar->setBackgroundTransparent(true);

    QGraphicsView *wcheckerBoard = new QGraphicsView(this);
    wcheckerBoard->setStyleSheet("background: transparent;border:0px");
    wcheckerBoard->setWindowFlags(Qt::FramelessWindowHint);
    wcheckerBoard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wcheckerBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wcheckerBoard->setFixedSize(widgetWidth, widgetHeight - titlebar()->height());
    wcheckerBoard->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    checkerboardScene = new CheckerboardScene();
    checkerboardScene->setSceneRect(0, 0, widgetWidth, widgetHeight - titlebar()->height());
    wcheckerBoard->setScene(checkerboardScene);

    setCentralWidget(wcheckerBoard);
    setFixedSize(QSize(widgetWidth, widgetHeight));
}

//初始化游戏
void GomokuMainWindow::initGame()
{
    GameControl *gameControl = new GameControl(chess_black, chess_white);
    checkerboardScene->setchessType(chess_white);//设置玩家棋子颜色
    connect(checkerboardScene, &CheckerboardScene::signalCurrentPoint, gameControl, &GameControl::chessCompleted);//更新棋盘数组
    connect(checkerboardScene, &CheckerboardScene::signalRestGame, gameControl, &GameControl::resetGame);//重置游戏
    connect(gameControl, &GameControl::AIPlayChess, checkerboardScene, &CheckerboardScene::slotPaintAIChess);//绘制AI落子
    connect(gameControl, &GameControl::isAIPlaying, checkerboardScene, &CheckerboardScene::signalIsAIPlaying);//通知棋子,当前旗手
    connect(gameControl, &GameControl::gameOver, checkerboardScene, &CheckerboardScene::signalGameOver);//游戏结束
    connect(gameControl, &GameControl::gameOver, this, [] {
        //失败弹出,暂时效果
        DDialog promptDialog;
        promptDialog.addButton(tr("OK", "button"));
        promptDialog.setIcon(QIcon::fromTheme("uss_warning"));
        promptDialog.setMessage("game over");
        promptDialog.exec();
    });
    gameControl->startGame();//开始游戏
}

//绘制titlebar背景
void GomokuMainWindow::paintTitleBar(QWidget *titlebar)
{
    DGuiApplicationHelper::ColorType themtype = DGuiApplicationHelper::instance()->themeType();
    QColor broundColor;
    if (themtype == DGuiApplicationHelper::ColorType::DarkType) {
        broundColor = titlebar->palette().color(QPalette::Normal, QPalette::Dark);
    } else if (themtype == DGuiApplicationHelper::ColorType::LightType) {
        broundColor = titlebar->palette().color(QPalette::Normal, QPalette::Light);
    }
    QPainter painter(titlebar);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    broundColor.setAlphaF(0.5);
    painter.setPen(Qt::NoPen);
    painter.setBrush(broundColor);
    painter.drawRect(titlebar->rect());
    painter.restore();
}

//过滤titlebar绘制事件
bool GomokuMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == mTitleBar) {
        if (event->type() == QEvent::Paint) {
            paintTitleBar(mTitleBar);
        }
    }
    return DMainWindow::eventFilter(watched, event);
}
