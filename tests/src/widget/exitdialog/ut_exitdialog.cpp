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
#include "ut_exitdialog.h"

#include <DHiDPIHelper>
#include <QPaintEvent>

TEST_F(UT_ExitDialog, UT_ExitDialog_initUI)
{
    m_ExitDialog->initUI();
}

TEST_F(UT_ExitDialog, UT_ExitDialog_initBackgroundPix1)
{
    m_ExitDialog->compositingStatus = true;
    m_ExitDialog->initBackgroundPix();
    EXPECT_EQ(m_ExitDialog->backgroundQPixmap, DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/close-dialog.svg"))
            << "check exitDialog initBackgroundPix";
}

TEST_F(UT_ExitDialog, UT_ExitDialog_initBackgroundPix2)
{
    m_ExitDialog->compositingStatus = false;
    m_ExitDialog->initBackgroundPix();
    EXPECT_EQ(m_ExitDialog->backgroundQPixmap, DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/close-dialog-nshadow.svg"))
            << "check exitDialog initBackgroundPix";
}

TEST_F(UT_ExitDialog, UT_ExitDialog_slotDialogClose)
{
    m_ExitDialog->soltDialogClose();
}

TEST_F(UT_ExitDialog, UT_ExitDialog_soltGameExit)
{
    m_ExitDialog->soltGameExit();
}

TEST_F(UT_ExitDialog, UT_ExitDialog_slotCompositingChanged)
{
    m_ExitDialog->slotCompositingChanged(true);
    EXPECT_EQ(m_ExitDialog->compositingStatus, true)
            << "check exitDialog slotCompositingChanged";
}

TEST_F(UT_ExitDialog, UT_ExitDialog_paintEvent)
{
    QRect rect;
    QPaintEvent event(rect);
    m_ExitDialog->paintEvent(&event);
}
