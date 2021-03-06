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
#include "globaltool.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <DHiDPIHelper>
#include <QDebug>

ExitButton::ExitButton(QWidget *parent)
    : QWidget(parent)
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
    if (event->button() & Qt::LeftButton) {
        buttonPressed = true;
        currentPixmap = buttonPress;
        DWidget::mousePressEvent(event);
        update();
    }
}

/**
 * @brief CancelButton::mouseReleaseEvent
 * @param event
 * 鼠标释放事件
 */
void ExitButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        buttonPressed = false;
        currentPixmap = buttonNormal;
        if (this->rect().contains(event->pos()))
            emit signalButtonOKClicked();
        DWidget::mouseReleaseEvent(event);
        update();
    }
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
    buttonPressed = false;
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
    font.setFamily(Globaltool::instacne()->loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Bold);
    font.setPixelSize(Globaltool::instacne()->getFontSize().dialogButton
                      - Globaltool::instacne()->getFontSize().dialogOffset); //阻塞弹窗按钮字体大小为17
    painter.setPen("#6e3b3b"); //字体颜色
    if (buttonPressed) {
        painter.setPen("#ffdb9e");
    }
    painter.setFont(font);
    QFontMetrics fontMetrics(font);
    QString text = tr("Exit");
    if (fontMetrics.width(text) > (this->rect().width() - 20)) {
        setToolTip(text);
        text = fontMetrics.elidedText(text, Qt::ElideRight, this->rect().width() - 20);
    }
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
    painter.restore();
    DWidget::paintEvent(event);
}


