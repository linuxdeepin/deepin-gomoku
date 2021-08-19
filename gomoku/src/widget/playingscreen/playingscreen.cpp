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
#include "playingscreen.h"

#include <QPainter>

PlayingScreen::PlayingScreen(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

void PlayingScreen::setCurrentPlay(bool player)
{
    currentPlayer = player;
    update();
}

QRectF PlayingScreen::boundingRect() const
{
    return QRectF(0, 0, 265, 155);
}

void PlayingScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor("#ffdb9e"));
    if (currentPlayer) {
        painter->drawText(QPointF(60, 70), "您的回合！");
    } else {
        painter->drawText(QPointF(60, 70), "小U正在思考...");
    }
    painter->restore();

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPointF(30, 104), QPixmap(":/resources/playingscreen/currentplayer.svg"));
    if (currentPlayer) {
        painter->drawPixmap(QPointF(85, 116), QPixmap(":/resources/playingscreen/user_playing.svg"));
    } else {
        painter->drawPixmap(QPointF(85, 118), QPixmap(":/resources/playingscreen/ai_playing.svg"));
    }
    painter->drawPixmap(QPointF(122, 158), QPixmap(":/resources/playingscreen/chess_black.svg"));

    painter->drawPixmap(QPointF(176, 120), QPixmap(":/resources/playingscreen/anotherplayer.svg"));
    if (currentPlayer) {
        painter->drawPixmap(QPointF(190, 132), QPixmap(":/resources/playingscreen/ai_notplay.svg"));
    } else {
        painter->drawPixmap(QPointF(191, 130), QPixmap(":/resources/playingscreen/user_notplay.svg"));
    }
    painter->drawPixmap(QPointF(224, 158), QPixmap(":/resources/playingscreen/chess_white.svg"));

    painter->restore();
}
