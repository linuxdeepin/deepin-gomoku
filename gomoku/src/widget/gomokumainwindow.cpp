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
#include "selectchess/selectchess.h"
#include "resultpopup/resultpopup.h"

#include "exitdialog/exitdialog.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <DWidgetUtil>
#include <DWidget>
#include <DTitlebar>
#include <DFrame>
#include <QCloseEvent>
#include <DDialog>

GomokuMainWindow::GomokuMainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    setFixedSize(QSize(widgetWidth, widgetHeight));
    setContentsMargins(QMargins(0, 0, 0, 0));

    initUI();

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
    QPixmap backgroundImage = DHiDPIHelper::loadNxPixmap(":/resources/background.svg");
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
    wcheckerBoard->setFixedSize(this->width(), this->height() - titlebar()->height());
    wcheckerBoard->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    checkerboardScene = new CheckerboardScene(0, 0, this->width(), this->height() - titlebar()->height());
    wcheckerBoard->setScene(checkerboardScene);
    connect(checkerboardScene, &CheckerboardScene::signalSelectChessPopup, this, &GomokuMainWindow::slotSelectChessPopup);
    connect(checkerboardScene, &CheckerboardScene::signalPopupResult, this, &GomokuMainWindow::slotPopupResult);
    connect(checkerboardScene, &CheckerboardScene::signalReplayFunction, this, &GomokuMainWindow::slotReplayPopup);

    //视图阴影
    m_transparentFrame = new DFrame(this);
    m_transparentFrame->setAutoFillBackground(true);
    m_transparentFrame->hide();
    setCentralWidget(wcheckerBoard);
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

/**
 * @brief playFailMusic 播放失败音乐
 */
void GomokuMainWindow::playWinMusic()
{
    if (checkerboardScene->getMusicPlay())
        QSound::play(":/resources/music/win.wav");
}

/**
 * @brief playWinMusic 播放胜利音乐
 */
void GomokuMainWindow::playFailMusic()
{
    if (checkerboardScene->getMusicPlay())
        QSound::play(":/resources/music/fail.wav");
}

/**
 * @brief GomokuMainWindow::viewtransparentFrame 视图阴影
 */
void GomokuMainWindow::viewtransparentFrame()
{
    DPalette tframepa = m_transparentFrame->palette();
    QColor tColor = "#000000";
    tColor.setAlphaF(0.3);
    tframepa.setColor(DPalette::Background, tColor);
    m_transparentFrame->setPalette(tframepa);
    m_transparentFrame->setBackgroundRole(DPalette::Background);
    m_transparentFrame->resize(this->width(), this->height());
    m_transparentFrame->show();
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

/**
 * @brief GomokuMainWindow::slotSelectChessPopup 选择棋子弹窗
 */
void GomokuMainWindow::slotSelectChessPopup()
{
    Selectchess *selectChess = new Selectchess(this);
    selectChess->setSelectChess(userChessColor);
    connect(selectChess, &Selectchess::signalButtonOKClicked, this, [ = ] {
        userChessColor = selectChess->getSelsectChess();
        if (userChessColor == chess_white)
        {
            checkerboardScene->setSelectChess(chess_white, chess_black);
        } else if (userChessColor == chess_black)
        {
            checkerboardScene->setSelectChess(chess_black, chess_white);
        }
        checkerboardScene->selsectChessOK();
        checkerboardScene->startGame();
    });
    connect(checkerboardScene, &CheckerboardScene::signalCloSelectPopup, selectChess, &Selectchess::slotCloseSelectPopup);
    viewtransparentFrame();
    selectChess->selectChessShow();
    m_transparentFrame->hide();
    delete selectChess;
}

/**
 * @brief GomokuMainWindow::slotReplayPopup 重玩弹窗
 */
void GomokuMainWindow::slotReplayPopup()
{
    ExitDialog *exitDialog = new ExitDialog(this);
    viewtransparentFrame();
    exitDialog->exec();
    m_transparentFrame->hide();

    if (exitDialog->getResult() == BTType::BTExit) { //按钮状态是退出状态
        slotReplayFunction();
    } else {
        exitDialog->close();
    }
}

/**
 * @brief GomokuMainWindow::slotReplayFunction 重玩功能
 */
void GomokuMainWindow::slotReplayFunction()
{
    checkerboardScene->replayFunction();
    slotSelectChessPopup();
}

/**
 * @brief CheckerboardScene::slotPopupResult 游戏结束弹窗
 * @param result 结果
 */
void GomokuMainWindow::slotPopupResult(ChessResult result)
{
    //失败弹出,暂时效果
    Resultpopup *resultPopUp = new Resultpopup(this) ;
    connect(resultPopUp, &Resultpopup::signalGameAgain, this, &GomokuMainWindow::slotReplayFunction);
    connect(resultPopUp, &Resultpopup::signalHaveRest, this, [ = ] {
        checkerboardScene->setStartPauseStatus();
    });
    int userChessColor = checkerboardScene->getUserChessColor();
    //判断用户棋子颜色
    if (userChessColor == chess_black) {
        //判断是哪个颜色的棋子赢了
        if (result == black_win) {
            //胜利弹窗
            resultPopUp->setHasWin(true);
            //播放胜利音效
            playWinMusic();
        } else if (result == white_win || result == tie) {
            //失败或平局均为失败弹窗
            //失败弹窗
            resultPopUp->setHasWin(false);
            //播放失败音效
            playFailMusic();
        }
    } else if (userChessColor == chess_white) {
        if (result == black_win || result == tie) {
            resultPopUp->setHasWin(false);
            playFailMusic();
        } else if (result == white_win) {
            resultPopUp->setHasWin(true);
            playWinMusic();
        }
    }
    viewtransparentFrame();
    resultPopUp->popupShow();
    m_transparentFrame->hide();
    delete resultPopUp;
    resultPopUp = nullptr;
}

/**
 * @brief GomokuMainWindow::changeEvent
 */
void GomokuMainWindow::changeEvent(QEvent *event)
{
    if (event->type() != QEvent::WindowStateChange) return;
    if (this->windowState() == Qt::WindowMinimized) {
        checkerboardScene->stopGAme();
    }
    DMainWindow::changeEvent(event);
}

/**
 * @brief GomokuMainWindow::closeEvent 关闭事件
 * @param event
 */
void GomokuMainWindow::closeEvent(QCloseEvent *event)
{
    ExitDialog *exitDialog = new ExitDialog(this);
    viewtransparentFrame();
    exitDialog->exec();
    m_transparentFrame->hide();

    if (exitDialog->getResult() == BTType::BTExit) { //按钮状态是退出状态
        event->accept(); //事件接受
    } else {
        event->ignore(); //事件忽略
    }
}
