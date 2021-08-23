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
#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "constants.h"

struct Position {
    int x;
    int y;
};

//棋局形式
enum ChessFrom {
    WIN5, //五连珠
    ALIVE4, //活四
    SLEEP4, //眠四
    JUMP4, //冲四
    ALIVE3, //活三
    JUMP3, //冲三
    SLEEP3, //眠三
    ALIVE2, //活二
    JUMP2, //冲二
    SLEEP2, //眠二
    SAFETY, //安全没有威胁
};

//判断方向
enum Direction {
    HORIZONTAL,//横向
    VERTICAL, //竖向
    NORTHEAST,//右上左下
    NORTHWEST, //左上右下
};

//当前位置的形式，对各类棋型进行统计后比较
struct Situatuion {
    int win5; //五连珠
    int alive4; //活四
    int sleep4; //眠四
    int jump4; //冲四
    int alive3; //活三
    int jump3; //冲三
    int sleep3; //眠三
    int alive2; //活二
    int jump2; //冲二
    int sleep2; //眠二
    int safety; //安全没有威胁
};

class ArtificialIntelligence
{
private:
    //制定评分等级
    static const int LEVEL1 = 100000; //五连珠
    static const int LEVEL2 = 10000; //活四或双眠四或眠四活三
    static const int LEVEL3 = 5000; //双活三
    static const int LEVEL4 = 1000; //眠三活三
    static const int LEVEL5 = 500; //眠四
    static const int LEVEL6 = 400; //冲四
    static const int LEVEL7 = 100; //活三
    static const int LEVEL8 = 90; //冲三
    static const int LEVEL9 = 50; //双活二
    static const int LEVEL10 = 10; //活二
    static const int LEVEL11 = 9; //冲二
    static const int LEVEL12 = 5; //眠三
    static const int LEVEL13 = 2; //眠二
    static const int LEVEL14 = 1; //安全
    static const int LEVEL15 = 0; //已有棋子


    //计算当前位置的分数
    int getChessScore(const int chessState[line_row][line_col], int color, Position Position);

    //获取某个方向上的棋局类型
    ChessFrom getChessType(const int chessState[line_row][line_col], int color, Position position, int direction);

    //根据统计好的棋局形势计算该位置的分数
    int getScore(Situatuion situation);

    //获取某个方向上的9个棋子
    void getChess(int chess[9], const int chessState[line_row][line_col], int color, Position position, int direction);

    //判断某个方向上的棋子类型
    ChessFrom judgeChessType(const int chess[9]);

    //计算出用户分数数组和AI分数数组中的最大值,由此决定进攻还是防守
    Position maxScore(const int AIScore[line_row][line_col], const int userScore[line_row][line_col]);
public:
    ArtificialIntelligence();

    //根据当前棋局形式，返回计算出的最佳位置
    Position getPosition(const int chessState[line_row][line_col], int color);

};

#endif // ARTIFICIALINTELLIGENCE_H
