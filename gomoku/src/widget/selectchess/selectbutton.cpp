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
#include "selectbutton.h"

#include <DHiDPIHelper>

#include <QPainter>
#include <QDebug>

Selectbutton::Selectbutton(QWidget *parent)
    : QRadioButton(parent)
    , selectNormal(DHiDPIHelper::loadNxPixmap(":/resources/chessselected/radio_unchecked.svg"))
    , selectHover(DHiDPIHelper::loadNxPixmap(":/resources/chessselected/radio_hover.svg"))
    , selectPress(DHiDPIHelper::loadNxPixmap(":/resources/chessselected/radio_checked.svg"))
    , currentStatus(selectNormal)
{
    setFixedSize(30, 30);
    //互斥
    setAutoExclusive(true);
}

/**
 * @brief Selectbutton::enterEvent 鼠标进入区域事件
 * @param event
 */
void Selectbutton::enterEvent(QEvent *event)
{
    currentStatus = selectHover;
    DWidget::enterEvent(event);
    update();
}

/**
 * @brief Selectbutton::leaveEvent 鼠标离开区域事件
 * @param event
 */
void Selectbutton::leaveEvent(QEvent *event)
{
    //如果已经checked, 则设置为press状态
    if (pressStatus) {
        currentStatus = selectPress;
    } else {
        currentStatus = selectNormal;
    }
    DWidget::leaveEvent(event);
    update();
}

/**
 * @brief Selectbutton::paintEvent 绘图函数
 * @param event
 */
void Selectbutton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    //如果被选择,设置选择状态图片
    if (isChecked()) {
        painter.drawPixmap(this->rect(), selectPress);
    } else {
        painter.drawPixmap(this->rect(), currentStatus);
    }
    painter.restore();
    DWidget::paintEvent(event);
}
