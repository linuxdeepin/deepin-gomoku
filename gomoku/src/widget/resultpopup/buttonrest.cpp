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
#include "buttonrest.h"

#include <QPainter>
#include <QMouseEvent>

#include <DHiDPIHelper>

Buttonrest::Buttonrest(QWidget *parent)
    : DWidget(parent)
    , winRestNormal(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/win_rest_normal.svg"))
    , winRestHover(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/win_rest_hover.svg"))
    , winRestPress(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/win_rest_press.svg"))
    , failRestNormal(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/fail_rest_normal.svg"))
    , failRestHover(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/fail_rest_hover.svg"))
    , failRestPress(DHiDPIHelper::loadNxPixmap(":/resources/resultpopup/fail_rest_press.svg"))
    , mResult(false)
{
    //设置大小
    setFixedSize(160, 42);
}

Buttonrest::~Buttonrest()
{

}

/**
 * @brief Buttonrest::setResult 设置对局结果
 * @param result 结果:true为赢,false为输
 */
void Buttonrest::setResult(bool result)
{
    mResult = result;
    //根据输赢情况设置不同的图片
    if (mResult) {
        currentPixmap = winRestNormal;
    } else {
        currentPixmap = failRestNormal;
    }
}

/**
 * @brief Buttonrest::mousePressEvent 鼠标点击事件
 * @param event
 */
void Buttonrest::mousePressEvent(QMouseEvent *event)
{
    buttonPressed = true;
    if (mResult) {
        currentPixmap = winRestPress;
    } else {
        currentPixmap = failRestPress;
    }
    DWidget::mousePressEvent(event);
    update();
}

/**
 * @brief Buttonrest::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void Buttonrest::mouseReleaseEvent(QMouseEvent *event)
{
    buttonPressed = false;
    if (mResult) {
        currentPixmap = winRestNormal;
    } else {
        currentPixmap = failRestNormal;
    }
    if (this->rect().contains(event->pos()))
        emit signalButtonRestClicked();
    DWidget::mouseReleaseEvent(event);
    update();
}

/**
 * @brief Buttonrest::enterEvent 鼠标进入区域事件
 * @param event
 */
void Buttonrest::enterEvent(QEvent *event)
{
    if (mResult) {
        currentPixmap = winRestHover;
    } else {
        currentPixmap = failRestHover;
    }
    DWidget::enterEvent(event);
    update();
}

/**
 * @brief Buttonrest::leaveEvent 鼠标离开区域事件
 * @param event
 */
void Buttonrest::leaveEvent(QEvent *event)
{
    if (mResult) {
        currentPixmap = winRestNormal;
    } else {
        currentPixmap = failRestNormal;
    }
    DWidget::leaveEvent(event);
    update();
}

/**
 * @brief Buttonrest::paintEvent 绘图事件
 * @param event
 */
void Buttonrest::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), currentPixmap);
    QFont font;
    font.setFamily("Yuanti SC");
    font.setWeight(QFont::Medium);
    font.setPixelSize(14);
    painter.setPen("#492c04");
    if (buttonPressed) {
        if (currentPixmap == winRestPress) {
            painter.setPen("#ffdb9e");
        } else if (currentPixmap == failRestPress) {
            painter.setPen("#d2d2d2");
        }
    }
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, tr("Have a Rest"));
    painter.restore();
    DWidget::paintEvent(event);
}
