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
#include "ut_determinebutton.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>

TEST_F(UT_DetermineButton, UT_DetermineButton_mousePressEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_DetermineButton->mousePressEvent(&event);
    EXPECT_EQ(m_DetermineButton->buttonPressed, true)
            << "check determineButton mousePressEvent";
}

TEST_F(UT_DetermineButton, UT_DetermineButton_mouseReleaseEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_DetermineButton->mouseReleaseEvent(&event);
    EXPECT_EQ(m_DetermineButton->buttonPressed, false)
            << "check determineButton mouseReleaseEvent";
}

TEST_F(UT_DetermineButton, UT_DetermineButton_enterEvent)
{
    QEvent event(QEvent::Enter);
    m_DetermineButton->enterEvent(&event);
    EXPECT_EQ(m_DetermineButton->currentPixmap, m_DetermineButton->buttonHover)
            << "check determineButton enterEvent";
}

TEST_F(UT_DetermineButton, UT_DetermineButton_leaveEvent)
{
    QEvent event(QEvent::Enter);
    m_DetermineButton->leaveEvent(&event);
    EXPECT_EQ(m_DetermineButton->buttonPressed, false)
            << "check determineButton leaveEvent";
}

TEST_F(UT_DetermineButton, UT_DetermineButton_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_DetermineButton->buttonPressed = true;
    m_DetermineButton->paintEvent(&event);
}
