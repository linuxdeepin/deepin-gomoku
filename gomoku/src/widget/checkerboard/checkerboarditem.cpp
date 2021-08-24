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
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

const int line_num = 13;

CheckerboardItem::CheckerboardItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/resources/checkerboard.svg"));
}

CheckerboardItem::~CheckerboardItem()
{
}

QRectF CheckerboardItem::boundingRect() const
{
    QRect pixRect = pixmap().rect();
    return QRectF(0, 0, pixRect.width(), pixRect.height());
}

void CheckerboardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pixmap());
    painter->drawRect(boundingRect());
    painter->restore();

    painter->save();
    QPen pen;
    QColor penColor("#000000");
//    penColor.setAlphaF(0.6); // 不带线棋盘透明度
    penColor.setAlphaF(0.25); //带线棋盘透明度
    pen.setColor(penColor);
    painter->setPen(pen);
    for (int i = 0; i < line_num; i++) {
        //横线
        painter->drawLine(backgrond_margin,
                          backgrond_margin + chess_size + chess_size * i,
                          static_cast<int>(boundingRect().width()) - backgrond_margin,
                          backgrond_margin + chess_size + chess_size * i);
        //竖线
        painter->drawLine(backgrond_margin + chess_size + chess_size * i,
                          backgrond_margin,
                          backgrond_margin + chess_size + chess_size * i,
                          static_cast<int>(boundingRect().height() - backgrond_margin));
        if (i == line_num / 2) {
            //天元点绘制
            painter->save();
            painter->setPen("#86582E");
            painter->setBrush(QColor("#86582E"));
            painter->drawEllipse((static_cast<int>(boundingRect().width()) / 2) - 5,
                                 (static_cast<int>(boundingRect().height()) / 2) - 5,
                                 10,
                                 10);
            painter->restore();
        }
    }
    painter->restore();
}
