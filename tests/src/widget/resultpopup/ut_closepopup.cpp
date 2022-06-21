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
#include "ut_closepopup.h"
#include <QMouseEvent>

TEST_F(UT_ClosePopup, UT_ClosePopup_mousePressEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ClosePopup->mousePressEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonPress)
            << "check closePopup mousePressEvent";
}

TEST_F(UT_ClosePopup, UT_ClosePopup_mouseReleaseEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ClosePopup->mouseReleaseEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonNormal)
            << "check closePopup mouseReleaseEvent";
}

TEST_F(UT_ClosePopup, UT_ClosePopup_enterEvent)
{
    QEvent event(QEvent::Enter);
    m_ClosePopup->enterEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonHover)
            << "check closePopup enterEvent";
}

TEST_F(UT_ClosePopup, UT_ClosePopup_leaveEvent)
{
    QEvent event(QEvent::Leave);
    m_ClosePopup->leaveEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonNormal)
            << "check closePopup leaveEvent";
}


TEST_F(UT_ClosePopup, UT_ClosePopup_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ClosePopup->paintEvent(&event);
}
