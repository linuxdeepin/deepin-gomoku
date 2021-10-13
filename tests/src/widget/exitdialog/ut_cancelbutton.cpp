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
#include "ut_cancelbutton.h"

#include <QMouseEvent>

TEST_F(UT_CancelButton, UT_CancelButton_mousePressEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_CalcelButton->mousePressEvent(&event);
    EXPECT_EQ(m_CalcelButton->buttonPressed, true)
            << "check calcelButton mousePressEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_mouseReleaseEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_CalcelButton->mouseReleaseEvent(&event);
    EXPECT_EQ(m_CalcelButton->buttonPressed, false)
            << "check calcelButton mouseReleaseEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_enterEvent)
{
    QEvent event(QEvent::Enter);
    m_CalcelButton->enterEvent(&event);
    EXPECT_EQ(m_CalcelButton->currentPixmap, m_CalcelButton->buttonHover)
            << "check calcelButton enterEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_leaveEvent)
{
    QEvent event(QEvent::Leave);
    m_CalcelButton->leaveEvent(&event);
    EXPECT_EQ(m_CalcelButton->currentPixmap, m_CalcelButton->buttonNormal)
            << "check calcelButton enterEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_CalcelButton->buttonPressed = true;
    m_CalcelButton->paintEvent(&event);
}
