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
#ifndef CHESSITEM_H
#define CHESSITEM_H

#include <DHiDPIHelper>

#include <QGraphicsItem>
#include <QtMultimedia/QSound>

DWIDGET_USE_NAMESPACE

class ChessItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ChessItem(int userChessColor, QGraphicsItem *parent = nullptr);

    //set chess type
    void setCurrentchess(int chesstype);
    int getChessColor();

    void setchessStatus(bool chessstatus);
    bool getchessStatus();

    int getChessPlayer();

signals:
    void signalCPaintItem(ChessItem *item); //当前绘制的item

public slots:
    void slotGameContinue();
    void slotGameStop();
    void slotGameOver();
    void slotIsAIPlaying(bool AIPlaying);
    /**
     * @brief slotMusicControl 音效控制槽函数
     * @param musicControl 是否打开音效
     */
    void slotMusicControl(bool musicControl);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap chessWhitePixmap; //白色棋子图片
    QPixmap chessBlackPixmap; //黑色棋子图片
    int chessType = 0; //棋子颜色
    int userChessType = 0; //玩家棋子颜色
    bool hoverStatus = false; //hover状态标志
    bool chessStatus = false; //是否有棋子标志
    bool gameStatus = true; //是否暂停
    bool gameOver = false; //游戏结束
    bool isAIPlaying = false; //是否为ai下棋
    bool musicControlStatue = true; //游戏音效控制状态
};

#endif // chessITEM_H
