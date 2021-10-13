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
#ifndef UT_DETERMINEBUTTON_H
#define UT_DETERMINEBUTTON_H

#include "gtest/gtest.h"
#include "determinebutton.h"
#include <QDebug>

class UT_DetermineButton : public testing::Test
{
public:
    void SetUp() //TEST跑之前会执行SetUp
    {
        m_DetermineButton = new Determinebutton();
        qInfo() << "SetUp" << endl;
    }
    void TearDown() //TEST跑完之后会执行TearDown
    {
        delete m_DetermineButton;
        qInfo() << "TearDown" << endl;
    }
    Determinebutton *m_DetermineButton;
};

#endif // UT_DETERMINEBUTTON_H
