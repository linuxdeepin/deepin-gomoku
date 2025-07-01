// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

//棋子形式
struct Chess {
    int x; //行
    int y; //列
    int color; // 颜色
    Chess(int x, int y, int color) : x(x), y(y), color(color) {}
};


//游戏状态
enum GameState {
    gameStart, //游戏开始
    gamePlaying, //游戏进行中
    gameOver, //游戏结束
};

//棋局形势
enum ChessResult {
    black_win,
    white_win,
    tie, //平局
    playing, //游戏继续中
};

//退出弹框的按钮类型
enum BTType {
    BTExit,
    BTCancel,
};

const int widgetWidth = 1024; //界面宽度
const int widgetHeight = 768; //界面高度
const int checkerboardSize = 694; //棋盘图片宽高（要求为正方形）
const int line_num = 15; //棋盘规格15X15
const int line_row = line_num; //棋盘横线数量
const int line_col = line_num; //棋盘纵线数量
const int chess_size = 41; //相邻两线之间的距离
const int backgrond_margin = (checkerboardSize - chess_size * (line_num - 1)) / 2; //棋盘左、上边距
const int hover_size = 20;

const int chess_none =  0; //没有棋子
const int chess_black = 1; //黑色棋子
const int chess_white = 2; //白色棋子

const QString COMPOSITINGSERVICE = "com.deepin.wm";
const QString COMPOSITINGPATH = "/com/deepin/wm";


#endif // CONSTANTS_H
