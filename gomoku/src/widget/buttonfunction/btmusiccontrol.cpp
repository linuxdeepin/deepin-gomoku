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
    return ButtonItem::boundingRect();
}

void BTMusicControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rectWidth = this->boundingRect().width();
    qreal rectHeight = this->boundingRect().height();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPointF(boundingRect().x(), boundingRect().y()), backgrounePix);
    painter->restore();

    painter->save();
    painter->setPen(Qt::NoPen);
    //声音控制图片
    if (!mouseReleased) {
        painter->drawPixmap(QPointF(rectWidth * pixmapPosWidth, rectHeight * pixmapPosHeight),
                            voiceOffPixmap);
    } else {
        painter->drawPixmap(QPointF(rectWidth * pixmapPosWidth, rectHeight * pixmapPosHeight),
                            voicePixmap);
    }
    painter->restore();

    painter->save();
    QFont font;
    font.setFamily("Yuanti SC");
    font.setPointSize(16);
    font.setBold(true);
    painter->setFont(font);
    if (pressStatus) {
        painter->setPen(QColor("#ffdb9e"));
    } else {
        painter->setPen(QColor("#024526"));
    }
    if (!mouseReleased) {
        painter->drawText(QPointF(rectWidth * musicTextPosWidth, rectHeight * textPosHeight),
                          tr("Open Music"));
    } else {
        painter->drawText(QPointF(rectWidth * musicTextPosWidth, rectHeight * textPosHeight),
                          tr("Close Music"));
    }
    painter->restore();
}

/**
 * @brief BTReplay::setNotFirstGame 设置是否第一次开始游戏
 */
void BTMusicControl::setNotFirstGame()
{
    mouseReleased = false;
    update();
}

//按钮功能
void BTMusicControl::buttonFunction()
{
    //控制音乐
    emit signalMusic(mouseReleased);
}
