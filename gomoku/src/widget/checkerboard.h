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
#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <DWidget>
#include <DPalette>
#include <QGraphicsView>

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

class checkerboard : public QGraphicsView
{
public:
    explicit checkerboard(QWidget *parent = nullptr);
    ~checkerboard() override;

private:
    void initBackground();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    int clickPosRow = 0;
    int clickPosCol  = 0;
};

#endif // CHECKERBOARD_H
