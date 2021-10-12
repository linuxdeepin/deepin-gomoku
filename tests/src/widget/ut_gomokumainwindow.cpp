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
#include "ut_gomokumainwindow.h"

#include <stub.h>

#include <DGuiApplicationHelper>
#include <DWidget>
#include <DTitlebar>

int UTPopupExec(QEventLoop::ProcessEventsFlags flag)
{
    Q_UNUSED(flag);
    return 0;
}

DGuiApplicationHelper::ColorType UT_MainWindow_themeType_001()
{
    return DGuiApplicationHelper::DarkType;
}

DGuiApplicationHelper::ColorType UT_MainWindow_themeType_002()
{
    return DGuiApplicationHelper::LightType;
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_handleQuit)
{
    m_mainwindow->handleQuit();
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_initUI)
{
    m_mainwindow->initUI();
    EXPECT_EQ(m_mainwindow->windowFlags(), m_mainwindow->windowFlags() & ~Qt::WindowMaximizeButtonHint)
            << "check the status after UT_MainWindow_initUI()";
    EXPECT_EQ(m_mainwindow->size(), QSize(widgetWidth, widgetHeight))
            << "check the status after UT_MainWindow_initUI()";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_initCompositingStatus)
{
    m_mainwindow->initCompositingStatus();
    EXPECT_EQ(m_mainwindow->compositingStatus, true) << "check DBus connect status after initCompositingStatus";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_paintTitleBar_themeType_001)
{
    Stub stub;
    stub.set(ADDR(DGuiApplicationHelper, themeType), UT_MainWindow_themeType_001);
    m_mainwindow->paintTitleBar(m_mainwindow->titlebar());
    EXPECT_NE(m_mainwindow->mTitleBar, nullptr) << "check the status after UT_MainWindow_paintTitleBar_themeType_001";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_paintTitleBar_themeType_002)
{
    Stub stub;
    stub.set(ADDR(DGuiApplicationHelper, themeType), UT_MainWindow_themeType_002);
    m_mainwindow->paintTitleBar(m_mainwindow->titlebar());
    EXPECT_NE(m_mainwindow->mTitleBar, nullptr) << "check the status after UT_MainWindow_paintTitleBar_themeType_001";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_playWinMusic_false)
{
    m_mainwindow->checkerboardScene->musicControlStatus = false;
    m_mainwindow->playWinMusic();
    EXPECT_EQ(m_mainwindow->checkerboardScene->musicControlStatus, false)
            << "check the musicControlStatus-false on win";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_playWinMusic_true)
{
    m_mainwindow->checkerboardScene->musicControlStatus = true;
    m_mainwindow->playWinMusic();
    EXPECT_EQ(m_mainwindow->checkerboardScene->musicControlStatus, true)
            << "check the musicControlStatus-true on win";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_playFailMusic_false)
{
    m_mainwindow->checkerboardScene->musicControlStatus = false;
    m_mainwindow->playFailMusic();
    EXPECT_EQ(m_mainwindow->checkerboardScene->musicControlStatus, false)
            << "check the musicControlStatus-false on fail";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_playFailMusic_true)
{
    m_mainwindow->checkerboardScene->musicControlStatus = true;
    m_mainwindow->playFailMusic();
    EXPECT_EQ(m_mainwindow->checkerboardScene->musicControlStatus, true)
            << "check the musicControlStatus-true on fail";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_viewtransparentFrame)
{
    m_mainwindow->viewtransparentFrame();
    EXPECT_EQ(m_mainwindow->m_transparentFrame->isHidden(), false)
            << "check the transparentFrame'size has mainwindow'size";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_eventFilter)
{
    QEvent event(QEvent::Paint);
    bool res = m_mainwindow->eventFilter(m_mainwindow->titlebar(), &event);
    EXPECT_EQ(res, true) << "check the eventFilter has paintevent";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotSelectChessPopup)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->slotSelectChessPopup();
    EXPECT_EQ(m_mainwindow->m_selectChess, nullptr)
            << "check selectChess popup";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotReplayPopup)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->slotReplayPopup();
    EXPECT_EQ(m_mainwindow->m_transparentFrame->isHidden(), true)
            << "check replay popup";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotReplayFunction)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->slotReplayFunction();
    EXPECT_EQ(m_mainwindow->m_transparentFrame->isHidden(), true)
            << "check replay function";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotPopupResult_balck_win)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->checkerboardScene->userChessColor = chess_black;
    m_mainwindow->slotPopupResult(ChessResult::black_win);
    EXPECT_EQ(m_mainwindow->checkerboardScene->getUserChessColor(), chess_black)
            << "check balck win result popup";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotPopupResult_white_win)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->checkerboardScene->userChessColor = chess_black;
    m_mainwindow->slotPopupResult(ChessResult::white_win);
    EXPECT_EQ(m_mainwindow->checkerboardScene->getUserChessColor(), chess_black)
            << "check white win result popup";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotPopupResult_white_win1)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->checkerboardScene->userChessColor = chess_white;
    m_mainwindow->slotPopupResult(ChessResult::white_win);
    EXPECT_EQ(m_mainwindow->checkerboardScene->getUserChessColor(), chess_white)
            << "check white win result popup";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotPopupResult_black_win1)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    m_mainwindow->checkerboardScene->userChessColor = chess_white;
    m_mainwindow->slotPopupResult(ChessResult::black_win);
    EXPECT_EQ(m_mainwindow->checkerboardScene->getUserChessColor(), chess_white)
            << "check black win result popup";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotCompositingChanged_false)
{
    m_mainwindow->slotCompositingChanged(false);
    EXPECT_EQ(m_mainwindow->compositingStatus, false)
            << "check the comopsitingStatus";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_slotCompositingChanged_true)
{
    m_mainwindow->slotCompositingChanged(true);
    EXPECT_EQ(m_mainwindow->compositingStatus, true)
            << "check the comopsitingStatus";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_changeEvent)
{
    QEvent event(QEvent::WindowStateChange);
    m_mainwindow->setWindowState(Qt::WindowMinimized);
    m_mainwindow->changeEvent(&event);
    EXPECT_EQ(m_mainwindow->windowState(), Qt::WindowMinimized)
            << "check window changeEvent";
}

TEST_F(UT_GomokuMainWindow, UT_MainWindow_closeEvent)
{
    Stub stub;
    stub.set(ADDR(QEventLoop, exec), UTPopupExec);
    QCloseEvent event;
    m_mainwindow->closeEvent(&event);
    EXPECT_EQ(m_mainwindow->m_transparentFrame->isHidden(), true)
            << "check mainwindow closeEvent";
}

