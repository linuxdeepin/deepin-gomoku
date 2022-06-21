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
#include "ut_resultpopup.h"
#include <DHiDPIHelper>
#include <QPaintEvent>

TEST_F(UT_ResultPopup, UT_ResultPopup_initUI)
{
    m_ResulePopup->initUI();
}

TEST_F(UT_ResultPopup, UT_ResultPopup_initBackgroundPix1)
{
    m_ResulePopup->compositingStatus = true;
    m_ResulePopup->initBackgroundPix();
    EXPECT_EQ(m_ResulePopup->winPixmap, DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/background_win.svg"))
            << "check resultPopup initBackgroundPix";
}

TEST_F(UT_ResultPopup, UT_ResultPopup_initBackgroundPix2)
{
    m_ResulePopup->compositingStatus = false;
    m_ResulePopup->initBackgroundPix();
    EXPECT_EQ(m_ResulePopup->winPixmap, DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/background_win_nshadow.svg"))
            << "check resultPopup initBackgroundPix";
}

TEST_F(UT_ResultPopup, UT_ResultPopup_popupShow)
{
    m_ResulePopup->popupShow();
}

TEST_F(UT_ResultPopup, UT_ResultPopup_setHasWin)
{
    m_ResulePopup->setHasWin(true);
    EXPECT_EQ(m_ResulePopup->hasWin, true)
            << "check resultPopup setHasWin";
}

TEST_F(UT_ResultPopup, UT_ResultPopup_popupClose)
{
    m_ResulePopup->popupClose();
}

TEST_F(UT_ResultPopup, UT_ResultPopup_slotCompositingChanged)
{
    m_ResulePopup->slotCompositingChanged(true);
    EXPECT_EQ(m_ResulePopup->compositingStatus, true)
            << "check resultPopup slotCompositingChanged";
}

TEST_F(UT_ResultPopup, UT_ResultPopup_paintEvent1)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ResulePopup->hasWin = true;
    m_ResulePopup->compositingStatus = true;
    m_ResulePopup->paintEvent(&event);
}

TEST_F(UT_ResultPopup, UT_ResultPopup_paintEvent2)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ResulePopup->hasWin = true;
    m_ResulePopup->compositingStatus = false;
    m_ResulePopup->paintEvent(&event);
}

TEST_F(UT_ResultPopup, UT_ResultPopup_paintEvent3)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ResulePopup->hasWin = false;
    m_ResulePopup->compositingStatus = true;
    m_ResulePopup->paintEvent(&event);
}

TEST_F(UT_ResultPopup, UT_ResultPopup_paintEvent4)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ResulePopup->hasWin = false;
    m_ResulePopup->compositingStatus = false;
    m_ResulePopup->paintEvent(&event);
}

TEST_F(UT_ResultPopup, UT_ResultPopup_mouseMoveEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ResulePopup->mouseMoveEvent(&event);
}
