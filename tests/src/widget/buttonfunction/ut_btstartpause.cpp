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
#include "ut_btstartpause.h"

TEST_F(UT_BTStartPause, UT_BTStartPause_setButtonStatus)
{
    m_ButtonStartPause->firstStartGame = false;
    m_ButtonStartPause->setButtonStatus(true);
    EXPECT_EQ(m_ButtonStartPause->mouseReleased, true)
            << "check btstartpause setButtonStatus";
}

TEST_F(UT_BTStartPause, UT_BTStartPause_setGameOverStatus)
{
    m_ButtonStartPause->gameOverStatus = false;
    m_ButtonStartPause->setGameOverStatus(false);
    EXPECT_EQ(m_ButtonStartPause->gameOverStatus, false)
            << "check btstartpause setGameOverStatus";
}

TEST_F(UT_BTStartPause, UT_BTStartPause_getButtonStatus)
{
    m_ButtonStartPause->mouseReleased = false;
    bool res = m_ButtonStartPause->getButtonStatus();
    EXPECT_EQ(res, false)
            << "check btstartpause getButtonStatus";
}

TEST_F(UT_BTStartPause, UT_BTStartPause_setNotFirstGame)
{
    m_ButtonStartPause->posHeight = 1.0;
    m_ButtonStartPause->setNotFirstGame();
    EXPECT_EQ(m_ButtonStartPause->firstStartGame, false)
            << "check btstartpause setNorFirstGame";
}

TEST_F(UT_BTStartPause, UT_BTStartPause_boundingRect)
{
    m_ButtonStartPause->boundingRect();
    EXPECT_EQ(m_ButtonStartPause->boundingRect().width(), 204)
            << "check btreplay boundingRect";
}

TEST_F(UT_BTStartPause, UT_BTStartPause_paint1)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonStartPause->gameOverStatus = true;
    m_ButtonStartPause->paint(&painter, option, widget);
}

TEST_F(UT_BTStartPause, UT_BTStartPause_paint2)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonStartPause->gameOverStatus = false;
    m_ButtonStartPause->firstStartGame = true;
    m_ButtonStartPause->pressStatus = true;
    m_ButtonStartPause->paint(&painter, option, widget);
}

TEST_F(UT_BTStartPause, UT_BTStartPause_paint3)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonStartPause->gameOverStatus = false;
    m_ButtonStartPause->firstStartGame = false;
    m_ButtonStartPause->pressStatus = false;
    m_ButtonStartPause->mouseReleased = true;
    m_ButtonStartPause->paint(&painter, option, widget);
}

TEST_F(UT_BTStartPause, UT_BTStartPause_paint4)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonStartPause->gameOverStatus = false;
    m_ButtonStartPause->firstStartGame = false;
    m_ButtonStartPause->pressStatus = false;
    m_ButtonStartPause->mouseReleased = false;
    m_ButtonStartPause->paint(&painter, option, widget);
}

TEST_F(UT_BTStartPause, UT_BTStartPause_buttonFunction)
{
    m_ButtonStartPause->firstStartGame = true;
}

TEST_F(UT_BTStartPause, UT_BTStartPause_buttonFunction1)
{
    m_ButtonStartPause->firstStartGame = false;
    m_ButtonStartPause->mouseReleased = true;
}

TEST_F(UT_BTStartPause, UT_BTStartPause_buttonFunction2)
{
    m_ButtonStartPause->firstStartGame = false;
    m_ButtonStartPause->mouseReleased = false;
}

TEST_F(UT_BTStartPause, UT_BTStartPause_getPosHeighe)
{
    m_ButtonStartPause->posHeight = 1.0;
    qreal res = m_ButtonStartPause->getPosHeight();
    EXPECT_EQ(res, 1.0)
            << "check btreplay getPosHeight";
}

TEST_F(UT_BTStartPause, UT_BTStartPause_getFirstGamePosHeight)
{
    const  qreal res = m_ButtonStartPause->getFirstGamePosHeight();
    EXPECT_EQ(res, 0.2314)
            << "check btreplay getFirstGamePosHeight";
}

