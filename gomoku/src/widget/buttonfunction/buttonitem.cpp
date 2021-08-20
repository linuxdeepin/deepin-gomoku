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
#include "buttonitem.h"

ButtonItem::ButtonItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , backgrounePix(":/resources/function_button/normal.svg")
{
    setAcceptHoverEvents(true);
}

ButtonItem::~ButtonItem()
{

}

QRectF ButtonItem::boundingRect() const
{
    return QRectF(0, 0, backgrounePix.width(), backgrounePix.height());
}

void ButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(backgrounePix);
    painter->drawRect(boundingRect());
    painter->restore();
}

//设置鼠标hover状态图片
void ButtonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    backgrounePix = QPixmap(":/resources/function_button/hover.svg");
    QGraphicsItem::hoverEnterEvent(event);
}

//设置正常图片
void ButtonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    backgrounePix = QPixmap(":/resources/function_button/normal.svg");
    QGraphicsItem::hoverLeaveEvent(event);
}

//设置鼠标点击图片
void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    backgrounePix = QPixmap(":/resources/function_button/press.svg");
    update();
}

//鼠标点击释放，设置图片
void ButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (contains(event->pos())) {
        backgrounePix = QPixmap(":/resources/function_button/normal.svg");
        mouseReleased = !mouseReleased;
        buttonFunction();
    }
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

//按钮功能虚函数
void ButtonItem::buttonFunction()
{
}