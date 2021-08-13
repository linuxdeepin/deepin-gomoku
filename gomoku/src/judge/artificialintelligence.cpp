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
#include <vector>
ArtificialIntelligence::ArtificialIntelligence()
{

}


//根据当前棋局形式判断最佳落子位置
Position ArtificialIntelligence::getPosition(const int (*chessState)[15], int color)
{
    //创建用来记录分数的数组
    int AIScore[15][15] = {0}; //记录AI的分数
    int userScore[15][15] = {0}; //记录用户分数

    //如果AI先手且棋盘没有落子，AI第一次落子在中心交点处
    int flag = 0; //退出双层循环
    int i = 0, j = 0;
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (chessState[i][j] > 0) { //棋盘已经落子
                flag = 1;
                break;
            }
        }
        if (flag) { //上一排有落子
            break;
        }
    }
    if (i == 15 && j == 15) { //遍历了整个棋盘，没有落子
        Position position = {7, 7}; //ai先手落子位置是最中心交点
        return position;
    }

    //不是先手第一次落子，开始计算最佳落子位置
    //遍历整个棋盘
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            Position position; //当前位置
            int score; //当前位置的分数
            position.x = i;
            position.y = j;

            //获取AI分数
            score = getChessScore(chessState, color, position);
            AIScore[i][j] = score;

            //判断用户棋子颜色
            if (color == BLACKCHESS) {
                color = WHITECHESS;
            } else {
                color = BLACKCHESS;
            }

            //获取用户分数
            score = getChessScore(chessState, color, position);
            userScore[i][j] = score;
        }
    }
    return maxScore(AIScore, userScore);
}

//计算当前位置的分数
int ArtificialIntelligence::getChessScore(const int (*chessState)[15], int color, Position position)
{
    Situatuion situation = {0};

    if (chessState[position.x][position.y]) { //该位置存在棋子
        return LEVEL15; // 没有任何威胁
    }

    //计算四个方向的棋子，0为横向、1为竖向、2为右上左下，3为左上右下
    for (int direction = 0; direction < 4; direction++) {
        int type = 0; // 每个方向上的棋局形势

        //获取某个方向上的棋局类型
        type = getChessType(chessState, color, position, direction);

        //统计出每个位置上的棋局类型
        switch (type) {
        case WIN5:
            situation.win5++;
            break;
        case ALIVE4:
            situation.alive4++;
            break;
        case SLEEP4:
            situation.sleep4++;
            break;
        case JUMP4:
            situation.jump4++;
            break;
        case ALIVE3:
            situation.alive3++;
            break;
        case JUMP3:
            situation.jump3++;
            break;
        case SLEEP3:
            situation.sleep3++;
            break;
        case ALIVE2:
            situation.alive2++;
            break;
        case JUMP2:
            situation.jump2++;
            break;
        case SLEEP2:
            situation.sleep2++;
            break;
        case SAFETY:
            situation.safety++;
            break;
        default:
            break;
        }
    }

    //根据统计好的棋局形势返回分数
    return getScore(situation);
}

//根据统计出的棋局形势计算出该位置的分数
int ArtificialIntelligence::getScore(Situatuion situation)
{
    int die4 = situation.sleep4 + situation.jump4;
    int alive3 = situation.alive3 + situation.jump3;
    int alive2 = situation.alive2 + situation.jump2;

    if  (situation.win5 >= 1) {
        return LEVEL1; // 五连珠
    }
    if (situation.alive4 >= 1 || die4 >= 2 || (die4 >=1 && alive3 >= 1)) {
        return LEVEL2; //活四、双眠四、眠四活三
    }
    if (alive3 >= 2) {
        return LEVEL3; //双活三
    }
    if (situation.sleep3 >= 1 && situation.alive3 >= 1) {
        return LEVEL4; //眠三活三
    }
    if (situation.sleep4 >= 1) {
        return LEVEL5; //眠四
    }
    if (situation.jump4 >= 1) {
        return LEVEL6; //冲四
    }
    if (situation.alive3 >= 1) {
        return LEVEL7; //活三
    }
    if (situation.jump3 >= 1) {
        return LEVEL8; //冲三
    }
    if (alive2 >= 2) {
        return LEVEL9; //双活二
    }
    if (situation.alive2 >= 1) {
        return LEVEL10; //活二
    }
    if (situation.jump2 >= 1) {
        return LEVEL11; //冲二
    }
    if (situation.sleep3 >= 1) {
        return LEVEL12; //眠三
    }
    if (situation.sleep2 >= 1) {
        return LEVEL13; //眠二
    }
    return LEVEL14; //安全没有威胁
}

