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
#include "closepopup.h"

#include <DHiDPIHelper>

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Closepopup::Closepopup(QWidget *parent)
    : DWidget(parent)
    , closePixmap(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/close.svg"))
{
    //设置大小
    setFixedSize(35, 35);
}

/**
 * @brief Closepopup::mousePressEvent 鼠标点击事件
 * @param event
 */
void Closepopup::mousePressEvent(QMouseEvent *event)
{
    DWidget::mousePressEvent(event);
}

/**
 * @brief Closepopup::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void Closepopup::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->rect().contains(event->pos()))
        emit signalCloseClicked();
    DWidget::mouseReleaseEvent(event);
}

/**
 * @brief Closepopup::paintEvent 绘图事件
 * @param event
 */
void Closepopup::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), closePixmap);
    painter.restore();
    DWidget::paintEvent(event);
}
