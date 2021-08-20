/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     liyucheng <liyucheng@uniontech.com>
   *
   * Maintainer:  liyucheng <liyucheng@uniontech.com>
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
#ifndef CHESSJUDGERESULT_H
#define CHESSJUDGERESULT_H


class ChessJudgeResult
{
public:
    //棋盘长宽
    static const int ROW = 13;
    static const int COL = 13;

    ChessJudgeResult();

    //判断棋局结果
    int judgeResult(const int chessState[ROW][COL], int lastRow, int lastCol);
};

#endif // CHESSJUDGERESULT_H
