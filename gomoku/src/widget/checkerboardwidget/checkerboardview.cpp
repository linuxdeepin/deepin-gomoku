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
#include "checkerboardview.h"
#include "checkerboardscene.h"

#include <QHBoxLayout>
#include <QtDebug>
#include <QMouseEvent>

#define BACKGROUND_MARGIN 40 //棋盘边距
#define LINE_NUM 13 //棋盘线条数
#define PIECES_SIZE 44 //棋盘格子宽度

checkerboardview::checkerboardview(QWidget *parent)
    : QGraphicsView(parent)
    , backgroundImage(":/resources/checkerboard.svg")
{
//    setFixedSize(backgroundImage.size());
//    setAutoFillBackground(true);
    setStyleSheet("background: transparent;border:0px");
    setWindowFlags(Qt::FramelessWindowHint);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setMouseTracking(true);
}
