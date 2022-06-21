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
#include "ut_exitbutton.h"

#include <QMouseEvent>

TEST_F(UT_ExitButton, UT_ExitButton_mousePressEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ExitButton->mousePressEvent(&event);
    EXPECT_EQ(m_ExitButton->buttonPressed,true)
            << "check exitButton mousePressEvent";
}

TEST_F(UT_ExitButton, UT_ExitButton_mouseReleaseEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ExitButton->mouseReleaseEvent(&event);
    EXPECT_EQ(m_ExitButton->buttonPressed,false)
            << "check exitButton mouseReleaseEvent";
}

TEST_F(UT_ExitButton, UT_ExitButton_enterEvent)
{
    QEvent event(QEvent::Enter);
    m_ExitButton->enterEvent(&event);
    EXPECT_EQ(m_ExitButton->currentPixmap, m_ExitButton->buttonHover)
            << "check exitButton enterEvent";
}

TEST_F(UT_ExitButton, UT_ExitButton_leaveEvent)
{
    QEvent event(QEvent::Enter);
    m_ExitButton->leaveEvent(&event);
    EXPECT_EQ(m_ExitButton->currentPixmap, m_ExitButton->buttonNormal)
            << "check exitButton enterLeave";
}

TEST_F(UT_ExitButton, UT_ExitButton_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ExitButton->buttonPressed = true;
    m_ExitButton->paintEvent(&event);
}
