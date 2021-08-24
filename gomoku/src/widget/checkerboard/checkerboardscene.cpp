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

CheckerboardScene::CheckerboardScene(QObject *parent)
    : QGraphicsScene(parent)
    , cbitem(new CheckerboardItem)
    , buttonStartPause(new BTStartPause)
    , buttonReplay(new BTReplay)
    , buttonMusicControl(new BTMusicControl)
    , playingScreen(new PlayingScreen)
{
    initCheckerboard();
    initPlayingScreen();
    initFunctionButton();
    connect(buttonStartPause, &BTStartPause::signalGameStop, this, &CheckerboardScene::slotGameStop);
    connect(buttonStartPause, &BTStartPause::signalGameStart, this, &CheckerboardScene::slotGameStart);
}

CheckerboardScene::~CheckerboardScene()
{
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
    cbitem->setPos(22, 6);
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
            chess->setPos(105 - 22 + 44 * j, 89 - 22 + 44 * i);
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
    buttonStartPause->setPos(764, 235 + 6);
    addItem(buttonStartPause);

    //重玩游戏
    buttonReplay->setPos(764, 315 + 6);
    connect(buttonReplay, &BTReplay::signalbuttonReplay, this, &CheckerboardScene::slotreplayFunction);
    addItem(buttonReplay);

    //音乐控制
    buttonMusicControl->setPos(764, 590 + 6);
    addItem(buttonMusicControl);
}

//初始化下棋详情
void CheckerboardScene::initPlayingScreen()
{
    //棋盘
    playingScreen->setPos(710, 6);
    addItem(playingScreen);
}

//重玩游戏
void CheckerboardScene::slotreplayFunction()
{
    if (gameStatus) {
        for (int i = 0; i < line_row; i++) {
            for (int j = 0; j < line_col; j++) {
                removeItem(chessItemList.at(i).at(j));
                chessHasPaint[i][j] = false;
            }
        }
        chessItemList.clear();
        initChess();
        emit signalRestGame();//通知游戏控制,重置游戏
    }
}

//开始游戏
void CheckerboardScene::slotGameStop()
{
    gameStatus = false;
}

//暂停游戏
void CheckerboardScene::slotGameStart()
{
    gameStatus = true;
}

//判断当前绘制的item，保存坐标
void CheckerboardScene::slotCPaintItem(ChessItem *cItem)
{
    int cRow = 0;
    int cCol = 0;
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            if (chessItemList.at(i).at(j) == cItem && !chessHasPaint[i][j]) {
                chessHasPaint[i][j] = true;
                cRow = i;
                cCol = j;
                Chess chess(cRow, cCol, cItem->getChessColor());
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
}

//绘制棋子
void CheckerboardScene::setchessPoint(Chess chess)
{
    int realRow = chess.x;
    int realCol = chess.y;
    qInfo() << realRow << realCol;// 查看AI落子位置
    chessItemList.at(realRow).at(realCol)->setCurrentchess(chess.color);
    chessItemList.at(realRow).at(realCol)->setchessStatus(true);
}

//绘制AI棋子
void CheckerboardScene::slotPaintAIChess(Chess chess)
{
    setchessPoint(chess);
}
