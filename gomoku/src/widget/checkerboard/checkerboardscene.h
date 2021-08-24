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
#ifndef CHECKERBOARDSCENE_H
#define CHECKERBOARDSCENE_H

#include "chess/chessitem.h"
#include "checkerboarditem.h"
#include "buttonfunction/btstartpause.h"
#include "buttonfunction/btreplay.h"
#include "buttonfunction/btmusiccontrol.h"
#include "playingscreen/playingscreen.h"
#include "constants.h"

#include <QGraphicsScene>

class CheckerboardScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CheckerboardScene(QObject *parent = nullptr);
    ~CheckerboardScene() override;

    void setchessType(int chess = 0);
    void setchessPoint(Chess chess);

public slots:
    void slotPaintAIChess(Chess chess);

signals:
    void signalCurrentPoint(Chess chess); //发送当前棋子坐标
    void signalIsAIPlaying(bool AIPlaying);
    void signalGameOver();
    void signalRestGame();

private:
    void initCheckerboard();
    void initChess();
    void initFunctionButton();
    void initPlayingScreen();

private slots:
    void slotreplayFunction();
    void slotGameStop();
    void slotGameStart();
    void slotCPaintItem(ChessItem *cItem);

private:
    QVector<QVector<ChessItem *>> chessItemList{}; //棋子数组
    bool chessHasPaint[13][13] = {{false}}; //每个位置是否绘制棋子
    CheckerboardItem *cbitem = nullptr; //棋盘item
    BTStartPause *buttonStartPause = nullptr; //开始、暂停按钮
    BTReplay *buttonReplay = nullptr; //重玩按钮
    BTMusicControl *buttonMusicControl = nullptr; //音乐控制按钮
    PlayingScreen *playingScreen = nullptr; //对局显示
    int userChessType = chess_black; //棋子颜色
    int clickPosRow = 0; //点击的行
    int clickPosCol = 0; // 点击的列
    bool gameStatus = true; //游戏状态
};

#endif // CHECKERBOARDSCENE_H
