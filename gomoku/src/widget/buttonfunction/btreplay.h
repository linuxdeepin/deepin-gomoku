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
#ifndef BTREPLAY_H
#define BTREPLAY_H

#include "buttonitem.h"

class BTReplay : public ButtonItem
{
    Q_OBJECT
public:
    explicit BTReplay(QGraphicsItem *parent = nullptr);
    ~BTReplay() override;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    void setNotFirstGame() override;

signals:
    void signalbuttonReplay(); //游戏重玩信号

private:
    void buttonFunction() override;

private:
    QPixmap replayPixmap; //重玩按钮图片
    //以下位置参数,根据UI图得来
    const qreal pixmapPosWidth = 0.147; //按钮图标位置占整个scene宽度比例
    const qreal pixmapPosHeight = 0.3125; //按钮图标位置占整个scene高度比例
    const qreal textPosWidth = 0.3921; //按钮文字位置占整个scene宽度比例
    const qreal textPosHeight = 0.625; //按钮文字位置占整个scene高度比例
};

#endif // BTREPLAY_H
