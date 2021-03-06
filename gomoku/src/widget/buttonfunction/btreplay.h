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

    inline qreal & getPosHeight() {return posHeight;}
    inline qreal getFirstGamePosHeight() {return firstGamePosHeight;}

    void setButtonState(bool state);

    void setNotFirstGame() override;

signals:
    void signalbuttonReplay(); //游戏重玩信号

private:
    void buttonFunction() override;

private:
    QPixmap replayPixmap; //重玩按钮图片
    qreal posHeight = 0.3425; //按钮位置占整个scene高度比例
    const qreal firstGamePosHeight = 0.3425;  //游戏未开始时按钮位置占整个scene高度比例
    const qreal notFirstGamePosHeight = 0.444; //重玩功能按钮位置占整个scene高度比例
};

#endif // BTREPLAY_H
