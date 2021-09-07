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
#ifndef BTSTARTPAUSE_H
#define BTSTARTPAUSE_H

#include "buttonitem.h"

class BTStartPause : public ButtonItem
{
    Q_OBJECT
public:
    explicit BTStartPause(QGraphicsItem *parent = nullptr);
    ~BTStartPause() override;

    void setButtonStatus(bool status);
    void setGameOverStatus(bool gameover);
    bool getButtonStatus();

signals:
    void signalGameStart(); //游戏开始信号
    void signalGameStop(); //游戏暂停信号
    void signalGameContinue(); //游戏继续信号

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setNotFirstGame() override;

private:
    void buttonFunction() override;

private:
    QPixmap beginPixmap; //开始按钮图片
    QPixmap stopPixmap; //暂停按钮图片
    bool gameOverStatus = false; //游戏结束标志
};

#endif // BTSTARTPAUSE_H
