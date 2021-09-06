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

#include <DHiDPIHelper>

#include <QGraphicsItem>
#include <QObject>

DWIDGET_USE_NAMESPACE

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
    QPixmap currentPlayer; //当前旗手
    QPixmap aiPlaying; //ai正在下棋
    QPixmap userPlaying; //用户正在下棋
    QPixmap chessBlack; //黑色棋子
    QPixmap chessWhite; //白色棋子
    QPixmap anotherPlayer; //另一个旗手
    QPixmap userNotPlay; //用户没有下棋
    QPixmap aiNotPlay; //ai没有下棋
    //以下位置参数,根据UI图得来
    const qreal chessPlayingTextPosWidth = 0.1764; //当前下棋提示语位置占整个scene宽度比例
    const qreal chessPlayingTextPosHeight = 0.35; //当前下棋提示语位置占整个scene宽度比例
    const qreal currentPlayerPosWidth = 0.1332; //当前旗手位置占整个scene宽度比例
    const qreal currentPlayerPosHeight = 0.52; //当前旗手位置占整个scene宽度比例
    const qreal aiPlayingPosWidth = 0.3207; //ai下棋位置占整个scene宽度比例
    const qreal aiPlayingPosHeight = 0.59; //ai下棋位置占整个scene高度比例
    const qreal userPlayingPosWidth = 0.3207; //用户下棋位置占整个scene宽度比例
    const qreal userPlayingPosHeight = 0.58; //用户下棋位置占整个scene高度比例
    const qreal currentPlayerChessPosWidth = 0.4603; //当前旗手棋子显示位置占整个scene宽度比例
    const qreal currentPlayerchessPosHeight = 0.79; //当前旗手棋子显示位置占整个scene高度比例
    const qreal anotherPlayerPosWidth = 0.6722; //另一方旗手位置占整个scene宽度比例
    const qreal anotherPlayerPosHeight = 0.6; //另一方旗手所在位置占整个scene高度比例
    const qreal userNotPlayPosWidth = 0.7207; //玩家未下棋时头像位置占整个scene宽度比例
    const qreal userNotPlayPosHeight = 0.65; //玩家未下棋时头像位置占整个scene高度比例
    const qreal aiNotPlayPosWidth = 0.7169; //ai未下棋时头像位置占整个scene宽度比例
    const qreal aiNotPlayPosHeight = 0.66; //ai未下棋时头像位置占整个scene高度比例
    const qreal anotherPlayerChessPosWidth = 0.8452; //另一个旗手棋子显示位置占整个scene宽度比例
    const qreal anotherPlayerChessPosHeight = 0.79; //另一个旗手棋子显示位置占整个scene高度比例
    const qreal sWelcomePosWidth1 = 0.1064; //欢迎语第一行位置占整个scene宽度比例
    const qreal sWelcomePosHeight1 = 0.39; //欢迎语第一行位置占整个scene高度比例
    const qreal sWelcomePosWidth2 = 0.1015; //欢迎语第二行位置占整个scene宽度比例
    const qreal sWelcomePosHeight2 = 0.71; //欢迎语第二行位置占整个scene高度比例
    const qreal sWelcomePosWidth3 = 0.1015; //欢迎语第三行位置占整个scene宽度比例
    const qreal sWelcomePosHeight3 = 0.85; //欢迎语第三行位置占整个scene高度比例
};

#endif // PLAYINGSCREEN_H
