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
#include "chessselected.h"

#include <DHiDPIHelper>

#include <QPainter>

Chessselected::Chessselected(int chessColor, QWidget *parent)
    : DWidget(parent)
    , chessWhite(DHiDPIHelper::loadNxPixmap(":/resources/white_chess.svg"))
    , chessBlack(DHiDPIHelper::loadNxPixmap(":/resources/black_chess.svg"))
    , mChessColor(chessColor)
{
    //设置大小
    setFixedSize(32, 32);
}

/**
 * @brief Chessselected::paintEvent 绘图事件
 * @param event
 */
void Chessselected::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    if (mChessColor == 1) {
        painter.drawPixmap(this->rect(), chessBlack);
    } else if (mChessColor == 2) {
        painter.drawPixmap(this->rect(), chessWhite);
    }
    painter.restore();
    DWidget::paintEvent(event);
}
