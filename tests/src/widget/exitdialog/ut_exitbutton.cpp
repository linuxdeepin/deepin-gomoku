// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ut_exitbutton.h"

#include <QMouseEvent>

TEST_F(UT_ExitButton, UT_ExitButton_mousePressEvent)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ExitButton->mousePressEvent(&event);
    EXPECT_EQ(m_ExitButton->buttonPressed,true)
            << "check exitButton mousePressEvent";
}

TEST_F(UT_ExitButton, UT_ExitButton_mouseReleaseEvent)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ExitButton->mouseReleaseEvent(&event);
    EXPECT_EQ(m_ExitButton->buttonPressed,false)
            << "check exitButton mouseReleaseEvent";
}

TEST_F(UT_ExitButton, UT_ExitButton_enterEvent)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event(QPointF(1,1), QPointF(1,1), QPointF(1,1));
#else
    QEvent event(QEvent::Enter);
#endif
    m_ExitButton->enterEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ExitButton->currentPixmap.cacheKey(), m_ExitButton->buttonHover.cacheKey())
#else
    EXPECT_EQ(m_ExitButton->currentPixmap, m_CalcelButton->buttonHover)
#endif
            << "check exitButton enterEvent";
}

TEST_F(UT_ExitButton, UT_ExitButton_leaveEvent)
{
    QEvent event(QEvent::Enter);
    m_ExitButton->leaveEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ExitButton->currentPixmap.cacheKey(), m_ExitButton->buttonNormal.cacheKey())
#else
    EXPECT_EQ(m_ExitButton->currentPixmap, m_CalcelButton->buttonNormal)
#endif
            << "check exitButton enterLeave";
}

TEST_F(UT_ExitButton, UT_ExitButton_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ExitButton->buttonPressed = true;
    m_ExitButton->paintEvent(&event);
}
