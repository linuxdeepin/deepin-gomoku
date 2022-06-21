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
#ifndef UT_BTSTARTPAUSE_H
#define UT_BTSTARTPAUSE_H

#include "gtest/gtest.h"
#include "btstartpause.h"

#include <QDebug>

class UT_BTStartPause : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_ButtonStartPause = new BTStartPause();
        m_scene = new QGraphicsScene(0, 0, widgetWidth, widgetHeight - 50);
        m_scene->addItem(m_ButtonStartPause);
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        m_scene->removeItem(m_ButtonStartPause);
        delete m_ButtonStartPause;
        delete m_scene;
        qInfo() << "TearDown" << endl;
    }
    BTStartPause *m_ButtonStartPause;
    QGraphicsScene *m_scene;
};

#endif // UT_BTSTARTPAUSE_H