//计算某个方向上的棋局形势
int ArtificialIntelligence::getChessType(const int (*chessState)[15], int color, Position position, int direction)
{
    int type = 0; //棋局类型
    int chess[9] = {0}; //存储一个方向上的9个棋子

    //获取一个方向上的9个棋子，注意边界问题
    getChess(chess, chessState, color, position, direction);

    //根据获取到的9个棋子判断棋局类型
    type = judgeChessType(chess);
    return type;
}

//收集某个方向上的9个棋子
void ArtificialIntelligence::getChess(int chess[9], const int (*chessState)[15], int color, Position position, int direction)
{
    //出界时设置为对手颜色
    int userColor;
    if (color == BLACKCHESS) {
        userColor = WHITECHESS;
    } else {
        userColor = BLACKCHESS;
    }

    chess[4] = color; //该数组的中心位置为该用户所持棋子

    switch (direction) {
    case 0: //横向棋子
        //左边四个棋子，遇到边界时记为对手棋子
        for (int i = position.x, j = 1; j <= 4; j++) {
            int col = position.y - j;
            if (col < 0) { //出界
                for (; j <= 4; j++) {
                    chess[4 - j] = userColor;
                }
                break;
            }
            chess[4 - j] = chessState[i][col];
        }
        //右边四个棋子，遇到边界时记为对手棋子
        for (int i = position.x, j = 1; j <= 4; j++) {
            int col = position.y + j;
            if (col > 14) {
                for (;j <= 4; j++) {
                    chess[4 + j] = userColor;
                }
                break;
            }
            chess[4 + j] = chessState[i][col];
        }
        break;
    case 1: //竖向棋子
        //上边四个棋子，遇到边界记为对手棋子
        for (int j = position.y, i = 1; i <= 4; i++) {
            int row = position.x - i;
            if (row < 0) {
                for (;i <=4; i++) {
                    chess[4 - i]  = userColor;
                }
                break;
            }
            chess[4 - i] = chessState[row][j];
        }
        //下边四个棋子，遇到边界记为对手棋子
        for (int j = position.y, i = 1; i <= 4; i++) {
            int row = position.x + i;
            if (row > 14) {
                for (; i <= 4; i++) {
                    chess[4 + i] = userColor;
                }
                break;
            }
            chess[4 + i] = chessState[row][j];
        }
        break;
    case 2: //右上左下
        //左下方四个棋子
        for (int i = 1, j = 1; i <= 4; j++, i++) {
            int row = position.x + i;
            int col = position.y - j;
            if (row > 14 || col < 0) {
                for (;i <= 4; i++) {
                    chess[4 - i] = userColor;
                }
                break;
            }
            chess[4 - i] = chessState[row][col];
        }
        //右上方四个棋子
        for (int i = 1, j = 1; i <= 4; i++, j++) {
            int row = position.x - i;
            int col = position.y + j;
            if (row < 0 || col > 14) {
                for (; i <= 4; i++) {
                    chess[4 + i] = userColor;
                }
                break;
            }
            chess[4 + i] = chessState[row][col];
        }
        break;
    case 3: //左上右下
        //左上方四个 棋子
        for (int i = 1, j = 1; i <= 4; i++, j++) {
            int row = position.x - i;
            int col = position.y - j;
            if (row < 0 || col < 0) {
                for (;i <= 4; i++) {
                    chess[4 - i] = userColor;
                }
                break;
            }
            chess[4 - i] = chessState[row][col];
        }
        //右下方四个棋子
        for (int i = 1, j = 1; i <= 4; j++, i++) {
            int row = position.x + i;
            int col = position.y + j;
            if (col > 14 || row > 14) {
                for (;i <= 4;i++) {
                    chess[4 + i] = userColor;
                }
                break;
            }
            chess[4 + i] = chessState[row][col];
        }
        break;
    default:
        break;
    }
}

