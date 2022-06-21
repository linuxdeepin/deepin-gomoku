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
#include "artificialintelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{

}

//根据当前棋局形式判断最佳落子位置
Position ArtificialIntelligence::getPosition(const ChessState chessState, const int color)
{
    //创建用来记录分数的数组
    int AIScore[line_row][line_col] = {{0}}; //记录AI的分数
    int opponentScore[line_row][line_col] = {{0}}; //记录用户分数
    int opponentColor; //对手颜色

    //如果AI先手且棋盘没有落子，AI第一次落子在中心交点处
    int flag = 0; //退出双层循环
    int i = 0, j = 0;
    for (i = 0; i < line_row; i++) {
        for (j = 0; j < line_col; j++) {
            if (chessState[i][j] > 0) { //棋盘已经落子
                flag = 1;
                break;
            }
        }
        if (flag) { //上一排有落子
            break;
        }
    }
    if (i == line_row && j == line_col) { //遍历了整个棋盘，没有落子
        return std::make_pair(line_row / 2, line_col / 2); //没有落子返回最中间天元位置
    }

    //记录对手棋子颜色
    opponentColor = ChessFromJudge::judgeColor(color);

    //不是先手第一次落子，开始计算最佳落子位置
    //遍历整个棋盘
    for (i = 0; i < line_row; i++) {
        for (j = 0; j < line_col; j++) {
            int score; //当前位置的分数
            Position position = std::make_pair(i, j);//构造位置

            //获取AI分数
            score = CalculateScore::getLocationScore(chessState, color, position);
            AIScore[i][j] = score;

            //获取用户分数
            score = CalculateScore::getLocationScore(chessState, opponentColor, position);
            opponentScore[i][j] = score;
        }
    }
    return CalculateScore::getBestLocation(AIScore, opponentScore);
}


