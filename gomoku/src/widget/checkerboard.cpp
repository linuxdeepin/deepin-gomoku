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
#include "checkerboard.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

#define BACKGROUND_MARGIN 40 //棋盘边距
#define LINE_NUM 13 //棋盘线条数
#define PIECES_SIZE 44 //棋盘格子宽度
const int kPosDelta = 3; //显示交叉点可落子范围

checkerboard::checkerboard(QWidget *parent)
    : QGraphicsView(parent)
{
    setContentsMargins(QMargins(0, 0, 0, 0));
    setAutoFillBackground(true);
    setMouseTracking(true);
    initBackground();
}

checkerboard::~checkerboard()
{
}

//初始化背景
void checkerboard::initBackground()
{
    DPalette palette(this->palette());
    QPixmap backgroundImage(":/resources/checkerboard.svg");
    setFixedSize(backgroundImage.size());
    palette.setColor(QPalette::Normal, QPalette::Background, Qt::transparent);
    palette.setBrush(DPalette::Background, QBrush(backgroundImage));
    setPalette(palette);
}

//绘制棋盘
void checkerboard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    QPen pen;
    QColor penColor("#000000");
    penColor.setAlphaF(0.25);
    pen.setColor(penColor);
    painter.setPen(pen);
    for (int i = 0; i < LINE_NUM; i++) {
        //横线
        painter.drawLine(BACKGROUND_MARGIN, BACKGROUND_MARGIN + PIECES_SIZE + PIECES_SIZE * i,
                         width() - BACKGROUND_MARGIN, BACKGROUND_MARGIN + PIECES_SIZE + PIECES_SIZE * i);
        //竖线
        painter.drawLine(BACKGROUND_MARGIN + PIECES_SIZE + PIECES_SIZE * i, BACKGROUND_MARGIN,
                         BACKGROUND_MARGIN + PIECES_SIZE + PIECES_SIZE * i, height() - BACKGROUND_MARGIN);
        if (i == LINE_NUM / 2) {
            //天元点绘制
            painter.save();
            painter.setPen("#86582E");
            painter.setBrush(QColor("#86582E"));
            painter.drawEllipse((width() / 2) - 4, (height() / 2) - 4, 8, 8);
            painter.restore();
        }
    }
    painter.restore();

    if (clickPosRow > 0 && clickPosRow < LINE_NUM &&
            clickPosCol > 0 && clickPosCol < LINE_NUM) {
        painter.save();
        painter.setBrush(QColor(Qt::white));
        painter.drawRect(BACKGROUND_MARGIN + PIECES_SIZE * clickPosCol - 6 / 2, BACKGROUND_MARGIN + PIECES_SIZE * clickPosRow - 6 / 2, 6, 6);
        painter.restore();
    }

    QGraphicsView::paintEvent(event);
}

void checkerboard::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

//    qInfo() << x << y;
    // 棋盘边缘不能落子
    if (x >= BACKGROUND_MARGIN + PIECES_SIZE / 2 &&
            x < size().width() - BACKGROUND_MARGIN &&
            y >= BACKGROUND_MARGIN + PIECES_SIZE / 2 &&
            y < size().height() - BACKGROUND_MARGIN) {
        // 获取最近的左上角的点
        int col = x / PIECES_SIZE;
        int row = y / PIECES_SIZE;

        int leftTopPosX = BACKGROUND_MARGIN + PIECES_SIZE * col;
        int leftTopPosY = BACKGROUND_MARGIN + PIECES_SIZE * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = static_cast<int>(qSqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY)));
        if (len < kPosDelta) {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = static_cast<int>(qSqrt((x - leftTopPosX - PIECES_SIZE) * (x - leftTopPosX - PIECES_SIZE) + (y - leftTopPosY) * (y - leftTopPosY)));
        if (len < kPosDelta) {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = static_cast<int>(qSqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - PIECES_SIZE) * (y - leftTopPosY - PIECES_SIZE)));
        if (len < kPosDelta) {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = static_cast<int>(qSqrt((x - leftTopPosX - PIECES_SIZE) * (x - leftTopPosX - PIECES_SIZE) + (y - leftTopPosY - PIECES_SIZE) * (y - leftTopPosY - PIECES_SIZE)));
        if (len < kPosDelta) {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    // 存了坐标后也要重绘
    update();
    QGraphicsView::mouseMoveEvent(event);
}
