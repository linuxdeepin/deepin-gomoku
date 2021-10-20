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
#ifndef UT_GOMOKUMAINWINDOW_H
#define UT_GOMOKUMAINWINDOW_H

#include "gomokumainwindow.h"
#include "gtest/gtest.h"
#include <QtTest/QTest>
#include <stub.h>

void stub_initCompositingStatus()
{
}

class UT_GomokuMainWindow : public ::testing::Test
{

public:
    GomokuMainWindow *m_mainwindow = nullptr;
    void SetUp() //TEST跑之前会执行SetUp
    {
        Stub stub;
        stub.set(ADDR(GomokuMainWindow, initCompositingStatus), stub_initCompositingStatus);
        m_mainwindow = new GomokuMainWindow();
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        if (m_mainwindow != nullptr) {
            delete m_mainwindow;
            m_mainwindow = nullptr;
        }
        qInfo() << "TearDown" << endl;
    }
};

#endif // UT_GOMOKUMAINWINDOW_H
