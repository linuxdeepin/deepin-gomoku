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
#include "selectinfo.h"
#include "globaltool.h"

Selectinfo::Selectinfo(QWidget *parent)
    : DLabel(parent)
{
    //设置大小
    setFixedSize(226, 40);
}

/**
 * @brief Selectinfo::paintEvent 绘图函数
 * @param event paintevent
 */
void Selectinfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.setPen("#02412c");
    QFont font;
    font.setFamily(Globaltool::instacne()->loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Bold);
    font.setPixelSize(Globaltool::instacne()->getFontSize().dialogLabel
                      - (Globaltool::instacne()->getFontSize().dialogOffset) * 3); //阻塞弹窗标签字体大小为16
    painter.setFont(font);
    QString str = tr("Play as");
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignBottom, str);
    painter.restore();
    DLabel::paintEvent(event);
}
