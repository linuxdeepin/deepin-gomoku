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
    , buttonNormal(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/normal.svg"))
    , buttonHover(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/hover.svg"))
    , buttonPress(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/press.svg"))
{
    setFixedSize(32, 32);
    currentPixmap = buttonNormal;
}

/**
 * @brief Closepopup::mousePressEvent 鼠标点击事件
 * @param event
 */
void Closepopup::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        currentPixmap = buttonPress;
        DWidget::mouseReleaseEvent(event);
        update();
    }
}

/**
 * @brief Closepopup::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void Closepopup::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        currentPixmap = buttonNormal;
        if (this->rect().contains(event->pos()))
            emit signalCloseClicked();
        DWidget::mouseReleaseEvent(event);
        update();
    }
}
/**
 * @brief Closepopup::enterEvent
 * @param event
 */
void Closepopup::enterEvent(QEvent *event)
{
    currentPixmap = buttonHover;
    DWidget::enterEvent(event);
    update();
}

/**
 * @brief Closepopup::leaveEvent
 * @param event
 * 移出事件
 */
void Closepopup::leaveEvent(QEvent *event)
{
    currentPixmap = buttonNormal;
    DWidget::leaveEvent(event);
    update();
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
    painter.drawPixmap(this->rect(), currentPixmap);
    painter.restore();
    DWidget::paintEvent(event);
}
