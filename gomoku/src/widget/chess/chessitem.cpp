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
#include "chessitem.h"
#include "constants.h"

#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
#include <QImageReader>

ChessItem::ChessItem(int userChessColor, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , backgroundPix(":/resources/black_chess.svg")
    , userChessType(userChessColor)
{
    setAcceptHoverEvents(true);
}

//设置棋子
void ChessItem::setCurrentchess(int chesstype)
{
    chessType = chesstype;
}

//获取棋子颜色
int ChessItem::getChessColor()
{
    return chessType;
}

//设置是否有棋子
void ChessItem::setchessStatus(bool chessstatus)
{
    chessStatus = chessstatus;
    update();
}

//获取是否有棋子
bool ChessItem::getchessStatus()
{
    return chessStatus;
}

void ChessItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor chessColor;
    QPixmap chessPixmap;
    painter->setRenderHints(QPainter::Antialiasing);

    if (chessStatus) {
        painter->save();
        painter->setPen(Qt::NoPen);
        if (chessType == 2) {
            chessPixmap = QPixmap(":/resources/white_chess.svg");
        } else if (chessType == 1) {
            chessPixmap = QPixmap(":/resources/black_chess.svg");
        }
        painter->setBrush(chessPixmap);
        painter->drawEllipse(boundingRect());
        painter->restore();
        emit signalCPaintItem(this);
    } else {
        painter->save();
        painter->setPen(Qt::NoPen);
        if (hoverStatus) {
            QColor backColor("000000");
            backColor.setAlphaF(0.2);
            painter->setBrush(backColor);

            //绘制白点或黑点
            painter->save();
            painter->setPen(Qt::NoPen);
            if (chessType == 2) {
                chessColor = Qt::white;
            } else if (chessType == 1) {
                chessColor = Qt::black;
                chessColor.setAlphaF(0.7);
            }
            painter->setBrush(chessColor);
            painter->drawEllipse(QRect(19, 19, 6, 6));
            painter->restore();
        }
        painter->drawEllipse(QRect(16, 16, 12, 12));
        painter->restore();
    }
}

QRectF ChessItem::boundingRect() const
{
    if (chessStatus) {
        //棋子大小
        return QRectF(0, 0, chess_size, chess_size);
    } else {
        //可落子范围
        int startHPoint = (chess_size - hover_size) / 2;
        return QRectF(startHPoint, startHPoint, hover_size, hover_size);
    }
}

void ChessItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!gameOver && gameStatus) {
        hoverStatus = true;
        //当前位置没有棋子,设置棋子颜色
        if (!chessStatus)
            setCurrentchess(userChessType);
    }
    QGraphicsItem::hoverEnterEvent(event);
}

void ChessItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hoverStatus = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

void ChessItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void ChessItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isAIPlaying)
        //玩家下棋才能落子
        if (hoverStatus && !chessStatus) {
            setchessStatus(true);
        }
    QGraphicsItem::mouseReleaseEvent(event);
}

//游戏结束
void ChessItem::slotGameOver()
{
    gameOver = true;
}

//判断旗手
void ChessItem::slotIsAIPlaying(bool AIPlaying)
{
    isAIPlaying = AIPlaying;
}

//开始游戏
void ChessItem::slotGameStart()
{
    gameStatus = true;
}

//暂停游戏
void ChessItem::slotGameStop()
{
    gameStatus = false;
}
