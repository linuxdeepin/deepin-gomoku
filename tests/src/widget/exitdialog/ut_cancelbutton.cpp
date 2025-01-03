// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ut_cancelbutton.h"

#include <QMouseEvent>

TEST_F(UT_CancelButton, UT_CancelButton_mousePressEvent)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_CalcelButton->mousePressEvent(&event);
    EXPECT_EQ(m_CalcelButton->buttonPressed, true)
            << "check calcelButton mousePressEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_mouseReleaseEvent)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_CalcelButton->mouseReleaseEvent(&event);
    EXPECT_EQ(m_CalcelButton->buttonPressed, false)
            << "check calcelButton mouseReleaseEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_enterEvent)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event(QPointF(1,1), QPointF(1,1), QPointF(1,1));
#else
    QEvent event(QEvent::Enter);
#endif
    m_CalcelButton->enterEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_CalcelButton->currentPixmap.cacheKey(), m_CalcelButton->buttonHover.cacheKey())
#else
    EXPECT_EQ(m_CalcelButton->currentPixmap, m_CalcelButton->buttonHover)
#endif
            << "check calcelButton enterEvent";
}

TEST_F(UT_CancelButton, UT_CancelButton_leaveEvent)
{
    QEvent event(QEvent::Leave);
    m_CalcelButton->leaveEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_CalcelButton->currentPixmap.cacheKey(), m_CalcelButton->buttonNormal.cacheKey())
        << "check calcelButton enterEvent";
#else
    EXPECT_EQ(m_CalcelButton->currentPixmap, m_CalcelButton->buttonNormal)
            << "check calcelButton enterEvent";
#endif

}

TEST_F(UT_CancelButton, UT_CancelButton_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_CalcelButton->buttonPressed = true;
    m_CalcelButton->paintEvent(&event);
}
