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
    explicit CheckerboardScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
    ~CheckerboardScene() override;

    void setchessType(int chess = 0);
    void startGame();
    void stopGAme();

signals:
    void signalCurrentPoint(Chess chess); //发送当前棋子坐标
    void signalIsAIPlaying(bool AIPlaying);
    void signalMusicControl(bool musicControl);//音效控制信号
    void signalGameStart();
    void signalGameOver();
    void signalRestGame();
    void signalStartGame();

public slots:
    void slotPaintAIChess(Chess chess);
    void slotreplayFunction();

private:
    void initGame();
    void initCheckerboard();
    void initChess();
    void initFunctionButton();
    void initPlayingScreen();
    void setAIChess(Chess chess);
    void playWinMusic();
    void playFailMusic();

private slots:
    void slotGameStop();
    void slotGameStart();
    void slotPopupResult(ChessResult result);
    void slotCPaintItem(ChessItem *cItem);

private:
    QVector<QVector<ChessItem *>> chessItemList{}; //棋子数组
    bool chessHasPaint[13][13] = {{false}}; //棋子坐标数组,保存每个位置是否绘制棋子
    CheckerboardItem *cbitem = nullptr; //棋盘item
    BTStartPause *buttonStartPause = nullptr; //开始、暂停按钮
    BTReplay *buttonReplay = nullptr; //重玩按钮
    BTMusicControl *buttonMusicControl = nullptr; //音乐控制按钮
    PlayingScreen *playingScreen = nullptr; //对局显示
    int userChessType = chess_black; //棋子颜色
    int clickPosRow = 0; //点击的行
    int clickPosCol = 0; // 点击的列
    int userChess; //用户棋子颜色
    int aiChess; //ai棋子颜色
    bool musicControlStatus = true; //是否可以播放音乐
    bool gameStatus = false; //游戏状态
    bool seleceChessPopup = true; //是否弹出选择棋子弹窗
    bool playChess = false; //是否是AI下棋
    bool AIChessStatus = false; //暂停游戏时,AI是否下棋
    Chess AIChess; //保存当前棋子位置
    //以下位置参数,根据UI图得来
    const qreal lefttopChessPosWidth = 0.02; //左上角第一个棋子位置占整个scene宽度比例
    const qreal lefttopChessPosHeight = 0.007; //左上角第一个棋子位置占整个scene高度比例
    const int chessOffset = 83; //棋子位置偏移量
    const qreal buttonPosWidth = 0.74; //功能按钮位置占整个scene宽度比例
    const qreal buttonStartPausePosHeight = 0.333;  //开始暂停功能按钮位置占整个scene高度比例
    const qreal buttonReplayPosHeight = 0.444; //重玩功能按钮位置占整个scene高度比例
    const qreal buttonMusicControlPosHeight = 0.765; //音乐功能按钮位置占整个scene高度比例
    const qreal playingScreenPosWidth = 0.7; //对局详情位置占整个scene宽度比例
    const qreal playingScreenPosHeight = 0.005; //对局详情位置占整个scene高度比例
    const qreal CheckerboardPosWidth = 0.02; //棋盘位置占整个scene宽度比例
    const qreal CheckerboardPosHeight = 0.007; //棋盘位置占整个scene高度比例
};

#endif // CHECKERBOARDSCENE_H
