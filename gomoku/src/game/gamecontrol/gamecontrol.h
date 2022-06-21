/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     liyucheng <liyucheng@uniontech.com>
   *
   * Maintainer:  liyucheng <liyucheng@uniontech.com>
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
#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "artificialintelligence/artificialintelligence.h"
#include "gamecontrol/checkerboard.h"

#include <QObject>

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(int AIColor, int userColor, QObject *parent = nullptr);
    ~GameControl();

    //开始游戏
    void startGame();
    void setChessColor(int ai, int user);
signals:
    void AIPlayChess(Chess chess); //电脑下棋
    void isAIPlaying(bool AIPlaying); //谁在下棋
    void gameOver(ChessResult result); //返回游戏结束标志

public slots:
    //接受主页面绘制完成棋子的槽函数
    void chessCompleted(Chess chess);

    //重置游戏
    void resetGame();

private:
    int AIColor; //电脑颜色
    int userColor; //用户颜色
    bool AIPlaying; //ai下棋
    bool gameReset = false; //重玩游戏标志
    bool initGameStatus = false; //初始化游戏

    Checkerboard *checkerboard;

    void initGame(); //初始化数组

    //下棋函数，棋局判断和下棋者判断
    void playChess(const Chess chess);


private slots:
    void setAIChess();
};
#endif // GAMECONTROL_H
