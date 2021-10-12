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
#include "ut_btreplay.h"

TEST_F(UT_BTReplay, UT_BTReplay_boundingRect)
{
    m_ButtonReplay->boundingRect();
    EXPECT_EQ(m_ButtonReplay->boundingRect().width(), 204)
            << "check btreplay boundingRect";
}

TEST_F(UT_BTReplay, UT_BTReplay_paint1)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonReplay->firstStartGame = true;
    m_ButtonReplay->paint(&painter, option, widget);
}

TEST_F(UT_BTReplay, UT_BTReplay_paint2)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonReplay->firstStartGame = false;
    m_ButtonReplay->pressStatus = true;
    m_ButtonReplay->paint(&painter, option, widget);
}

TEST_F(UT_BTReplay, UT_BTReplay_setButtonState)
{
    m_ButtonReplay->setButtonState(true);
    EXPECT_EQ(m_ButtonReplay->firstStartGame, true)
            << "check btreplay setbuttonState";
}

TEST_F(UT_BTReplay, UT_BTReplay_buttonFunction)
{
    m_ButtonReplay->firstStartGame = false;
    m_ButtonReplay->buttonFunction();
}

TEST_F(UT_BTReplay, UT_BTReplay_setNotFirstGame)
{
    m_ButtonReplay->posHeight = 1.0;
    m_ButtonReplay->setNotFirstGame();
    EXPECT_EQ(m_ButtonReplay->firstStartGame, false)
            << "check btreplay setNotFirstGame";
}

TEST_F(UT_BTReplay, UT_BTReplay_getPosHeighe)
{
    m_ButtonReplay->posHeight = 1.0;
    qreal res = m_ButtonReplay->getPosHeight();
    EXPECT_EQ(res, 1.0)
            << "check btreplay getPosHeight";
}

TEST_F(UT_BTReplay, UT_BTReplay_getFirstGamePosHeight)
{
    const qreal res = m_ButtonReplay->getFirstGamePosHeight();
    EXPECT_EQ(res, 0.3425)
            << "check btreplay getFirstGamePosHeight";
}
