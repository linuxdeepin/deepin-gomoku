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
#include "ut_checkerboarditme.h"

#include <stub.h>

TEST_F(UT_CheckerboardItme, UT_CheckerboardItem_boundingRect)
{
    QRectF rectf = m_checkerboardItem->boundingRect();
    EXPECT_EQ(rectf.height(), 662)
            << "check checkerboardItem boundingRect";
}

TEST_F(UT_CheckerboardItme, UT_CheckerboardItem_paint)
{
    QStyleOptionGraphicsItem *option = nullptr;
    QWidget *widget = nullptr;
    QPainter painter;
    m_checkerboardItem->paint(&painter, option, widget);
}
