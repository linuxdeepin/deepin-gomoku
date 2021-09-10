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
#include "btstartpause.h"

BTStartPause::BTStartPause(QGraphicsItem *parent)
    : ButtonItem(parent)
    , beginPixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/begin.svg"))
    , stopPixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/stop.svg"))
{
    posHeight = firstGamePosHeight;
}

BTStartPause::~BTStartPause()
{
}

/**
 * @brief BTStartPause::setStopStatus 设置按钮状态
 */
void BTStartPause::setButtonStatus(bool status)
{
    //修改按钮图片
    mouseReleased = status;
    if (!firstStartGame) {
        //更新功能
        buttonFunction();
    }
    update();
}

/**
 * @brief BTStartPause::setGameOverStatus 设置游戏结束标志
 */
void BTStartPause::setGameOverStatus(bool gameover)
{
    gameOverStatus = gameover;
    if (!gameOverStatus) {
        firstStartGame = true;
    }
    update();
}

/**
 * @brief BTStartPause::getButtonStatus 获取按钮当前状态
 * @return
 */
bool BTStartPause::getButtonStatus()
{
    return mouseReleased;
}

/**
 * @brief BTStartPause::setFirstGameStatus 设置是否第一次开始游戏
 */
void BTStartPause::setNotFirstGame()
{
    if (qAbs(posHeight - notFirstGamePosHeight) >= (1e-6))
        posHeight = notFirstGamePosHeight;
    firstStartGame = false;
    mouseReleased = false;
    buttonFunction();
    update();
}

QRectF BTStartPause::boundingRect() const
{
    return QRectF(this->scene()->width() * buttonPosWidth,
                  this->scene()->height() * posHeight,
                  backgrounePix.width(),
                  backgrounePix.height());
}

void BTStartPause::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rectX = this->boundingRect().x(); //矩形起始位置X
    qreal rectY = this->boundingRect().y(); //矩形起始位置Y
    qreal rectWidth = this->boundingRect().width(); //矩形宽度
    qreal rectHeight = this->boundingRect().height(); //矩形高度

    QFont font;
    font.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Black);
    font.setPixelSize(20);
    font.setBold(true);

    painter->setRenderHint(QPainter::Antialiasing);

    if (gameOverStatus) {
        painter->save();
        painter->drawPixmap(QPointF(rectX, rectY),
                            DHiDPIHelper::loadNxPixmap(":/resources/function_button/normal.svg"));
        //图片或文字位置通过起始位置+偏移量的方式设置
        painter->drawPixmap(QPointF(rectX + rectWidth *  pixmapPosWidth, //起始X + 向左的偏移量
                                    rectY + rectHeight * pixmapPosHeight), //起始Y + 向下的偏移量
                            beginPixmap);
        painter->setFont(font);
        painter->setPen(QColor("#024526"));
        painter->drawText(QPointF(rectX + rectWidth * textPosWidth,
                                  rectY + rectHeight * textPosHeight),
                          tr("Start"));
        painter->restore();
    } else {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->drawPixmap(QPointF(rectX, rectY), backgrounePix);
        painter->restore();

        painter->save();
        painter->setPen(Qt::NoPen);
        if (firstStartGame) {
            painter->drawPixmap(QPointF(rectX + rectWidth * pixmapPosWidth,
                                        rectY + rectHeight * pixmapPosHeight),
                                beginPixmap);
        } else {
            if (mouseReleased) {
                painter->drawPixmap(QPointF(rectX + rectWidth * pixmapPosWidth,
                                            rectY + rectHeight * pixmapPosHeight),
                                    beginPixmap);
            } else {
                painter->drawPixmap(QPointF(rectX + rectWidth * pixmapPosWidth,
                                            rectY + rectHeight * pixmapPosHeight),
                                    stopPixmap);
            }
        }
        painter->restore();

        painter->save();
        painter->setFont(font);
        if (pressStatus) {
            painter->setPen(QColor("#ffdb9e"));
        } else {
            painter->setPen(QColor("#024526"));
        }
        if (firstStartGame) {
            painter->drawText(QPointF(rectX + rectWidth * textPosWidth,
                                      rectY + rectHeight * textPosHeight),
                              tr("Start"));
        } else {
            if (mouseReleased) {
                painter->drawText(QPointF(rectX + rectWidth * textPosWidth,
                                          rectY + rectHeight * textPosHeight),
                                  tr("Continue"));
            } else {
                painter->drawText(QPointF(rectX + rectWidth * textPosWidth,
                                          rectY + rectHeight * textPosHeight),
                                  tr("Pause"));
            }
        }
        painter->restore();
    }
}

//按钮功能
void BTStartPause::buttonFunction()
{
    if (!firstStartGame) {
        //开始暂停功能
        if (mouseReleased) {
            //暂停游戏
            emit signalGameStop();
        } else {
            //继续游戏
            emit signalGameContinue();
        }
    } else {
        //开始游戏
        emit signalGameStart();
    }
}
