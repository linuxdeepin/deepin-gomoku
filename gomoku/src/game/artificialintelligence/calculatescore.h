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
#ifndef CALCULATESCORE_H
#define CALCULATESCORE_H

#include "chessfromjudge.h"
#include <unordered_map>

class CalculateScore
{
public:
    CalculateScore();

    /**
     * @brief getLocationScore 得出该位置的分数
     * @param chessState 棋盘数组
     * @param color 所判断的棋子颜色
     * @param position 判断的位置
     * @return 该位置的分数
     */
    static int getLocationScore(const ChessState chessState,
                                const int color, const Position position);
    /**
     * @brief getBestLocation 根据分数得出最佳落子位置
     * @param AIScore AI分数数组
     * @param userScore 用户分数数组
     * @return
     */
    static Position getBestLocation(const int AIScore[line_row][line_col],
                                               const int userScore[line_row][line_col]);

private:
    /**
     * @brief computeScore计算该位置的分数
     * @param locationSituation 该位置的棋局形势
     * @return
     */
    static int computeScore(std::unordered_map<ChessFrom, int> locationSituation);

private:
    /**
     * 棋局形式评分等级
     */
    static const int SCORE_WIN5 = 100000; //五连珠分数
//    static const int SCORE_ALIVE4_DOUBLESLEEP4_SLEEP4ALIVE3= 10000; //活四、双眠四、眠四活三分数
    static const int SCORE_ALIVE4 = 10000;//活四
    static const int SCORE_DOUBLESLEEP4_SLEEP4ALIVE3 = 8000; //双眠四、眠四活三分数
    static const int SCORE_DOUBLEALIVE3 = 5000; //双活三分数
    static const int SCORE_SLEEP3ALIVE3 = 1000; //眠三活三分数
//    static const int SCORE_SLEEP4 = 500; //眠四分数
//    static const int SCORE_RUSH4 = 400; //冲四分数
//    static const int SCORE_ALIVE3 = 100; //活三分数
    static const int SCORE_ALIVE3_SLEEP4_RUSH4 = 500; //活三、眠四、冲四
    static const int SCORE_RUSH3 = 90; //冲三分数
    static const int SCORE_DOUBLEALIVE2 = 50; //双活二分数
    static const int SCORE_SLEEP3 = 10; //眠三分数
    static const int SCORE_ALIVE2 = 9; //活二分数
    static const int SCORE_RUSH2 = 5; //冲二分数
    static const int SCORE_SLEEP2 = 2; //眠二分数
    static const int SCORE_SAFETY = 1; //安全分数
    static const int SCORE_SELECTED = 0; //已有棋子分数

};

#endif // CALCULATESCORE_H
