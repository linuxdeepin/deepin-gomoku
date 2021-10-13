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
#include "ut_selectbutton.h"

#include <QEvent>
#include <QPaintEvent>

TEST_F(UT_SelectButton, UT_SelectButton_enterEvent)
{
    QEvent event(QEvent::Enter);
    m_SelectButton->enterEvent(&event);
    EXPECT_EQ(m_SelectButton->currentStatus, m_SelectButton->selectHover)
            << "check selectButton enterEvent";
}

TEST_F(UT_SelectButton, UT_SelectButton_leaveEvent1)
{
    QEvent event(QEvent::Leave);
    m_SelectButton->pressStatus = true;
    m_SelectButton->leaveEvent(&event);
    EXPECT_EQ(m_SelectButton->currentStatus, m_SelectButton->selectPress)
            << "check selectButton leaveEvent";
}

TEST_F(UT_SelectButton, UT_SelectButton_leaveEvent2)
{
    QEvent event(QEvent::Leave);
    m_SelectButton->pressStatus = false;
    m_SelectButton->leaveEvent(&event);
    EXPECT_EQ(m_SelectButton->currentStatus, m_SelectButton->selectNormal)
            << "check selectButton leaveEvent";
}

TEST_F(UT_SelectButton, UT_SelectButton_paintEvent1)
{
    QRect rect;
    m_SelectButton->setChecked(true);
    QPaintEvent event(rect);
    m_SelectButton->paintEvent(&event);
}

TEST_F(UT_SelectButton, UT_SelectButton_paintEvent2)
{
    QRect rect;
    m_SelectButton->setChecked(false);
    QPaintEvent event(rect);
    m_SelectButton->paintEvent(&event);
}
