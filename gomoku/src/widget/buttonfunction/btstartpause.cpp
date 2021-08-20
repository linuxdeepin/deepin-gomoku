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
{
}

BTStartPause::~BTStartPause()
{
}

QRectF BTStartPause::boundingRect() const
{
    return ButtonItem::boundingRect();
}

void BTStartPause::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ButtonItem::paint(painter, option, widget);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->save();
    painter->setPen(Qt::NoPen);
    if (mouseReleased) {
        painter->drawPixmap(QPointF(30, 20), QPixmap(":/resources/icon/stop.svg"));
    } else {
        painter->drawPixmap(QPointF(30, 20), QPixmap(":/resources/icon/begin.svg"));
    }
    painter->restore();

    painter->save();
    QFont font;
    font.setFamily("Yuanti SC");
    font.setPointSize(16);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor("#024526"));
    if (mouseReleased) {
        painter->drawText(QPointF(80, 40), "暂停");
    } else {
        painter->drawText(QPointF(80, 40), "开始");
    }
    painter->restore();
}

//按钮功能
void BTStartPause::buttonFunction()
{
    //开始暂停功能
    if (mouseReleased) {
        //暂停游戏
        emit signalGameStop();
    } else {
        //开始游戏
        emit signalGameStart();
    }
}
