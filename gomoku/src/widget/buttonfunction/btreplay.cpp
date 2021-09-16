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
#include "btreplay.h"

BTReplay::BTReplay(QGraphicsItem *parent)
    : ButtonItem(parent)
    , replayPixmap(DHiDPIHelper::loadNxPixmap(":/resources/icon/replay.svg"))
{
    posHeight = firstGamePosHeight;
}

BTReplay::~BTReplay()
{

}

QRectF BTReplay::boundingRect() const
{
    return QRectF(this->scene()->width() * buttonPosWidth,
                  this->scene()->height() * posHeight,
                  200,
                  60);
}

void BTReplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rectX = this->boundingRect().x(); //矩形起始位置X
    qreal rectY = this->boundingRect().y(); //矩形起始位置Y
    qreal rectWidth = this->boundingRect().width(); //矩形宽度
    qreal rectHeight = this->boundingRect().height(); //矩形高度

    painter->setRenderHint(QPainter::Antialiasing);

    //首次开始游戏,设置不同的背景
    if (firstStartGame) {
        painter->save();
        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);
        painter->setOpacity(0.4); //设置图片透明度
        painter->drawPixmap(QPointF(rectX, rectY),
                            DHiDPIHelper::loadNxPixmap(":/resources/function_button/normal.svg"));
        painter->restore();
    } else {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->drawPixmap(QPointF(rectX, rectY), backgrounePix);
        painter->restore();
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    //首次开始游戏
    if (firstStartGame)
        painter->setOpacity(0.4); //设置图片透明度
    painter->drawPixmap(QPointF(rectX + rectWidth * pixmapPosWidth,
                                rectY + rectHeight * pixmapPosHeight),
                        replayPixmap);
    painter->restore();

    painter->save();
    QFont font;
    font.setFamily(Globaltool::loadFontFamilyFromFiles(":/resources/font/ResourceHanRoundedCN-Bold.ttf"));
    font.setWeight(QFont::Black);
    font.setPixelSize(23);
    font.setBold(true);
    painter->setFont(font);
    if (!firstStartGame && pressStatus) {
        painter->setPen(QColor("#ffdb9e"));
    } else {
        painter->setPen(QColor("#024526"));
    }
    //首次开始游戏
    if (firstStartGame)
        painter->setOpacity(0.4); //设置图片透明度
    painter->drawText(QPointF(rectX + rectWidth * textPosWidth,
                              rectY + rectHeight * textPosHeight),
                      tr("New Game"));
    painter->restore();
}

//按钮功能
void BTReplay::buttonFunction()
{
    if (!firstStartGame) {
        //重玩功能
        emit signalbuttonReplay();
    }
}

/**
 * @brief BTReplay::setNotFirstGame 设置是否第一次开始游戏
 */
void BTReplay::setNotFirstGame()
{
    if (qAbs(posHeight - notFirstGamePosHeight) >= (1e-6))
        posHeight = notFirstGamePosHeight;
    firstStartGame = false;
    mouseReleased = false;
    update();
}

