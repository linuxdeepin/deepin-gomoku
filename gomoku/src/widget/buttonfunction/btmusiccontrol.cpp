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
#include "btmusiccontrol.h"

BTMusicControl::BTMusicControl(QGraphicsItem *parent)
    : ButtonItem(parent)
    , voicePixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/voice.svg"))
    , voiceOffPixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/voiceoff.svg"))
{
}

BTMusicControl::~BTMusicControl()
{

}

QRectF BTMusicControl::boundingRect() const
{
    return QRectF(this->scene()->width() * buttonPosWidth,
                  this->scene()->height() * buttonMusicControlPosHeight,
                  200,
                  60);
}

void BTMusicControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rectX = this->boundingRect().x(); //矩形起始位置X
    qreal rectY = this->boundingRect().y(); //矩形起始位置Y
    qreal rectWidth = this->boundingRect().width(); //矩形宽度
    qreal rectHeight = this->boundingRect().height(); //矩形高度

    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPointF(rectX, rectY), backgrounePix);
    painter->restore();

    painter->save();
    painter->setPen(Qt::NoPen);
    //声音控制图片
    if (mouseReleased) {
        painter->drawPixmap(QPointF(rectX + rectWidth * pixmapPosWidth,
                                    rectY + rectHeight * pixmapPosHeight),
                            voicePixmap);
    } else {
        painter->drawPixmap(QPointF(rectX + rectWidth * pixmapPosWidth,
                                    rectY + rectHeight * pixmapPosHeight),
                            voiceOffPixmap);
    }
    painter->restore();

    painter->save();
    QFont font;
    font.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Black);
    font.setPixelSize(20);
    font.setBold(true);
    painter->setFont(font);
    if (pressStatus) {
        painter->setPen(QColor("#ffdb9e"));
    } else {
        painter->setPen(QColor("#024526"));
    }
    if (mouseReleased) {
        painter->drawText(QPointF(rectX + rectWidth * musicTextPosWidth,
                                  rectY + rectHeight * textPosHeight),
                          tr("Sound Off"));
    } else {
        painter->drawText(QPointF(rectX + rectWidth * musicTextPosWidth,
                                  rectY + rectHeight * textPosHeight),
                          tr("Sound On"));
    }
    painter->restore();
}

/**
 * @brief BTReplay::setNotFirstGame 设置是否第一次开始游戏
 */
void BTMusicControl::setNotFirstGame()
{
//    mouseReleased = true;
    buttonFunction();
    update();
}

//按钮功能
void BTMusicControl::buttonFunction()
{
    //控制音乐
    emit signalMusic(mouseReleased);
}
