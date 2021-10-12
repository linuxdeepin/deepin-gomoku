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
#include "ut_btmusiccontrol.h"

TEST_F(UT_BTMusicControl, UT_BTMusicControl_boundingRect)
{
    m_ButtonMusicControl->boundingRect();
    EXPECT_EQ(m_ButtonMusicControl->boundingRect().width(), 204)
            << "check btreplay boundingRect";
}

TEST_F(UT_BTMusicControl, UT_BTMusicControl_paint1)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonMusicControl->mouseReleased = true;
    m_ButtonMusicControl->pressStatus = true;
    m_ButtonMusicControl->paint(&painter, option, widget);
}

TEST_F(UT_BTMusicControl, UT_BTMusicControl_paint2)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_ButtonMusicControl->mouseReleased = false;
    m_ButtonMusicControl->pressStatus = false;
    m_ButtonMusicControl->paint(&painter, option, widget);
}

TEST_F(UT_BTMusicControl, UT_BTMusicControl_buttonFunction)
{
    m_ButtonMusicControl->buttonFunction();
}

TEST_F(UT_BTMusicControl, UT_BTMusicControl_setNotFirstGame)
{
    m_ButtonMusicControl->setNotFirstGame();
}