//判断某个方向上的棋局类型
int ArtificialIntelligence::judgeChessType(const int chess[9])
{
    int myColor = chess[4]; //自己棋子颜色
    int userColor; //对手的棋子颜色
    int count = 1; //统计相同棋子
    int left = -1, right = -1; //记录从中间往左数第几个不是同色的位置
    int leftColor = -1, rightColor = -1; //记录断开时该位置的棋子颜色

    if (myColor == BLACKCHESS) {
        userColor = WHITECHESS;
    } else {
        userColor = BLACKCHESS;
    }

    //计算左边4个棋子
    for (int i = 1; i <= 4; i++) {
        if (chess[4 - i] == myColor) {
            count++; //从中心往左数有几个连子
        } else {
            left = 4 - i; //棋子颜色不同时记录位置跟颜色
            leftColor = chess[4 - i];
            break;
        }
    }

    //统计右边四个棋子
    for (int i = 0; i <= 4; i++) {
        if (chess[4 + i] == myColor) {
            count++;
        } else {
            right  = 4 + i;
            rightColor = chess[4 + i];
            break;
        }
    }

    //五连珠
    if (count >= 5) {
        return WIN5;
    }

    //四连珠
    //已经达成四连珠，需判断是眠四、活四还是两面都堵死了没有威胁
    if (count == 4) {
        if (leftColor == EMPTY && rightColor == EMPTY) {
            return ALIVE4;//两边都是空的，活四
        } else if (rightColor == userColor && leftColor == userColor) {
            return SAFETY; //两边都被堵死了，没有威胁
        } else if (rightColor == EMPTY || leftColor == EMPTY) {
            return SLEEP4; //有一边为空，眠四
        }
    }

    //三连珠
    if (count == 3) {
        //记录下断开位置旁边的位置的棋子颜色，用来判断这个三连能否有五连的机会
        int leftColor1  = chess[left - 1];
        int rightColor1 = chess[right -1 ];

        //三连珠两边位置都空，有五连珠的机会
        if (leftColor == EMPTY && rightColor == EMPTY) {
            if (leftColor1 == userColor && rightColor1 == userColor) { //被对手封住
                return SLEEP3;//1022201形式 眠三
            } else if (leftColor1 == myColor || rightColor1 == myColor) { //有一方是自己的棋子
                return JUMP4; //1022202形式 冲四
            } else if (leftColor1 == EMPTY && rightColor1 == EMPTY) { //两边都为空
                return ALIVE3; //0022200形式 活三
            }

        }

        //三连两边都被封住，没有威胁
        if (leftColor == userColor && rightColor == userColor) {
            return SAFETY;//12221形式 安全没威胁
        }

        //三连珠两边只有一个是空的
        if (leftColor == EMPTY || rightColor == EMPTY) {
            //分两种情况，左边被封和右边被封
            //左边被封
            if (leftColor == userColor) {
                if (rightColor1 == userColor) { //右边被堵了，无法五连
                    return SAFETY; //122201形式 安全无威胁
                }
                if (rightColor1 == EMPTY) { //右边是开的
                    return SLEEP3; //122200形式 眠三
                }
                if (rightColor1 == myColor) { //右边是自己的棋子
                    return JUMP4; //122202形式 冲四
                }
            }

            //右边被封 和左边被封同理
            if (rightColor == userColor) {
                if (leftColor1 == userColor) {
                    return SAFETY;
                }
                if (leftColor1 == EMPTY) {
                    return SLEEP3;
                }
                if (leftColor1 == myColor) {
                    return JUMP4;
                }
            }

        }

    }

    //二连s
    if (count == 2) {
        //记录二连两边各三个位置
        int leftColor1 = chess[left - 1];
        int leftColor2 = chess[left - 2];
        int rightColor1 = chess[right + 1];
        int rightColor2 = chess[right + 2];

        //二连两边都为空
        if (leftColor == EMPTY && rightColor == EMPTY) {
            if ((rightColor1 == EMPTY && rightColor2 == myColor) ||  //022002或020022
                 (leftColor1 == EMPTY && leftColor2 == myColor)) {
                return SLEEP3;//眠三
            } else if (leftColor1 == EMPTY && rightColor1 == EMPTY) {
                return ALIVE2;// 002200形式 活二
            }

            if ((rightColor1 == myColor && rightColor2 == userColor) ||
                    (leftColor1 == myColor && leftColor2 == userColor)) {
                return SLEEP3; // 120220 或 022021 形式 眠三
            }
            //022022 或 220220
            if ((rightColor1 == myColor && rightColor2 == myColor) ||
                    (leftColor1 == myColor && leftColor2 == myColor)) {
                return JUMP4; //冲四
            }
            // 020220 //冲三
            if ((rightColor1 == myColor && rightColor2 == EMPTY) ||
                    (leftColor1 == myColor && leftColor2 == EMPTY)) {
                return JUMP3; //冲三
            }
        } else if (leftColor == userColor && rightColor == userColor) { //两边都被堵死
            return SAFETY; //安全没威胁
        } else if (leftColor == EMPTY || rightColor == EMPTY) { //一方被堵死
            if (leftColor == userColor) { //左边被堵死 1220
                if (rightColor1 == userColor || rightColor2 == userColor) { //右边也被堵死 122011
                    return SAFETY; //安全没威胁
                } else if (rightColor1 == EMPTY && rightColor2 == EMPTY) {  //122000
                    return SLEEP2; //眠二
                } else if (rightColor1 == myColor && rightColor2 == myColor) { //右边是自己棋子 122022
                    return JUMP4; //冲四
                } else if (rightColor1 == myColor || rightColor2 == myColor) { //右边是自己的棋子 122020 或 122002
                    return SLEEP3; //眠三
                }
            }
            if (rightColor == userColor) { //右边被堵死 0221
                if (leftColor1 == userColor || leftColor2 == userColor) { //左边也被堵死 110221
                    return SAFETY; //安全没威胁
                } else if (leftColor1 == EMPTY && leftColor2 == EMPTY) {  // 000221
                    return SLEEP2; //眠二
                } else if (leftColor1 == myColor && leftColor2 == myColor) { //左边是自己棋子 220221
                    return JUMP4; //冲四
                } else if (leftColor1 == myColor || leftColor2 == EMPTY) { //左边是自己的棋子 020221 或 200221
                    return SLEEP3; //眠三
                }
            }
        }
    }

    //一连，该棋就是要下的棋子
    if (count ==  1) {
        //记录一连两边各四个位置
        int leftColor1 = chess[left - 1];
        int leftColor2 = chess[left - 2];
        int leftColor3 = chess[left - 3];
        int rightColor1 = chess[right + 1];
        int rightColor2 = chess[right + 2];
        int rightColor3 = chess[right + 3];

        //在该点落子能连成冲四 20222 或 22202
        if (leftColor == EMPTY && leftColor1 == myColor &&
                leftColor2 == myColor && leftColor3 == myColor ) {
            return JUMP4;
        }
        if (rightColor == EMPTY && rightColor1 == myColor &&
                rightColor2 == myColor && rightColor3 == myColor ) {
            return JUMP4;
        }

        //022020 冲三
        if (leftColor == EMPTY && leftColor1 == myColor &&
                leftColor2 == myColor && leftColor3 == EMPTY && rightColor == EMPTY) {
            return JUMP3;
        }
        if (rightColor == EMPTY && rightColor1 == myColor &&
                rightColor2 == myColor && rightColor3 == EMPTY && leftColor == EMPTY) {
            return JUMP3;
        }

        //122020 眠三
        if (leftColor == EMPTY && leftColor1 == myColor &&
                leftColor2 == myColor && leftColor3 == userColor && rightColor == EMPTY) {
            return SLEEP3;
        }
        if (rightColor == EMPTY && rightColor1 == myColor &&
                rightColor2 == myColor && rightColor3 == userColor && leftColor == EMPTY) {
            return SLEEP3;
        }

        //眠三22002
        if (leftColor == EMPTY && leftColor1 == EMPTY &&
                leftColor2 == myColor && leftColor3 == myColor) {
            return SLEEP3;
        }
        if (rightColor == EMPTY && rightColor1 == EMPTY &&
                rightColor2 == myColor && rightColor3 == myColor) {
            return SLEEP3;
        }

        //眠三 20202
        if (leftColor == EMPTY && leftColor1 ==myColor &&
                leftColor2 == EMPTY &&  leftColor3 == myColor) {
            return SLEEP3;
        }
        if (rightColor == EMPTY && rightColor1 ==myColor &&
                rightColor2 == EMPTY &&  rightColor3 == myColor) {
            return SLEEP3;
        }

        //冲二 002020
        if (leftColor == EMPTY && leftColor1 == myColor &&
                leftColor2 == EMPTY && leftColor3 == EMPTY && rightColor == EMPTY) {
            return JUMP2;
        }
        if (rightColor == EMPTY && rightColor1 == myColor &&
                rightColor2 == EMPTY && rightColor3 == EMPTY && leftColor == EMPTY) {
            return JUMP2;
        }

        //冲二 020020
        if (leftColor == EMPTY && leftColor1 == EMPTY &&
                leftColor2 == myColor && leftColor3 == EMPTY && rightColor == EMPTY) {
            return JUMP2;
        }
        if (rightColor == EMPTY && rightColor1 == EMPTY &&
                rightColor2 == myColor && rightColor3 == EMPTY && leftColor == EMPTY) {
            return JUMP2;
        }
    }
    return SAFETY;
}

