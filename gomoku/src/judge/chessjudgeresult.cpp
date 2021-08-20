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
#include "chessjudgeresult.h"

ChessJudgeResult::ChessJudgeResult()
{

}

int ChessJudgeResult::judgeResult(const int chessState[ROW][COL], int lastRow, int lastCol)
{
    int color = chessState[lastRow][lastRow]; // 记录最后一次落子的颜色
    int count = 0; // 统计连起来的棋子数目
    int left = 0, right = 0, top = 0, button = 0; //记录下该位置的上下左右边界，用来判断出界问题
    //判断是否达成平局
    int flag = 0;
    int i = 0, j = 0;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (chessState[i][j] == 0) { //有位置没落子，不存在平局
                flag = 1;
                break;
            }
        }
        if (flag) { //退出外层循环
            break;
        }
    }
    if (i == ROW && j == COL) {
        return -1; //平局
    }

    //横向判断
    left  = (lastCol - 4) < 0 ? 0 : (lastCol - 4); //左边出界时记为0
    right = (lastCol + 4) > (COL - 1) ? (COL - 1) : (lastCol + 4); //右边出界时为12
    for (i = lastRow, j = left; j <= right; j++) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return color; //五连珠胜利
            }
        } else {
            count = 0; //断开重新计数
        }
    }

    //纵向判断
    count = 0;
    top = (lastRow - 4) < 0 ? 0 : (lastRow - 4); //上边出界时记为0
    button = (lastRow + 4) > (ROW - 1) ? (ROW - 1) : (lastRow + 4); //下边边出界时记为12
    for (i = top, j = lastCol; i <= button; i++) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return color;
            }
        } else {
            count = 0;
        }
    }

    //左下右上判断
   count  = 0;
   top = lastRow - 4; //行的最小值
   right = lastCol + 4; //列的最大值
   if (top < 0 || left > (COL - 1)) { //右上出界
       if (lastRow < (COL - 1 - lastCol)) {//判断行先出界还是列先出界
           top = 0; //行出界
           right = lastRow + lastRow; //行几步出界，列就几步
       } else {
           right = COL - 1;
           top = lastRow - (COL - 1 - lastCol);//列几步出界，行就几步
       }
   }
    //左下
    button = lastRow + 4;//行最大值
    left = lastCol - 4; //列最小值
    if (left < 0 || button > (ROW - 1)) { //左下出界
        if (left < (ROW - 1 - lastRow)) { //列先出界
            left = 0;
            button = lastRow + lastCol;
        } else {
            button = ROW - 1;
            left = lastRow - (ROW - 1 - lastRow);
        }
    }
    //统计棋子数目
    for (i = top, j = left; i < button;i++, j--) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5){
                return color;
            }
        } else {
            count = 0;
        }
    }

    //左上右下判断
    count = 0;
    left = lastCol - 4; //列最小值
    top = lastRow - 4; //行最小值
    if (left < 0 || top < 0) { //左上出界
        if (lastCol < lastRow) { //列先出界
            left = 0;
            top = lastRow - lastCol;
        } else {
            top = 0;
            left = lastCol - lastRow;
        }
    }
    //右下
    right = lastCol + 4; //列最大值
    button  = lastRow + 4; //行最大值
    if (right > (COL - 1) || button > (ROW - 1)) { //右下出界
        if (lastCol < lastRow) { //行先出界
            button = ROW - 1;
            right = lastCol + (ROW - 1 - lastRow);
        } else {
            right = COL - 1;
            button = lastRow + (COL - 1 - lastCol);
        }
    }
    //统计棋子数目
    for (i = top, j = left; i < button; i++, j++) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return color;
            }
        } else {
            count = 0;
        }
    }
    return 0; //游戏还在继续
}
