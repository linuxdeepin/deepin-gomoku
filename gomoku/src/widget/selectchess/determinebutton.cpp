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
#include "determinebutton.h"
#include "globaltool.h"

#include <QPainter>
#include <QMouseEvent>

#include <DHiDPIHelper>

Determinebutton::Determinebutton(QWidget *parent)
    : DWidget(parent)
    , buttonNormal(DHiDPIHelper::loadNxPixmap(":/resources/chessselected/button_normal.svg"))
    , buttonHover(DHiDPIHelper::loadNxPixmap(":/resources/chessselected/button_hover.svg"))
    , buttonPress(DHiDPIHelper::loadNxPixmap(":/resources/chessselected/button_press.svg"))
{
    setFixedSize(334, 46);
    currentPixmap = buttonNormal;
}

/**
 * @brief Determinebutton::mousePressEvent 鼠标点击事件
 * @param event
 */
void Determinebutton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        buttonPressed = true;
        currentPixmap = buttonPress;
        DWidget::mousePressEvent(event);
        update();
    }
}

/**
 * @brief Determinebutton::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void Determinebutton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        buttonPressed = false;
        currentPixmap = buttonNormal;
        //发送鼠标点击信号
        if (this->rect().contains(event->pos()))
            emit signalButtonOKClicked();
        DWidget::mouseReleaseEvent(event);
        update();
    }
}

/**
 * @brief Determinebutton::enterEvent 鼠标进入区域事件
 * @param event
 */
void Determinebutton::enterEvent(QEvent *event)
{
    currentPixmap = buttonHover;
    DWidget::enterEvent(event);
    update();
}

/**
 * @brief Determinebutton::leaveEvent 鼠标离开区域事件
 * @param event
 */
void Determinebutton::leaveEvent(QEvent *event)
{
    currentPixmap = buttonNormal;
    DWidget::leaveEvent(event);
    update();
}

/**
 * @brief Determinebutton::paintEvent 绘图事件
 * @param event
 */
void Determinebutton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), currentPixmap);
    QFont font;
    font.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Bold);
    font.setPixelSize(20);
    painter.setPen("#492c04");
    if (buttonPressed) {
        painter.setPen("#ffdb9e");
    }
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, tr("OK"));
    painter.restore();
    DWidget::paintEvent(event);
}
