// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ut_closepopup.h"
#include <QMouseEvent>

TEST_F(UT_ClosePopup, UT_ClosePopup_mousePressEvent)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_ClosePopup->mousePressEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap.cacheKey(), m_ClosePopup->buttonPress.cacheKey())
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ClosePopup->mousePressEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonPress)
#endif
            << "check closePopup mousePressEvent";
}

TEST_F(UT_ClosePopup, UT_ClosePopup_mouseReleaseEvent)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    m_ClosePopup->mouseReleaseEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap.cacheKey(), m_ClosePopup->buttonNormal.cacheKey())
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
    m_ClosePopup->mouseReleaseEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonNormal)
#endif
            << "check closePopup mouseReleaseEvent";
}

TEST_F(UT_ClosePopup, UT_ClosePopup_enterEvent)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event( QPointF(1, 1), QPointF(1, 1), QPointF(1, 1));
    m_ClosePopup->enterEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap.cacheKey(), m_ClosePopup->buttonHover.cacheKey())
#else
    QEvent event(QEvent::Enter);
    m_ClosePopup->enterEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonHover)
#endif
            << "check closePopup enterEvent";
}

TEST_F(UT_ClosePopup, UT_ClosePopup_leaveEvent)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event( QPointF(1, 1), QPointF(1, 1), QPointF(1, 1));
    m_ClosePopup->leaveEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap.cacheKey(), m_ClosePopup->buttonNormal.cacheKey())
#else
    QEvent event(QEvent::Leave);
    m_ClosePopup->leaveEvent(&event);
    EXPECT_EQ(m_ClosePopup->currentPixmap, m_ClosePopup->buttonNormal)
#endif
            << "check closePopup leaveEvent";
}


TEST_F(UT_ClosePopup, UT_ClosePopup_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ClosePopup->paintEvent(&event);
}
