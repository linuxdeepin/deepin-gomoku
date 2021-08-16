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
#include <constants.h>

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include <QTime>

checkerboardscene::checkerboardscene(QObject *parent)
    : QGraphicsScene(parent)
{
    checkerboarditem *cbitem = new checkerboarditem();
    cbitem->setPos(22, 6);
    addItem(cbitem);

    for (int i = 0; i < line_num; i++) {
        QVector<chessitem *> pieceItems;
        for (int j = 0; j < line_num; j++) {
            chessitem *chess = new chessitem();
            chess->setPos(105 - 22 + 44 * j, 89 - 22 + 44 * i);
            pieceItems.append(chess);
            addItem(chess);
        }
        chessItemList.append(pieceItems);
    }
    setchessPoint(4, 4);
}

checkerboardscene::~checkerboardscene()
{
    chessItemList.clear();
}

void checkerboardscene::setchessType(int chess)
{
    chessType = chess;
}

void checkerboardscene::setchessPoint(int row, int col)
{
    int realRow = row - 1;
    int realCol = col - 1;
    chessItemList.at(realRow).at(realCol)->setHoverStatus(false);
    chessItemList.at(realRow).at(realCol)->setchessStatus(true);
    chessItemList.at(realRow).at(realCol)->setCurrentchess(1);
}

void checkerboardscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QTransform transform;
    qreal posX = event->scenePos().x();
    qreal posY = event->scenePos().y();
    QPointF currentPoint(posX, posY);
    chessitem *item = dynamic_cast<chessitem *>(itemAt(currentPoint, transform));
    for (int i = 0; i < line_num; i++) {
        for (int j = 0; j < line_num; j++) {
            if (chessItemList.at(i).at(j) == item && !item->getchessStatus()) {
                clickPosRow = i + 1;
                clickPosCol = j + 1;
                currentItem = item;
                currentItem->setHoverStatus(true);
                currentItem->setCurrentchess(chessType);
            } else {
                if (!chessItemList.at(i).at(j)->getchessStatus()) {
                    chessItemList.at(i).at(j)->setHoverStatus(false);
                    chessItemList.at(i).at(j)->setCurrentchess(0);
                }
            }
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}


void checkerboardscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QTransform transform;
    qreal posX = event->scenePos().x();
    qreal posY = event->scenePos().y();
    QPointF currentPoint(posX, posY);
    chessitem *item = dynamic_cast<chessitem *>(itemAt(currentPoint, transform));
    if (currentItem != nullptr && currentItem == item) {
        currentItem->setchessStatus(true);
        currentItem->setCurrentchess(chessType);
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
