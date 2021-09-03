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
#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include "constants.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QObject>

#include <DHiDPIHelper>

DWIDGET_USE_NAMESPACE

class ButtonItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ButtonItem(QGraphicsItem *parent = nullptr);
    ~ButtonItem() override;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void buttonFunction();

    bool mouseReleased = true; //鼠标是否释放
    bool gamePlaying = false;
    //以下位置参数,根据UI图得来
    const qreal pixmapPosWidth = 0.147; //按钮图标位置占整个scene宽度比例
    const qreal pixmapPosHeight = 0.3125; //按钮图标位置占整个scene高度比例
    const qreal textPosWidth = 0.3921; //按钮文字位置占整个scene宽度比例
    const qreal textPosHeight = 0.625; //按钮文字位置占整个scene高度比例
private:
    QPixmap backgrounePix; //需要显示的背景图片
    QPixmap normalBackgrounePix; //正常的背景图片
    QPixmap hoverBackgrounePix; //hover状态的背景图片
    QPixmap PressBackgrounePix; //press状态的背景图片
    bool hoverStatus = false; //hover状态标志
    bool pressStatus = false; //鼠标点击状态标志
};

#endif // BUTTONITEM_H
