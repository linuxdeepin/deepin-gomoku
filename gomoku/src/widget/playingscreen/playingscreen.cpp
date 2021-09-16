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
#include "globaltool.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

PlayingScreen::PlayingScreen(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , currentPlayer(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/currentplayer.svg"))
    , aiPlaying(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/ai_playing.svg"))
    , userPlaying(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/user_playing.svg"))
    , chessBlack(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/chess_black.svg"))
    , chessWhite(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/chess_white.svg"))
    , anotherPlayer(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/anotherplayer.svg"))
    , userNotPlay(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/user_notplay.svg"))
    , aiNotPlay(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/ai_notplay.svg"))
{
    sceneWidth = 300;
    sceneHeight = 100;
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
    gameOverStatus = false;
    update();
}

/**
 * @brief PlayingScreen::setGameOverStatus 设置游戏结束标志
 */
void PlayingScreen::setGameOverStatus()
{
    gameOverStatus = true;
}

QRectF PlayingScreen::boundingRect() const
{
    //对局详情所在rect大小
    return QRectF(this->scene()->width() * playingScreenPosWidth,
                  this->scene()->height() * playingScreenPosHeight,
                  sceneWidth,
                  sceneHeight);
}

void PlayingScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

//    painter->drawRect(boundingRect());

    //图片或文字位置通过起始位置+偏移量的方式设置
    qreal rectX = this->boundingRect().x();
    qreal rectY = this->boundingRect().y();
    qreal rectWidth = this->boundingRect().width();
    qreal rectHeight = this->boundingRect().height();

    painter->setRenderHint(QPainter::Antialiasing);

    if (gamePlaying) {
        if (gameOverStatus) {
            painter->save();
            QFont gameOverFont;
            gameOverFont.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
            gameOverFont.setWeight(QFont::Bold);
            gameOverFont.setPixelSize(24);
            gameOverFont.setBold(true);
            painter->setFont(gameOverFont);
            painter->setPen(QColor("#ffdb9e"));


            painter->drawText(QRect(static_cast<int>(rectX),
                                    static_cast<int>(rectY + rectHeight * chessPlayingTextPosHeight),
                                    static_cast<int>(rectWidth),
                                    static_cast<int>(rectHeight)),
                              Qt::AlignHCenter | Qt::TextWordWrap,
                              tr("Game Over!"));
            painter->restore();
        } else {
            //游戏开始后
            painter->save();
            QFont font;
            int fontSize = 24;
            font.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
            font.setWeight(QFont::Black);
            font.setPixelSize(fontSize);
            painter->setFont(font);
            painter->setPen(QColor("#ffdb9e"));
            QString playerText;
            if (AIPlayer) {
                playerText = Globaltool::AutoFeed(tr("I am thinking..."), fontSize,
                                                  static_cast<int>(rectWidth * (1 - chessPlayingTextPosWidth)));
            } else {
                playerText = Globaltool::AutoFeed(tr("Place your chess piece..."), fontSize,
                                                  static_cast<int>(rectWidth * (1 - chessPlayingTextPosWidth)));
            }
            painter->drawText(QRect(static_cast<int>(rectX),
                                    static_cast<int>(rectY + rectHeight * chessPlayingTextPosHeight),
                                    static_cast<int>(rectWidth),
                                    static_cast<int>(rectHeight)),
                              Qt::AlignHCenter | Qt::TextWordWrap,
                              playerText);
            painter->restore();
        }

        painter->save();
        painter->setPen(Qt::NoPen);
        //当前旗手
        painter->drawPixmap(QPointF(rectX + rectWidth * currentPlayerPosWidth,
                                    rectY + rectHeight * currentPlayerPosHeight),
                            currentPlayer);
        if (AIPlayer) {
            painter->drawPixmap(QPointF(rectX + rectWidth * aiPlayingPosWidth,
                                        rectY + rectHeight * aiPlayingPosHeight),
                                aiPlaying);
        } else {
            painter->drawPixmap(QPointF(rectX + rectWidth * userPlayingPosWidth,
                                        rectY + rectHeight * userPlayingPosHeight),
                                userPlaying);
        }
        if (currentChessColro == chess_black) {
            painter->drawPixmap(QPointF(rectX + rectWidth * currentPlayerChessPosWidth,
                                        rectY + rectHeight * currentPlayerchessPosHeight),
                                chessBlack);
        } else {
            painter->drawPixmap(QPointF(rectX + rectWidth * currentPlayerChessPosWidth,
                                        rectY + rectHeight * currentPlayerchessPosHeight),
                                chessWhite);
        }
        //另一方旗手
        painter->drawPixmap(QPointF(rectX + rectWidth * anotherPlayerPosWidth,
                                    rectY + rectHeight * anotherPlayerPosHeight),
                            anotherPlayer);
        if (AIPlayer) {
            painter->drawPixmap(QPointF(rectX + rectWidth * userNotPlayPosWidth,
                                        rectY + rectHeight * userNotPlayPosHeight),
                                userNotPlay);
        } else {
            painter->drawPixmap(QPointF(rectX + rectWidth * aiNotPlayPosWidth,
                                        rectY + rectHeight * aiNotPlayPosHeight),
                                aiNotPlay);
        }
        if (currentChessColro == chess_black) {
            painter->drawPixmap(QPointF(rectX + rectWidth * anotherPlayerChessPosWidth,
                                        rectY + rectHeight * anotherPlayerChessPosHeight),
                                chessWhite);
        } else {
            painter->drawPixmap(QPointF(rectX + rectWidth * anotherPlayerChessPosWidth,
                                        rectY + rectHeight * anotherPlayerChessPosHeight),
                                chessBlack);
        }

        painter->restore();
    } else if (!gamePlaying) {
        //游戏还未开始
        painter->save();
        QFont welcomeFont;
        welcomeFont.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
        welcomeFont.setWeight(QFont::Black);
        welcomeFont.setPixelSize(30);
        painter->setFont(welcomeFont);
        painter->setPen(QColor("#ffdb9e"));
        painter->drawText(QRect(static_cast<int>(rectX),
                                static_cast<int>(rectY + rectHeight * sWelcomePosHeight1),
                                static_cast<int>(rectWidth),
                                static_cast<int>(rectHeight)),
                          Qt::AlignHCenter,
                          tr("Welcome"));
        painter->restore();
    }
}

//游戏是否开始
void PlayingScreen::slotStartGame()
{
    gamePlaying = true;
    //游戏开始后需要显示旗手,增加高度
    sceneHeight = 200;
    update();
}

/**
 * @brief PlayingScreen::slotNewGame 游戏状态为新游戏时重置右侧显示
 */
void PlayingScreen::slotNewGame()
{
    gamePlaying = false;
    AIPlayer = false;
    gamePlaying = false;
    gameOverStatus = false;
    sceneHeight = 100;
    currentChessColro = 0;
}
