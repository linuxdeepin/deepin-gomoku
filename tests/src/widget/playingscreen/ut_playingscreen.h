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
#ifndef UT_PLAYINGSCREEN_H
#define UT_PLAYINGSCREEN_H

#include <QObject>
#include <QGraphicsScene>
#include <QDebug>
#include "constants.h"
#include "gtest/gtest.h"

#include "playingscreen.h"

class UT_PlayingScreen : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_PlayingScreen = new PlayingScreen();
        m_scene = new QGraphicsScene(0, 0, widgetWidth, widgetHeight - 50);
        m_scene->addItem(m_PlayingScreen);
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        m_scene->removeItem(m_PlayingScreen);
        delete m_PlayingScreen;
        delete m_scene;
        qInfo() << "TearDown" << endl;
    }
    PlayingScreen *m_PlayingScreen;
    QGraphicsScene *m_scene;
};

#endif // UT_PLAYINGSCREEN_H
