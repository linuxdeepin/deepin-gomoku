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
#include "ut_resuleinfo.h"
#include <QPaintEvent>


TEST_F(UT_ResuleInfo, UT_ResuleInfo_setResult1)
{
    m_ResuleInof->setResult(true);
    EXPECT_EQ(m_ResuleInof->mResult, true)
            << "check resultInfo setResult";
}

TEST_F(UT_ResuleInfo, UT_ResuleInfo_setResult2)
{
    m_ResuleInof->setResult(false);
    EXPECT_EQ(m_ResuleInof->mResult, false)
            << "check resultInfo setResult";
}


TEST_F(UT_ResuleInfo, UT_ResuleInfo_paintEvent1)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ResuleInof->paintEvent(&event);
}
