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
#ifndef CONSTANTS_H
#define CONSTANTS_H

//棋子形式
struct Chess {
    int x; //行
    int y; //列
    int color; // 颜色
    Chess(int x, int y, int color) : x(x), y(y), color(color) {}
};

//棋局形势
enum ChessResult {
    black_win,
    white_win,
    tie, //平局
    playing, //游戏继续中
};

const int widgetWidth = 1024; //界面宽度
const int widgetHeight = 768; //界面高度

const int backgrond_margin = 40; //棋盘边距
const int line_row = 13; //棋盘线长
const int line_col = 13; //棋盘线宽
const int chess_size = 44; //棋盘格子宽度
const int hover_size = 20;

const int chess_none =  0; //没有棋子
const int chess_black = 1; //黑色棋子
const int chess_white = 2; //白色棋子


#endif // CONSTANTS_H
