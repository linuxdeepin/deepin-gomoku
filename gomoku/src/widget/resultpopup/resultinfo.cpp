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
#include "resultinfo.h"
#include "globaltool.h"

Resultinfo::Resultinfo(QWidget *parent)
    : DLabel(parent)
    , mResult(true)
    , strResult("")
{
    //设置大小
    setFixedSize(300, 48);
}

Resultinfo::~Resultinfo()
{

}

/**
 * @brief Resultinfo::setResult 设置对局结果
 * @param result 对局结果:true为赢, false为输
 */
void Resultinfo::setResult(bool result)
{
    mResult = result;
    if (mResult) {
        strResult = tr("You did great!");
    } else {
        strResult = tr("Game Over");
    }
}

/**
 * @brief Resultinfo::paintEvent 绘图事件
 * @param event
 */
void Resultinfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.setPen("#353535");
    QFont font;
    font.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Bold);
    font.setPixelSize(25);
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, strResult);
    painter.restore();

    DLabel::paintEvent(event);
}
