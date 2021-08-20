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
#include <QTime>

CheckerboardScene::CheckerboardScene(QObject *parent)
    : QGraphicsScene(parent)
    , cbitem(new CheckerboardItem)
    , buttonStartPause(new BTStartPause)
    , buttonReplay(new BTReplay)
    , buttonMusicControl(new BTMusicControl)
    , playingScreen(new PlayingScreen)
{
    initCheckerboard();
    initChess();
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
    for (int i = 0; i < line_num; i++) {
        QVector<ChessItem *> pieceItems;
        for (int j = 0; j < line_num; j++) {
            ChessItem *chess = new ChessItem();
            connect(buttonStartPause, &BTStartPause::signalGameStop, chess, &ChessItem::slotGameStop);
            connect(buttonStartPause, &BTStartPause::signalGameStart, chess, &ChessItem::slotGameStart);
            chess->setPos(105 - 22 + 44 * j, 89 - 22 + 44 * i);
            pieceItems.append(chess);
            addItem(chess);
        }
        chessItemList.append(pieceItems);
    }
}

//初始化功能按钮
void CheckerboardScene::initFunctionButton()
{
    buttonStartPause->setPos(764, 235 + 6);
    addItem(buttonStartPause);

    buttonReplay->setPos(764, 315 + 6);
    connect(buttonReplay, &BTReplay::signalbuttonReplay, this, &CheckerboardScene::slotreplayFunction);
    addItem(buttonReplay);

    buttonMusicControl->setPos(764, 590 + 6);
    addItem(buttonMusicControl);
}

//初始化下棋详情
void CheckerboardScene::initPlayingScreen()
{
    playingScreen->setPos(710, 6);
    addItem(playingScreen);
}

//重玩游戏
void CheckerboardScene::slotreplayFunction()
{
    if (gameStatus) {
        for (int i = 0; i < line_num; i++) {
            for (int j = 0; j < line_num; j++) {
                removeItem(chessItemList.at(i).at(j));
            }
        }
        chessItemList.clear();

        initChess();
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

void CheckerboardScene::setchessType(int chess)
{
    chessType = chess;
}

void CheckerboardScene::setchessPoint(int row, int col)
{
    int realRow = row - 1;
    int realCol = col - 1;
    chessItemList.at(realRow).at(realCol)->setHoverStatus(false);
    chessItemList.at(realRow).at(realCol)->setchessStatus(true);
    chessItemList.at(realRow).at(realCol)->setCurrentchess(1);
}
