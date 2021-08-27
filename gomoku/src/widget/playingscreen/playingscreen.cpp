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
#include "constants.h"

#include <QPainter>
#include <QDebug>

PlayingScreen::PlayingScreen(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

PlayingScreen::~PlayingScreen()
{

}

//棋子颜色
void PlayingScreen::setCurrentChessColor(bool AIPlaying, int chesscolor)
{
    //当时是否为AI下棋
    AIPlayer = AIPlaying;
    //转换棋子的颜色
    currentChessColro = chesscolor;
    update();
}

QRectF PlayingScreen::boundingRect() const
{
    return QRectF(0, 0, 265, 200);
}

void PlayingScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    if (gamePlaying) {
        //游戏开始后
        painter->save();
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        painter->setFont(font);
        painter->setPen(QColor("#ffdb9e"));
        if (AIPlayer) {
            painter->drawText(QPointF(60, 70), "小U正在思考...");
        } else {
            painter->drawText(QPointF(60, 70), "您的回合！");
        }
        painter->restore();

        painter->save();
        painter->setPen(Qt::NoPen);
        //当前旗手
        painter->drawPixmap(QPointF(30, 104), QPixmap(":/resources/playingscreen/currentplayer.svg"));
        if (AIPlayer) {
            painter->drawPixmap(QPointF(85, 118), QPixmap(":/resources/playingscreen/ai_playing.svg"));
        } else {
            painter->drawPixmap(QPointF(85, 116), QPixmap(":/resources/playingscreen/user_playing.svg"));
        }
        if (currentChessColro == chess_black) {
            painter->drawPixmap(QPointF(122, 158), QPixmap(":/resources/playingscreen/chess_black.svg"));
        } else {
            painter->drawPixmap(QPointF(122, 158), QPixmap(":/resources/playingscreen/chess_white.svg"));
        }
        //另一方旗手
        painter->drawPixmap(QPointF(176, 120), QPixmap(":/resources/playingscreen/anotherplayer.svg"));
        if (AIPlayer) {
            painter->drawPixmap(QPointF(191, 130), QPixmap(":/resources/playingscreen/user_notplay.svg"));
        } else {
            painter->drawPixmap(QPointF(190, 132), QPixmap(":/resources/playingscreen/ai_notplay.svg"));
        }
        if (currentChessColro == chess_black) {
            painter->drawPixmap(QPointF(224, 158), QPixmap(":/resources/playingscreen/chess_white.svg"));
        } else {
            painter->drawPixmap(QPointF(224, 158), QPixmap(":/resources/playingscreen/chess_black.svg"));
        }

        painter->restore();
    } else {
        //游戏还未开始
        painter->save();
        QFont welcomeFont;
        welcomeFont.setPointSize(20);
        welcomeFont.setBold(true);
        painter->setFont(welcomeFont);
        painter->setPen(QColor("#ffdb9e"));
        painter->drawText(QPointF(60, 78), "欢迎来到五子棋");
        painter->restore();

        painter->save();
        QFont startFont1;
        startFont1.setPointSize(16);
        startFont1.setBold(true);
        painter->setFont(startFont1);
        painter->setPen(QColor("#ffffff"));
        painter->drawText(QPointF(64, 142), "点击下面的开始按钮");
        painter->restore();

        painter->save();
        QFont startFont2;
        startFont2.setPointSize(16);
        startFont2.setBold(true);
        painter->setFont(startFont2);
        painter->setPen(QColor("#ffffff"));
        painter->drawText(QPointF(64, 170), "来下棋吧~");
        painter->restore();
    }
}

//游戏是否开始
void PlayingScreen::slotStartGame()
{
    gamePlaying = true;
    update();
}
