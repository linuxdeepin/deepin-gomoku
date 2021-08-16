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
#include "buttonbase.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>

buttonbase::buttonbase(QWidget *parent)
    : DFrame(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setFixedSize(204, 64);
    setAutoFillBackground(true);
    setMouseTracking(true);
    initBackground();
//    setFrameStyle(QFrame::Sunken);
//    setStyle(QStyle::PE_FrameDefaultButton);
}

void buttonbase::initBackground()
{
    DPalette palette;
    QPixmap backgroundImage(":/resources/button.svg");
    palette.setColor(QPalette::Background, Qt::transparent);
    palette.setBrush(QPalette::Background, QBrush(backgroundImage));
    setPalette(palette);
}

//鼠标移动事件，保证单机移动后不会移动整个窗口
void buttonbase::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

//鼠标release
void buttonbase::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        return;

    if (!this->rect().contains(event->pos())) {
        mouseReleaseStatus = false;
    } else {
        mouseReleaseStatus = true;
    }
    mouseRelease();
    DFrame::mouseReleaseEvent(event);
}

void buttonbase::mousePressEvent(QMouseEvent *event)
{
    qInfo() << "000000";
    DFrame::mousePressEvent(event);
}

void buttonbase::paintEvent(QPaintEvent *event)
{
//    qInfo() << "&&&&&&&&&";
//    QPainter painter(this);
//    QStyleOptionButton option;
//    option.
//    option.initFrom(this);

//    option.backgroundColor = palette().color(QPalette::Background);
//    option.text =

//    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);
//    QPixmap backgroundImage(":/resources/button.svg");
//    painter.setBrush(Qt::red);
//    painter.drawRect(rect());
//    painter.setBrush(backgroundImage);
//    painter.drawRect(rect());
    DFrame::paintEvent(event);
}

void buttonbase::mouseRelease()
{
}