//从AI评分数组和用户评分数组中统计出最佳落子位置，决定进攻还是防守
Position ArtificialIntelligence::maxScore(int (*AIScore)[15], int (*userScore)[15])
{
    Position position; //最佳落子位置
    int AIMaxScore = 0; //AI最大分数
    int userMaxScore = 0; //用户最大分数

    /*
        思路：可能最大值有很多个，所以要找出我这几个最大值中对方也是最大值的位置，这个位置就是最佳落子位置。
    */
    std::vector<Position> AIMaxPositions; //存储AI评分最高的位置
    std::vector<Position> userMaxPositions; //存储用户评分最高的位置

    //ai数组中的最大值，最大值可能有多个
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (AIScore[i][j] == AIMaxScore) { //将最大值的位置全部存储
                position.x = i;
                position.y = j;
                AIMaxPositions.push_back(position);
            }
            if (AIScore[i][j] > AIMaxScore) {
                AIMaxScore = AIScore[i][j];
                AIMaxPositions.clear(); //有更大值就将前面的全清理出去
                position.x = i;
                position.y = j;
                AIMaxPositions.push_back(position);
            }
        }
    }

    //用户数组中的最大值
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (userScore[i][j] == userMaxScore) { //将最大值的位置全部存储
                position.x = i;
                position.y = j;
                userMaxPositions.push_back(position);
            }
            if (userScore[i][j] > userMaxScore) {
                userMaxScore = userScore[i][j];
                userMaxPositions.clear(); //有更大值就将前面的全清理出去
                position.x = i;
                position.y = j;
                userMaxPositions.push_back(position);
            }
        }
    }

    //由AI和用户的最大值判断是进攻还是防守，最佳落子位置
    if (AIMaxScore >= userMaxScore) { //进攻
        int tempScore = 0;
        for (auto it : AIMaxPositions) {
            if (userScore[it.x][it.y] >= tempScore) { //从AI的最大值中挑选用户也最大的位置
                tempScore = userScore[it.x][it.y];
                position = it;
            }
        }
        return position;
    } else { //防守
        int tempScore = 0;
        for (auto it : userMaxPositions) {
            if (AIScore[it.x][it.y] >= tempScore) { //从用户的最大值中挑选AI也最大的位置
                tempScore = AIScore[it.x][it.y];
                position = it;
            }
        }
        return position;
    }
}
