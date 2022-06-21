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
#include "checkerboard.h"

Checkerboard::Checkerboard(QObject *parent) : QObject(parent)
{
    initCheckerboard();
}

/**
 * @brief Checkerboard::insertChess
 * @param chess
 * 棋盘中增加棋子数据
 */
void Checkerboard::insertChess(Chess chess)
{
    int x = chess.x;
    int y = chess.y;
    int color = chess.color;
    chessState[x][y] = color;
}

/**
 * @brief Checkerboard::getChessState
 * @param chessStatus
 * 获取棋盘数组数据
 */

const ChessState &Checkerboard::getChessState()
{
    return chessState;
}

/**
 * @brief Checkerboard::clearCheckerboard 初始化数组数组
 *
 */
void Checkerboard::initCheckerboard()
{
    for (int i = 0; i < line_row; i++) {
        QVector<int> chessState_col;
        for (int j = 0; j < line_col; j++) {
            chessState_col.push_back(chess_none);
        }
        this->chessState.push_back(chessState_col);
    }
}

/**
 * @brief Checkerboard::clearCheckerboard 重置数组
 */
void Checkerboard::resetCheckerboard()
{
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            chessState[i][j] = chess_none;
        }
    }
}
