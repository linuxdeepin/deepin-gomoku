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
#include "checkerboarditem.h"
#include "constants.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

const int line_num = 13;

CheckerboardItem::CheckerboardItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , checkerboardPixmap(DHiDPIHelper::loadNxPixmap(":/resources/checkerboard.svg"))
{
}

CheckerboardItem::~CheckerboardItem()
{
}

QRectF CheckerboardItem::boundingRect() const
{
    //设置棋盘位置和大小
    return QRectF(this->scene()->width() * CheckerboardPosWidth,
                  this->scene()->height() * CheckerboardPosHeight,
                  checkerboardPixmap.width(),
                  checkerboardPixmap.height());
}

void CheckerboardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(QPointF(boundingRect().x(), boundingRect().y()), checkerboardPixmap);
    painter->restore();

    painter->save();
    QPen pen;
    QColor penColor("#000000");
//    penColor.setAlphaF(0.6); // 不带线棋盘透明度
    penColor.setAlphaF(0.25); //带线棋盘透明度
    pen.setColor(penColor);
    painter->setPen(pen);
    for (int i = 0; i < line_num; i++) {
        //655为实测宽度
        //横线
        int hLineStartX = static_cast<int>(this->scene()->width() * CheckerboardPosWidth //棋盘左边界到整个页面左边界的距离
                                           + backgrond_margin); //线边界到棋盘边界的距离
        int hLineStartY = static_cast<int>(this->scene()->height() * CheckerboardPosHeight //棋盘上边界到整个页面上边界的距离
                                           + backgrond_margin //线边界到棋盘边界的距离
                                           + chess_size //最上面空了一行, 所以添加一行棋格的宽度
                                           + chess_size * i); //依次递增棋格宽度
        int hLineEndX = static_cast<int>(this->scene()->width() * CheckerboardPosWidth //棋盘左边界到整个页面左边界的距离
                                         + checkerboardPixmap.width() //整个棋盘的宽度
                                         -  backgrond_margin); //线边界到棋盘边界的距离
        int hLineEndY = static_cast<int>(this->scene()->height() * CheckerboardPosHeight //棋盘上边界到整个页面上边界的距离
                                         + backgrond_margin //线边界到棋盘边界的距离
                                         + chess_size //最上面空了一行, 所以添加一行棋格的宽度
                                         + chess_size * i); //依次递增棋格宽度
        painter->drawLine(hLineStartX, hLineStartY, hLineEndX, hLineEndY);
        //竖线
        int vLineStartX = static_cast<int>(this->scene()->width() * CheckerboardPosWidth //棋盘左边界到整个页面左边界的距离
                                           + backgrond_margin //线边界到棋盘边界的距离
                                           + chess_size //最左面空了一行, 所以添加一行棋格的宽度
                                           + chess_size * i); //依次递增棋格宽度
        int vLineStartY = static_cast<int>(this->scene()->height() * CheckerboardPosHeight //棋盘上边界到整个页面上边界的距离
                                           + backgrond_margin); //线边界到棋盘边界的距离
        int vLineEndX = static_cast<int>(this->scene()->width() * CheckerboardPosWidth //棋盘左边界到整个页面左边界的距离
                                         + backgrond_margin //线边界到棋盘边界的距离
                                         + chess_size //最左面空了一行, 所以添加一行棋格的宽度
                                         + chess_size * i); //依次递增棋格宽度
        int vLineEndY = static_cast<int>(this->scene()->height() * CheckerboardPosHeight //棋盘上边界到整个页面上边界的距离
                                         + checkerboardPixmap.height() //整个棋盘的高度
                                         - backgrond_margin); //线边界到棋盘边界的距离

        painter->drawLine(vLineStartX, vLineStartY, vLineEndX, vLineEndY);
        if (i == line_num / 2) {
            //天元点绘制
            painter->save();
            painter->setPen("#86582E");
            painter->setBrush(QColor("#86582E"));
            //6为偏移量,调整位置
            int roundX = static_cast<int>(this->scene()->width() * CheckerboardPosWidth
                                          + backgrond_margin
                                          + chess_size
                                          + chess_size * i
                                          - 5
                                          - 1); //为保证中心的偏移量
            int roundY = static_cast<int>(this->scene()->height() * CheckerboardPosHeight
                                          + backgrond_margin
                                          + chess_size
                                          + chess_size * i
                                          - 5
                                          - 1); //为保证中心的偏移量
            painter->drawEllipse(roundX, roundY, 10, 10);
            painter->restore();
        }
    }
    painter->restore();
}
