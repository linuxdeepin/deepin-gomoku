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
#include "ut_playingscreen.h"

#include <QPainter>

TEST_F(UT_PlayingScreen, UT_PlayingScreen_setCurrentChessColor)
{
    m_PlayingScreen->setCurrentChessColor(false, chess_black);
    EXPECT_EQ(m_PlayingScreen->AIPlayer, false)
            << "check playingScreen setCurrentChessColor";
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_setGameOverStatus)
{
    m_PlayingScreen->setGameOverStatus();
    EXPECT_EQ(m_PlayingScreen->gameOverStatus, true)
            << "check playingScreen setGameOverStatus";
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_boundingRect)
{
    m_PlayingScreen->boundingRect();
    EXPECT_EQ(m_PlayingScreen->sceneWidth, 300)
            << "check playingScreen boundingRect";
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_paint1)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_PlayingScreen->gamePlaying = false;
    m_PlayingScreen->paint(&painter, option, widget);
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_paint2)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_PlayingScreen->gamePlaying = true;
    m_PlayingScreen->gameOverStatus = true;
    m_PlayingScreen->AIPlayer = true;
    m_PlayingScreen->currentChessColro = chess_black;
    m_PlayingScreen->paint(&painter, option, widget);
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_paint3)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_PlayingScreen->gamePlaying = true;
    m_PlayingScreen->gameOverStatus = false;
    m_PlayingScreen->AIPlayer = false;
    m_PlayingScreen->currentChessColro = chess_white;
    m_PlayingScreen->paint(&painter, option, widget);
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_slotStartGame)
{
    m_PlayingScreen->slotStartGame();
    EXPECT_EQ(m_PlayingScreen->gamePlaying, true)
            << "check playingScreen slotStartGame";
}

TEST_F(UT_PlayingScreen, UT_PlayingScreen_slotNewGame)
{
    m_PlayingScreen->slotNewGame();
    EXPECT_EQ(m_PlayingScreen->gamePlaying, false)
            << "check playingScreen slotNewGame";
}
