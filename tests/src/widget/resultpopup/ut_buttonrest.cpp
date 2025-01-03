// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ut_buttonrest.h"
#include <QMouseEvent>

TEST_F(UT_ButtonRest, UT_ButtonRest_setResult1)
{
    m_ButtonRest->setResult(true);
    EXPECT_EQ(m_ButtonRest->mResult, true)
            << "check buttonRest setResult";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_setResult2)
{
    m_ButtonRest->setResult(false);
    EXPECT_EQ(m_ButtonRest->mResult, false)
            << "check buttonRest setResult";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_mousePressEvent1)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ButtonRest->mResult = true;
    m_ButtonRest->mousePressEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->winRestPress.cacheKey())
#else
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->winRestPress)
#endif
            << "check buttonRest mousePressEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_mousePressEvent2)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ButtonRest->mResult = false;
    m_ButtonRest->mousePressEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->failRestPress.cacheKey())
#elif
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->failRestPress)
#endif
            << "check buttonRest mousePressEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_mouseReleaseEvent1)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ButtonRest->mResult = true;
    m_ButtonRest->mouseReleaseEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->winRestNormal.cacheKey())
#else
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->winRestNormal)
#endif
            << "check buttonRest mouseReleaseEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_mouseReleaseEvent2)
{
#if QT_VERSION_MAJOR > 5
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
#else
    QMouseEvent event(QMouseEvent::Type::MouseButtonPress, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, nullptr);
#endif
    m_ButtonRest->mResult = false;
    m_ButtonRest->mouseReleaseEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->failRestNormal.cacheKey())
#else
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->failRestNormal)
#endif
            << "check buttonRest mouseReleaseEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_enterEvent1)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1));
    m_ButtonRest->mResult = true;
    m_ButtonRest->enterEvent(&event);
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->winRestHover.cacheKey())
#else
    QEvent event(QEvent::Enter);
    m_ButtonRest->mResult = true;
    m_ButtonRest->enterEvent(&event);
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->winRestHover)
#endif
            << "check buttonRest enterEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_enterEvent2)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1));
    m_ButtonRest->mResult = false;
    m_ButtonRest->enterEvent(&event);
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->failRestHover.cacheKey())
#else
    QEvent event(QEvent::Enter);
    m_ButtonRest->mResult = false;
    m_ButtonRest->enterEvent(&event);
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->failRestHover)
#endif
            << "check buttonRest enterEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_leaveEvent1)
{
    QEvent event(QEvent::Leave);
    m_ButtonRest->mResult = true;
    m_ButtonRest->leaveEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->winRestNormal.cacheKey())
#else
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->winRestNormal)
#endif
            << "check buttonRest enterEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_leaveEvent2)
{
    QEvent event(QEvent::Leave);
    m_ButtonRest->mResult = false;
    m_ButtonRest->leaveEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_ButtonRest->currentPixmap.cacheKey(), m_ButtonRest->failRestNormal.cacheKey())
#else
    EXPECT_EQ(m_ButtonRest->currentPixmap, m_ButtonRest->failRestNormal)
#endif
            << "check buttonRest enterEvent";
}

TEST_F(UT_ButtonRest, UT_ButtonRest_paintEvent1)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ButtonRest->buttonPressed = true;
    m_ButtonRest->currentPixmap = m_ButtonRest->winRestPress;
    m_ButtonRest->paintEvent(&event);
}

TEST_F(UT_ButtonRest, UT_ButtonRest_paintEvent2)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ButtonRest->buttonPressed = true;
    m_ButtonRest->currentPixmap = m_ButtonRest->failRestPress;
    m_ButtonRest->paintEvent(&event);
}
