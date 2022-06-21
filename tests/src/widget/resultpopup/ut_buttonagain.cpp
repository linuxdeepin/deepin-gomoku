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
#include "ut_buttonagain.h"
#include <QMouseEvent>

TEST_F(UT_ButtonAgain, UT_ButtonAgain_setResult1)
{
    m_ButtonAgain->setResult(true);
    EXPECT_EQ(m_ButtonAgain->mResult, true)
            << "check buttonAgain setResult";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_setResult2)
{
    m_ButtonAgain->setResult(false);
    EXPECT_EQ(m_ButtonAgain->mResult, false)
            << "check buttonAgain setResult";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_mousePressEvent1)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ButtonAgain->mResult = true;
    m_ButtonAgain->mousePressEvent(&event);
    EXPECT_EQ(m_ButtonAgain->currentPixmap, m_ButtonAgain->againPress)
            << "check buttonRest mousePressEvent";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_mousePressEvent2)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ButtonAgain->mResult = false;
    m_ButtonAgain->mousePressEvent(&event);
    EXPECT_EQ(m_ButtonAgain->currentPixmap, m_ButtonAgain->failAgainPress)
            << "check buttonRest mousePressEvent";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_mouseReleaseEvent)
{
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ButtonAgain->mResult = true;
    m_ButtonAgain->mouseReleaseEvent(&event);
    EXPECT_EQ(m_ButtonAgain->currentPixmap, m_ButtonAgain->againNormal)
            << "check buttonRest mouseReleaseEvent";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_enterEvent)
{
    QEvent event(QEvent::Enter);
    m_ButtonAgain->mResult = true;
    m_ButtonAgain->enterEvent(&event);
    EXPECT_EQ(m_ButtonAgain->currentPixmap, m_ButtonAgain->againHover)
            << "check buttonRest enterEvent";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_leaveEvent)
{
    QEvent event(QEvent::Leave);
    m_ButtonAgain->mResult = true;
    m_ButtonAgain->leaveEvent(&event);
    EXPECT_EQ(m_ButtonAgain->currentPixmap, m_ButtonAgain->againNormal)
            << "check buttonRest enterEvent";
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_paintEvent1)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ButtonAgain->buttonPressed = true;
    m_ButtonAgain->currentPixmap = m_ButtonAgain->againPress;
    m_ButtonAgain->paintEvent(&event);
}

TEST_F(UT_ButtonAgain, UT_ButtonAgain_paintEvent2)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ButtonAgain->buttonPressed = true;
    m_ButtonAgain->currentPixmap = m_ButtonAgain->failAgainPress;
    m_ButtonAgain->paintEvent(&event);
}
