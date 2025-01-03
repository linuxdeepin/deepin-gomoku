// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ut_selectbutton.h"

#include <QEvent>
#include <QPaintEvent>

TEST_F(UT_SelectButton, UT_SelectButton_enterEvent)
{
#if QT_VERSION_MAJOR > 5
    QEnterEvent event(QPointF(1, 1), QPointF(1, 1), QPointF(1, 1));
#else
    QEvent event(QEvent::Enter);
#endif
    m_SelectButton->enterEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_SelectButton->currentStatus.cacheKey(), m_SelectButton->selectHover.cacheKey())
#else
    EXPECT_EQ(m_SelectButton->currentStatus, m_SelectButton->selectHover)
#endif
            << "check selectButton enterEvent";
}

TEST_F(UT_SelectButton, UT_SelectButton_leaveEvent1)
{
    QEvent event(QEvent::Leave);
    m_SelectButton->pressStatus = true;
    m_SelectButton->leaveEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_SelectButton->currentStatus.cacheKey(), m_SelectButton->selectPress.cacheKey())
#else
    EXPECT_EQ(m_SelectButton->currentStatus, m_SelectButton->selectPress)
#endif
            << "check selectButton leaveEvent";
}

TEST_F(UT_SelectButton, UT_SelectButton_leaveEvent2)
{
    QEvent event(QEvent::Leave);
    m_SelectButton->pressStatus = false;
    m_SelectButton->leaveEvent(&event);
#if QT_VERSION_MAJOR > 5
    EXPECT_EQ(m_SelectButton->currentStatus.cacheKey(), m_SelectButton->selectNormal.cacheKey())
#else
    EXPECT_EQ(m_SelectButton->currentStatus, m_SelectButton->selectNormal)
#endif
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
