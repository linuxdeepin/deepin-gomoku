/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     liyucheng <liyucheng@uniontech.com>
   *
   * Maintainer:  liyucheng <liyucheng@uniontech.com>
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
#include "exitbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <DHiDPIHelper>

ExitButton::ExitButton(QWidget *parent)
    : DWidget(parent)
    , buttonNormal(DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/exit-normal.svg"))
    , buttonHover(DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/exit-hover.svg"))
    , buttonPress(DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/exit-press.svg"))
{
    setFixedSize(160, 42); //设置按钮大小
    currentPixmap = buttonNormal;
}

/**
 * @brief CancelButton::mouseReleaseEvent
 * @param event
 * 鼠标按压事件
 */
void ExitButton::mousePressEvent(QMouseEvent *event)
{
    buttonPressed = true;
    currentPixmap = buttonPress;
    DWidget::mousePressEvent(event);
    update();
}

/**
 * @brief CancelButton::mouseReleaseEvent
 * @param event
 * 鼠标释放事件
 */
void ExitButton::mouseReleaseEvent(QMouseEvent *event)
{
    buttonPressed = false;
    currentPixmap = buttonNormal;
    if (this->rect().contains(event->pos()))
        emit signalButtonOKClicked();
    DWidget::mouseReleaseEvent(event);
    update();
}

/**
 * @brief CancelButton::mouseReleaseEvent
 * @param event
 * 移入事件
 */
void ExitButton::enterEvent(QEvent *event)
{
    currentPixmap = buttonHover;
    DWidget::enterEvent(event);
    update();
}

/**
 * @brief CancelButton::mouseReleaseEvent
 * @param event
 * 移出事件
 */
void ExitButton::leaveEvent(QEvent *event)
{
    currentPixmap = buttonNormal;
    DWidget::leaveEvent(event);
    update();
}

/**
 * @brief CancelButton::mouseReleaseEvent
 * @param event
 * 重写绘画事件
 */
void ExitButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), currentPixmap);
    QFont font;
    font.setFamily("Yuanti SC");
    font.setWeight(QFont::Medium);
    font.setPixelSize(16);
    painter.setPen("#492c04"); //字体颜色
    if (buttonPressed) {
        painter.setPen("#ffdb9e");
    }
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, tr("Exit"));
    painter.restore();
    DWidget::paintEvent(event);
}


