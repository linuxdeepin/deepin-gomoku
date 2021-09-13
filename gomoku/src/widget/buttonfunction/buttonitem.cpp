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

#include <QTimer>

ButtonItem::ButtonItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , backgrounePix(DHiDPIHelper::loadNxPixmap(":/resources/function_button/normal.svg"))
    , normalBackgrounePix(DHiDPIHelper::loadNxPixmap(":/resources/function_button/normal.svg"))
    , hoverBackgrounePix(DHiDPIHelper::loadNxPixmap(":/resources/function_button/hover.svg"))
    , PressBackgrounePix(DHiDPIHelper::loadNxPixmap(":/resources/function_button/press.svg"))
{
    setAcceptHoverEvents(true);
}

ButtonItem::~ButtonItem()
{
}

//设置鼠标hover状态图片
void ButtonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    backgrounePix = hoverBackgrounePix;
    update();
    QGraphicsItem::hoverEnterEvent(event);
}

//设置正常图片
void ButtonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    backgrounePix =  normalBackgrounePix;
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

//设置鼠标点击图片
void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        event->accept();
        pressStatus = true;
        backgrounePix = PressBackgrounePix;
        update();
    }
}

//鼠标点击释放，设置图片
void ButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        pressStatus = false;
        if (contains(event->pos())) {
            backgrounePix =  normalBackgrounePix;
            mouseReleased = !mouseReleased;
            //设置一个1ms的延时,保证按钮状态切换
            QTimer::singleShot(1, this, [ = ] {
                buttonFunction();
            });
        }
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

//按钮功能虚函数
void ButtonItem::buttonFunction()
{
}

/**
 * @brief ButtonItem::setNotFirstGame 设置是否第一次开始游戏
 */
void ButtonItem::setNotFirstGame()
{
}
