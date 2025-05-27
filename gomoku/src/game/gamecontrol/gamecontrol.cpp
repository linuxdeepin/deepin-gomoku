// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "gamecontrol.h"
#include "ddlog.h"

#include <QDebug>
#include <QTimer>
GameControl::GameControl(int AIColor, int userColor, QObject *parent)
    : QObject(parent)
    , AIColor(AIColor)
    , userColor(userColor)
    , AIPlaying(false)
    , checkerboard(new Checkerboard())
{
    qCDebug(appLog) << "GameControl created with AI color:" << AIColor << "User color:" << userColor;
}

GameControl::~GameControl()
{
    qCDebug(appLog) << "GameControl destroyed";
    if (checkerboard != nullptr) {
        delete checkerboard;
        checkerboard = nullptr;
    }
}

/**
 * @brief GameControl::initGame 初始化游戏
 */
void GameControl::initGame()
{
    qCDebug(appLog) << "Initializing game";
    //当前下棋者
    if (AIColor == chess_black) {
        AIPlaying = true;
        qCDebug(appLog) << "AI plays first (black)";
    } else {
        AIPlaying = false;
        qCDebug(appLog) << "User plays first (white)";
    }
    if (gameReset) {
        qCDebug(appLog) << "Resetting game flag";
        gameReset = false;
    }

    initGameStatus = true;

    checkerboard->resetCheckerboard(); //清空数组
    qCDebug(appLog) << "Checkerboard reset";
}

/**
 * @brief GameControl::startGame 开始游戏
 */
void GameControl::startGame()
{
    qCDebug(appLog) << "Starting game";
    initGame();
    Chess chess(-1, -1, 0); //还没有落子
    playChess(chess);
}

/**
 * @brief GameControl::setChessColor 设置用户和AI棋子颜色
 * @param aiColor ai棋子颜色
 * @param userColor 用户棋子颜色
 */
void GameControl::setChessColor(int ai, int user)
{
    qCDebug(appLog) << "Setting colors - AI:" << ai << "User:" << user;
    AIColor = ai;
    userColor = user;
}


/**
 * @brief GameControl::chessCompleted 槽函数：页面绘制完成棋子后对棋盘数组进行更新
 * @param chess 完成的棋子数据
 */
void GameControl::chessCompleted(const Chess chess)
{
    qCDebug(appLog) << "Chess completed at position:" << chess.x << "," << chess.y << "Color:" << chess.color;
    checkerboard->insertChess(chess); // 向棋盘插入棋子数据
    playChess(chess); //开始下棋
}

/**
 * @brief GameControl::resetGame 重置游戏
 */
void GameControl::resetGame()
{
    qCDebug(appLog) << "Resetting game";
    gameReset = true; //设置重玩的标志
    initGame();//初始化游戏
    startGame(); //开始游戏
}

/**
 * @brief GameControl::playChess 开始下棋
 * @param chess 最后一次落子数据
 */
void GameControl::playChess(const Chess chess)
{
    qCDebug(appLog) << "Playing chess at position:" << chess.x << "," << chess.y;
    ChessResult result;
    if ((result = ChessFromJudge::judgeResult(checkerboard->getChessState(), chess)) == playing) { //游戏正在进行中
        qCDebug(appLog) << "Game continues, current player:" << (AIPlaying ? "AI" : "User");
        emit isAIPlaying(AIPlaying); //发送旗手信号
        setAIChess();
    } else {
        qCDebug(appLog) << "Game over with result:" << result;
        emit gameOver(result); //游戏结束，发送结束状态
    }
}

/**
 * @brief GameControl::setAIChess AI下棋
 */
void GameControl::setAIChess()
{
    qCDebug(appLog) << "Setting AI chess, current game reset status:" << gameReset;
    bool currentGameStatus = gameReset; //记录当前是否重玩游戏
    if (!gameReset) { //没有重置游戏
        if (AIPlaying) { //AI下棋
            if (initGameStatus) { //如果是初始化,则减少延时时间
                qCDebug(appLog) << "Initial AI move with short delay";
                QTimer::singleShot(100, this, [ = ] {
                    Position AIpos = ArtificialIntelligence::getPosition(checkerboard->getChessState(), AIColor); //AI计算最佳落子位置
                    qCDebug(appLog) << "AI calculated position:" << AIpos.first << "," << AIpos.second;
                    Chess  chess(AIpos.first, AIpos.second, AIColor);
                    emit AIPlayChess(chess); //发送AI下棋信号
                });
                initGameStatus = false;
            } else {
                qCDebug(appLog) << "Normal AI move with standard delay";
                //延时函数,AI思考时间(方便显示回合信息)
                QTimer::singleShot(666, this, [ = ] {
                    Position AIpos = ArtificialIntelligence::getPosition(checkerboard->getChessState(), AIColor); //AI计算最佳落子位置
                    qCDebug(appLog) << "AI calculated position:" << AIpos.first << "," << AIpos.second;
                    Chess  chess(AIpos.first, AIpos.second, AIColor);
                    if (!currentGameStatus && !AIPlaying)
                        emit AIPlayChess(chess); //发送AI下棋信号
                });
            }
        }
        AIPlaying = !AIPlaying; //下一位下棋者
        qCDebug(appLog) << "Next player:" << (AIPlaying ? "AI" : "User");
    } else {
        //重置重玩游戏的标志
        qCDebug(appLog) << "Game reset, clearing reset flag";
        gameReset = false;
    }
}



