/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
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
#include "checkerboardscene.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>

CheckerboardScene::CheckerboardScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(parent)
    , cbitem(new CheckerboardItem)
    , buttonStartPause(new BTStartPause)
    , buttonReplay(new BTReplay)
    , buttonMusicControl(new BTMusicControl)
    , playingScreen(new PlayingScreen)
    , AIChess(-1, -1, 0)
{
    //设置scene大小
    setSceneRect(x, y, width, height);
    initCheckerboard();
    initPlayingScreen();
    initFunctionButton();
    connect(buttonStartPause, &BTStartPause::signalGameStop, this, &CheckerboardScene::slotGameStop);
    connect(buttonStartPause, &BTStartPause::signalGameStart, this, &CheckerboardScene::slotGameStart);

    connect(this, &CheckerboardScene::signalStartGame, buttonStartPause, &ButtonItem::slotStartGame);
    connect(this, &CheckerboardScene::signalStartGame, buttonReplay, &ButtonItem::slotStartGame);
    connect(this, &CheckerboardScene::signalStartGame, buttonMusicControl, &ButtonItem::slotStartGame);
    connect(this, &CheckerboardScene::signalStartGame, playingScreen, &PlayingScreen::slotStartGame);
}

CheckerboardScene::~CheckerboardScene()
{
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            removeItem(chessItemList.at(i).at(j));
            delete chessItemList.at(i).at(j);
        }
    }
    chessItemList.clear();
    if (cbitem != nullptr) {
        delete cbitem;
        cbitem = nullptr;
    }
    if (buttonStartPause != nullptr) {
        delete buttonStartPause;
        buttonStartPause = nullptr;
    }
    if (buttonReplay != nullptr) {
        delete buttonReplay;
        buttonReplay = nullptr;
    }
    if (buttonMusicControl != nullptr) {
        delete buttonMusicControl;
        buttonMusicControl = nullptr;
    }
    if (playingScreen != nullptr) {
        delete playingScreen;
        playingScreen = nullptr;
    }
}

//初始化棋盘
void CheckerboardScene::initCheckerboard()
{

    cbitem->setPos(this->width() * CheckerboardPosWidth, this->height() * CheckerboardPosHeight);
    addItem(cbitem);
}

//初始化棋子
void CheckerboardScene::initChess()
{
    for (int i = 0; i < line_row; i++) {
        QVector<ChessItem *> pieceItems;
        for (int j = 0; j < line_col; j++) {
            ChessItem *chess = new ChessItem(userChessType);
            connect(this, &CheckerboardScene::signalGameOver, chess, &ChessItem::slotGameOver);//游戏结束
            connect(this, &CheckerboardScene::signalIsAIPlaying, chess, &ChessItem::slotIsAIPlaying);//当前旗手
            connect(buttonStartPause, &BTStartPause::signalGameStop, chess, &ChessItem::slotGameStop);//暂停游戏
            connect(buttonStartPause, &BTStartPause::signalGameStart, chess, &ChessItem::slotGameStart);//开始游戏
            connect(chess, &ChessItem::signalCPaintItem, this, &CheckerboardScene::slotCPaintItem);//落子坐标,判断输赢
            //整个棋盘左上角点,加上偏移量到达绘制区域,减去棋格半径是以棋子所在rect左上角为圆点绘制棋子
            //循环添加每个位置棋子
            chess->setPos(this->width() * lefttopChessPosWidth + chessOffset  - chess_size / 2 + chess_size * j,
                          this->height() * lefttopChessPosHeight + chessOffset  - chess_size / 2 + chess_size * i);
            pieceItems.append(chess);
            addItem(chess);
            chessHasPaint[i][j] = false;
        }
        chessItemList.append(pieceItems);
    }
}

//初始化功能按钮
void CheckerboardScene::initFunctionButton()
{
    //开始/暂停游戏
    buttonStartPause->setPos(this->width() * buttonPosWidth, this->height() * buttonStartPausePosHeight);
    addItem(buttonStartPause);
    //重玩游戏
    buttonReplay->setPos(this->width() * buttonPosWidth, this->height() * buttonReplayPosHeight);
    connect(buttonReplay, &BTReplay::signalbuttonReplay, this, &CheckerboardScene::slotreplayFunction);
    addItem(buttonReplay);

    //音乐控制
    buttonMusicControl->setPos(this->width() * buttonPosWidth, this->height() * buttonMusicControlPosHeight);
    addItem(buttonMusicControl);
}

//初始化下棋详情
void CheckerboardScene::initPlayingScreen()
{
    //棋盘
    playingScreen->setPos(this->width() * playingScreenPosWidth, this->height() * playingScreenPosHeight);
    addItem(playingScreen);
}

//放置AI棋子
void CheckerboardScene::setAIChess(Chess chess)
{
    int row = chess.x;
    int col = chess.y;
    int color = chess.color;
    chessItemList.at(row).at(col)->setCurrentchess(color);
    chessItemList.at(row).at(col)->setchessStatus(true);
}

//重玩游戏
void CheckerboardScene::slotreplayFunction()
{
    qInfo() << gameStatus;
    if (gameStatus) {
        for (int i = 0; i < line_row; i++) {
            for (int j = 0; j < line_col; j++) {
                removeItem(chessItemList.at(i).at(j));
                chessItemList.at(i).at(j)->deleteLater();
                chessHasPaint[i][j] = false;
            }
        }
        chessItemList.clear();
        initChess();
        playingScreen->setCurrentChessColor(false, userChessType);//重置回合信息显示
        emit signalRestGame();//通知游戏控制,重置游戏
    }
}

//暂停游戏
void CheckerboardScene::slotGameStop()
{
    gameStatus = false;
}

//开始游戏
void CheckerboardScene::slotGameStart()
{
    gameStatus = true;
    //如果AI已经下棋,绘制AI棋子
    if (AIChessStatus) {
        setAIChess(AIChess);
        AIChessStatus = false;
    }
}

//判断当前绘制的item，保存坐标
void CheckerboardScene::slotCPaintItem(ChessItem *cItem)
{
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            if (chessItemList.at(i).at(j) == cItem && !chessHasPaint[i][j]) {
                chessHasPaint[i][j] = true;
                Chess chess(i, j, cItem->getChessColor());
                bool chessPlayer = !cItem->getChessPlayer();
                int chessColor = cItem->getChessColor();
                //反转棋子颜色,显示回合信息
                if (chessColor == chess_black) {
                    chessColor = chess_white;
                } else if (chessColor == chess_white) {
                    chessColor = chess_black;
                }
                playingScreen->setCurrentChessColor(chessPlayer, chessColor);
                emit signalCurrentPoint(chess);
            }
        }
    }
}

//设置棋子颜色
void CheckerboardScene::setchessType(int chess)
{
    userChessType = chess;
    initChess();
    playingScreen->setCurrentChessColor(false, userChessType);
}

//开始游戏
void CheckerboardScene::startGame()
{
    emit signalStartGame();
}

//绘制AI棋子
void CheckerboardScene::slotPaintAIChess(Chess chess)
{
    //保存AI下棋数据
    AIChess.x = chess.x;
    AIChess.y = chess.y;
    AIChess.color = chess.color;
    //游戏暂停不能下棋
    if (gameStatus) {
        setAIChess(chess);
    } else {
        AIChessStatus = true;
    }
}
