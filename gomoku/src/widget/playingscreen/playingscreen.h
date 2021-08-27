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
#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H

#include <QGraphicsItem>
#include <QObject>

class PlayingScreen : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PlayingScreen(QGraphicsItem *parent = nullptr);
    ~PlayingScreen() override;

    void setCurrentPlay(bool player);
    void setCurrentChessColor(bool AIPlaying, int chesscolor);

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void slotStartGame();

private:
    bool AIPlayer = false; //旗手
    bool gamePlaying = false; //游戏是否开始
    int currentChessColro = 0; //棋子颜色
};

#endif // PLAYINGSCREEN_H
