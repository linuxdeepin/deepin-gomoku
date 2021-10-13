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
#include "ut_checkerboard.h"

TEST_F(UT_CheckerBoard, UT_CheckerBoard_insertChess)
{
    Chess chess(1, 1, chess_black);
    m_CheckerBoard->insertChess(chess);
    EXPECT_EQ(m_CheckerBoard->chessState[1][1], chess_black)
            << "check checkerBoard insertChess";
}

TEST_F(UT_CheckerBoard, UT_CheckerBoard_getChessState)
{
    Chess chess(1, 1, chess_black);
    m_CheckerBoard->insertChess(chess);
    ChessState res = m_CheckerBoard->getChessState();
    EXPECT_EQ(res[1][1], chess_black)
            << "check checkerBoard getChessState";
}

TEST_F(UT_CheckerBoard, UT_CheckerBoard_initCheckerboard)
{
    m_CheckerBoard->initCheckerboard();
    EXPECT_EQ(m_CheckerBoard->chessState[1][1], chess_none)
            << "check checkerBoard initCheckerboard";
}

TEST_F(UT_CheckerBoard, UT_CheckerBoard_resetCheckerboard)
{
    m_CheckerBoard->resetCheckerboard();
    EXPECT_EQ(m_CheckerBoard->chessState[1][1], chess_none)
            << "check checkerBoard initCheckerboard";
}

