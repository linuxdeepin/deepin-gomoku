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
#include "gamecontrol.h"
#include <QDebug>
#include <QTimer>
GameControl::GameControl(int AIColor, int userColor, QObject *parent) : QObject(parent)
{
    this->AIColor = AIColor;
    this->userColor = userColor;
    this->AI = new ArtificialIntelligence();

    initGame();//初始化游戏
}

GameControl::~GameControl()
{
    if (AI != nullptr) {
        delete  AI;
        AI = nullptr;
    }

}

//初始化游戏
void GameControl::initGame()
{
    //初始胡数组
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            chessState[i][j] = 0;
        }
    }

    //当前下棋者
    if (AIColor == chess_black) {
        AIPlaying = true;
    } else {
        AIPlaying = false;
    }
    if (gameReset)
        gameReset = false;

    initGameStatus = true;
}

//开始游戏
void GameControl::startGame()
{
    Chess chess(-1, -1, 0); //还没有落子
    playChess(chess);
}

//槽函数同步数据
void GameControl::chessCompleted(Chess chess)
{
    chessState[chess.x][chess.y] = chess.color; //更新数组状态，同步数据
    playChess(chess); //开始下棋
}

//重置游戏
void GameControl::resetGame()
{
    gameReset = true; //设置重玩的标志
    initGame();//初始化游戏
    startGame(); //开始游戏
}

//下棋
void GameControl::playChess(Chess chess)
{
    ChessResult result;
    if ((result = judgeResult(chess)) == playing) { //游戏正在进行中
        emit isAIPlaying(AIPlaying); //发送旗手信号
        setAIChess();
    } else {
        emit gameOver(result); //游戏结束，发送结束状态
    }
}

//AI下棋
void GameControl::setAIChess()
{
    bool currentGameStatus = gameReset; //记录当前是否重玩游戏
    if (!gameReset) { //没有重置游戏
        if (AIPlaying) { //AI下棋
            if (initGameStatus) { //如果是初始化,则减少延时时间
                QTimer::singleShot(100, this, [ = ] {
                    Position AIpos = AI->getPosition(chessState, AIColor); //AI计算最佳落子位置
                    Chess  chess(AIpos.x, AIpos.y, AIColor);
                    emit AIPlayChess(chess); //发送AI下棋信号
                });
                initGameStatus = false;
            } else {
                //延时函数,AI思考时间(方便显示回合信息)
                QTimer::singleShot(888, this, [ = ] {
                    Position AIpos = AI->getPosition(chessState, AIColor); //AI计算最佳落子位置
                    Chess  chess(AIpos.x, AIpos.y, AIColor);
                    if (!currentGameStatus && !AIPlaying)
                        emit AIPlayChess(chess); //发送AI下棋信号
                });
            }
        }
        AIPlaying = !AIPlaying; //下一位下棋者
    } else {
        //重置重玩游戏的标志
        gameReset = false;
    }
}

//判断棋局形式
ChessResult GameControl::judgeResult(Chess chess)
{
    int lastRow = chess.x;
    int lastCol = chess.y;
    int color = chess.color; // 记录最后一次落子的颜色
    ChessResult result; //胜利形式
    int count = 0; // 统计连起来的棋子数目
    int left = 0, right = 0, top = 0, button = 0; //记录下该位置的上下左右边界，用来判断出界问题

    //游戏刚开始
    if (lastCol == -1 && lastRow == -1) {
        return playing;
    }

    //判断是否达成平局
    int flag = 0;
    int i = 0, j = 0;
    for (i = 0; i < line_row; i++) {
        for (j = 0; j < line_col; j++) {
            if (chessState[i][j] == 0) { //有位置没落子，不存在平局
                flag = 1;
                break;
            }
        }
        if (flag) { //退出外层循环
            break;
        }
    }
    if (i == line_row && j == line_col) {
        return tie; //平局
    }

    if (color == chess_black) {
        result = black_win;
    } else {
        result = white_win;
    }

    //横向判断
    left  = (lastCol - 4) < 0 ? 0 : (lastCol - 4); //左边出界时记为0
    right = (lastCol + 4) > (line_col - 1) ? (line_col - 1) : (lastCol + 4); //右边出界时为12
    for (i = lastRow, j = left; j <= right; j++) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return result; //五连珠胜利
            }
        } else {
            count = 0; //断开重新计数
        }
    }

    //纵向判断
    count = 0;
    top = (lastRow - 4) < 0 ? 0 : (lastRow - 4); //上边出界时记为0
    button = (lastRow + 4) > (line_row - 1) ? (line_row - 1) : (lastRow + 4); //下边边出界时记为12
    for (i = top, j = lastCol; i <= button; i++) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return result;
            }
        } else {
            count = 0;
        }
    }

    //左下右上判断
    count  = 0;
    top = lastRow - 4; //行的最小值
    right = lastCol + 4; //列的最大值
    if (top < 0 || right > (line_col - 1)) { //右上出界
        if (lastRow < (line_col - 1 - lastCol)) {//判断行先出界还是列先出界
            top = 0; //行出界
            right = lastRow + lastCol; //行几步出界，列就几步
        } else {
            right = line_col - 1;
            top = lastRow - (line_col - 1 - lastCol);//列几步出界，行就几步
        }
    }
    //左下
    button = lastRow + 4;//行最大值
    left = lastCol - 4; //列最小值
    if (left < 0 || button > (line_row - 1)) { //左下出界
        if (left < (line_row - 1 - lastRow)) { //列先出界
            left = 0;
            button = lastRow + lastCol;
        } else {
            button = line_row - 1;
            left = lastRow - (line_row - 1 - lastRow);
        }
    }
    //统计棋子数目
    for (i = top, j = right; i <= button; i++, j--) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return result;
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
    if (right > (line_col - 1) || button > (line_row - 1)) { //右下出界
        if (lastCol < lastRow) { //行先出界
            button = line_row - 1;
            right = lastCol + (line_row - 1 - lastRow);
        } else {
            right = line_col - 1;
            button = lastRow + (line_col - 1 - lastCol);
        }
    }
    //统计棋子数目
    for (i = top, j = left; i <= button; i++, j++) {
        if (chessState[i][j] == color) {
            count++;
            if (count == 5) {
                return result;
            }
        } else {
            count = 0;
        }
    }
    return playing; //游戏还在继续
}



