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
#include "btreplay.h"

BTReplay::BTReplay(QGraphicsItem *parent)
    : ButtonItem(parent)
{
}

BTReplay::~BTReplay()
{

}

QRectF BTReplay::boundingRect() const
{
    return ButtonItem::boundingRect();
}

void BTReplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ButtonItem::paint(painter, option, widget);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPointF(30, 20), QPixmap(":/resources/icon/replay.svg"));
    painter->restore();

    painter->save();
    QFont font;
    font.setFamily("Yuanti SC");
    font.setPointSize(16);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor("#024526"));
    painter->drawText(QPointF(80, 40), "重玩");
    painter->restore();
}

//按钮功能
void BTReplay::buttonFunction()
{
    //重玩功能
    emit signalbuttonReplay();
}
