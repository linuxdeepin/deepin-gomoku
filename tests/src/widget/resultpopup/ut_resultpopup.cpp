// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ResulePopup->winPixmap.cacheKey(), DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/background_win.svg").cacheKey())
#else
    EXPECT_EQ(m_ResulePopup->winPixmap, DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/background_win.svg"))
#endif
            << "check resultPopup initBackgroundPix";
}

TEST_F(UT_ResultPopup, UT_ResultPopup_initBackgroundPix2)
{
    m_ResulePopup->compositingStatus = false;
    m_ResulePopup->initBackgroundPix();
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ResulePopup->winPixmap.cacheKey(), DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/background_win_nshadow.svg").cacheKey())
#else
    EXPECT_EQ(m_ResulePopup->winPixmap, DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/background_win_nshadow.svg"))
#endif
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
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ResulePopup->mouseMoveEvent(&event);
}
