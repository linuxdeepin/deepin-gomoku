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
#include "checkerboarditem.h"
#include "buttonfunction/btstartpause.h"
#include "buttonfunction/btreplay.h"
#include "buttonfunction/btmusiccontrol.h"
#include "playingscreen/playingscreen.h"
#include "constants.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include <QTime>

CheckerboardScene::CheckerboardScene(QObject *parent)
    : QGraphicsScene(parent)
{
    initCheckerboard();
    initPlayingScreen();
    initFunctionButton();
}

CheckerboardScene::~CheckerboardScene()
{
    chessItemList.clear();
}

//初始化棋盘
void CheckerboardScene::initCheckerboard()
{
    CheckerboardItem *cbitem = new CheckerboardItem();
    cbitem->setPos(22, 6);
    addItem(cbitem);

    QGraphicsItemGroup *itemGroup = new QGraphicsItemGroup();

    for (int i = 0; i < line_num; i++) {
        QVector<ChessItem *> pieceItems;
        for (int j = 0; j < line_num; j++) {
            ChessItem *chess = new ChessItem();
            chess->setPos(105 - 22 + 44 * j, 89 - 22 + 44 * i);
            itemGroup->addToGroup(chess);
            pieceItems.append(chess);
            addItem(chess);
        }
        chessItemList.append(pieceItems);
    }
}

//初始化功能按钮
void CheckerboardScene::initFunctionButton()
{
    BTStartPause *buttonStartPause = new BTStartPause();
    buttonStartPause->setPos(764, 235 + 6);
    addItem(buttonStartPause);

    BTReplay *buttonReplay = new BTReplay();
    buttonReplay->setPos(764, 315 + 6);
    addItem(buttonReplay);

    BTMusicControl *buttonMusicControl = new BTMusicControl();
    buttonMusicControl->setPos(764, 590 + 6);
    addItem(buttonMusicControl);
}

//初始化下棋详情
void CheckerboardScene::initPlayingScreen()
{
    PlayingScreen *playingScreen = new PlayingScreen();
    playingScreen->setPos(710, 6);
    addItem(playingScreen);
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
