// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "checkerboard.h"
#include "ddlog.h"

Checkerboard::Checkerboard(QObject *parent) : QObject(parent)
{
    qCDebug(appLog) << "Checkerboard initialized";
    initCheckerboard();
}

/**
 * @brief Checkerboard::insertChess
 * @param chess
 * 棋盘中增加棋子数据
 */
void Checkerboard::insertChess(Chess chess)
{
    qCDebug(appLog) << "Inserting chess at (" << chess.x << "," << chess.y << ") with color:" << chess.color;
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
    qCDebug(appLog) << "Getting current chess state";
    return chessState;
}

/**
 * @brief Checkerboard::clearCheckerboard 初始化数组数组
 *
 */
void Checkerboard::initCheckerboard()
{
    qCDebug(appLog) << "Initializing checkerboard with size:" << line_row << "x" << line_col;
    for (int i = 0; i < line_row; i++) {
        QVector<int> chessState_col;
        for (int j = 0; j < line_col; j++) {
            chessState_col.push_back(chess_none);
        }
        this->chessState.push_back(chessState_col);
    }
    qCDebug(appLog) << "Checkerboard initialization completed";
}

/**
 * @brief Checkerboard::clearCheckerboard 重置数组
 */
void Checkerboard::resetCheckerboard()
{
    qCDebug(appLog) << "Resetting checkerboard";
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            chessState[i][j] = chess_none;
        }
    }
    qCDebug(appLog) << "Checkerboard reset completed";
}
