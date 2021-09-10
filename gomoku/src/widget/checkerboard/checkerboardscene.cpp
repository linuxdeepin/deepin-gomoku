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
#include "checkerboardscene.h"
#include "exitdialog/exitdialog.h"
#include "selectchess/selectchess.h"
#include "resultpopup/resultpopup.h"
#include "gamecontrol/gamecontrol.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>

CheckerboardScene::CheckerboardScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(parent)
    , playChessSound(new QSound(":/resources/music/chessone.wav", this))
    , cbitem(new CheckerboardItem)
    , buttonStartPause(new BTStartPause)
    , buttonReplay(new BTReplay)
    , buttonMusicControl(new BTMusicControl)
    , playingScreen(new PlayingScreen)
    , gameControl(new GameControl(aiChessColor, userChessColor))
    , selectChess(new Selectchess)
    , AIChess(-1, -1, 0)
{
    //设置scene大小
    setSceneRect(x, y, width, height);
    addItem(cbitem);
    addItem(playingScreen);
    addButtonFunction();
    initGame();
    connect(buttonStartPause, &BTStartPause::signalGameStart, this, &CheckerboardScene::slotGameStart);
    connect(buttonStartPause, &BTStartPause::signalGameStop, this, &CheckerboardScene::slotGameStop);
    connect(buttonStartPause, &BTStartPause::signalGameContinue, this, &CheckerboardScene::slotGameContinue);
    connect(buttonReplay, &BTReplay::signalbuttonReplay, this, &CheckerboardScene::signalReplayFunction); //重玩游戏
    connect(buttonMusicControl, &BTMusicControl::signalMusic, this, [ = ](bool musicControl) {
        musicControlStatus = musicControl;
    });//音效控制
}

CheckerboardScene::~CheckerboardScene()
{
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            removeItem(chessItemList.at(i).at(j));
            delete chessItemList.at(i).at(j);
        }
    }
    chessItemList.clear();
    if (cbitem != nullptr) {
        delete cbitem;
        cbitem = nullptr;
    }
    if (buttonStartPause != nullptr) {
        delete buttonStartPause;
        buttonStartPause = nullptr;
    }
    if (buttonReplay != nullptr) {
        delete buttonReplay;
        buttonReplay = nullptr;
    }
    if (buttonMusicControl != nullptr) {
        delete buttonMusicControl;
        buttonMusicControl = nullptr;
    }
    if (playingScreen != nullptr) {
        delete playingScreen;
        playingScreen = nullptr;
    }
}

//初始化棋子
void CheckerboardScene::initChess()
{
    //清空
    if (!chessItemList.isEmpty()) {
        for (int i = 0; i < line_row; i++) {
            for (int j = 0; j < line_col; j++) {
                removeItem(chessItemList.at(i).at(j));
                chessItemList.at(i).at(j)->deleteLater();
                chessHasPaint[i][j] = false;
            }
        }
        chessItemList.clear();
    }
    //赋值
    for (int i = 0; i < line_row; i++) {
        QVector<ChessItem *> pieceItems;
        for (int j = 0; j < line_col; j++) {
            ChessItem *chess = new ChessItem(userChessColor);
            connect(this, &CheckerboardScene::signalGameOver, chess, &ChessItem::slotGameOver);//游戏结束
            connect(this, &CheckerboardScene::signalIsAIPlaying, chess, &ChessItem::slotIsAIPlaying);//当前旗手
            connect(buttonStartPause, &BTStartPause::signalGameStop, chess, &ChessItem::slotGameStop);//暂停游戏
            connect(this, &CheckerboardScene::signalGameContinue, chess, &ChessItem::slotGameContinue);//继续游戏
            connect(chess, &ChessItem::signalCPaintItem, this, &CheckerboardScene::slotCPaintItem);//落子坐标,判断输赢
            //整个棋盘左上角点,加上偏移量到达绘制区域,减去棋格半径是以棋子所在rect左上角为圆点绘制棋子
            //循环添加每个位置棋子
            chess->setPos(this->width() * lefttopChessPosWidth + chessOffset  - chess_size / 2 + chess_size * j,
                          this->height() * lefttopChessPosHeight + chessOffset  - chess_size / 2 + chess_size * i);
            pieceItems.append(chess);
            addItem(chess);
            chessHasPaint[i][j] = false;
        }
        chessItemList.append(pieceItems);
    }
}

/**
 * @brief CheckerboardScene::removeButtonFunction 移除功能按钮
 */
void CheckerboardScene::removeButtonFunction()
{
    removeItem(buttonStartPause);
    removeItem(buttonReplay);
    removeItem(buttonMusicControl);
}

/**
 * @brief CheckerboardScene::addButtonFunction 添加功能按钮
 */
void CheckerboardScene::addButtonFunction()
{
    addItem(buttonStartPause);//开始/暂停游戏
    addItem(buttonReplay); //重玩游戏
    addItem(buttonMusicControl); //音乐控制
}

//放置AI棋子
void CheckerboardScene::setAIChess(Chess chess)
{
    int row = chess.x;
    int col = chess.y;
    int color = chess.color;
    chessItemList.at(row).at(col)->setCurrentchess(color);
    chessItemList.at(row).at(col)->setchessStatus(true);
}

/**
 * @brief CheckerboardScene::slotGameStart 开始游戏, 选择棋子
 */
void CheckerboardScene::slotGameStart()
{
    emit signalSelectChessPopup();
}

//重玩游戏
void CheckerboardScene::replayFunction()
{
    qInfo() << __FUNCTION__ << "game status:" << gameStatus << buttonStartPause->getButtonStatus();
    //添加游戏重玩标志, 防止点击重玩后,AI继续下棋导致数组越界问题
    gameReplay = true;
    buttonStartPause->setGameOverStatus(false);
    emit signalRestGame();//通知游戏控制,重置游戏
}

/**
 * @brief CheckerboardScene::setStartPauseStatus 设置开始暂停按钮是否为游戏结束状态
 */
void CheckerboardScene::setStartPauseStatus()
{
    buttonStartPause->setGameOverStatus(false);
    buttonStartPause->setButtonStatus(true);
}

/**
 * @brief CheckerboardScene::initGame 初始化游戏
 */
void CheckerboardScene::initGame()
{
    connect(this, &CheckerboardScene::signalCurrentPoint, gameControl, &GameControl::chessCompleted);//更新棋盘数组
    connect(this, &CheckerboardScene::signalRestGame, gameControl, &GameControl::resetGame);//重置游戏
    connect(gameControl, &GameControl::AIPlayChess, this, &CheckerboardScene::slotPaintAIChess);//绘制AI落子
    connect(gameControl, &GameControl::isAIPlaying, this, &CheckerboardScene::signalIsAIPlaying);//通知棋子,当前旗手
    connect(gameControl, &GameControl::gameOver, this, &CheckerboardScene::slotGameOver);//游戏结束
}

//暂停游戏
void CheckerboardScene::slotGameStop()
{
    gameStatus = false;
}

//开始游戏
void CheckerboardScene::slotGameContinue()
{
    gameStatus = true;
    emit signalGameContinue();
    //如果AI已经下棋,绘制AI棋子
    if (AIChessStatus) {
        setAIChess(AIChess);
        AIChessStatus = false;
    }
}

/**
 * @brief CheckerboardScene::slotGameOver 游戏结束
 */
void CheckerboardScene::slotGameOver(ChessResult result)
{
    buttonStartPause->setGameOverStatus(true);
    playingScreen->setGameOverStatus();
    emit signalGameOver();
    emit signalPopupResult(result);
}

/**
 * @brief CheckerboardScene::slotSelsectChessOK 选择完棋子
 */
void CheckerboardScene::selsectChessOK()
{
    //先移除功能按钮,再添加,保证按钮三态显示正常
    removeButtonFunction();
    addButtonFunction();
    //使能功能按钮
    buttonStartPause->setNotFirstGame();
    buttonReplay->setNotFirstGame();
    buttonMusicControl->setNotFirstGame();
//    emit signalGameContinue(); //继续游戏
    emit signalCloSelectPopup(); //关闭弹窗
//    startGame(); //开始游戏
    gameStatus = true;
}

/**
 * @brief CheckerboardScene::getMusicPlay 是否可以播放音乐
 * @return
 */
bool CheckerboardScene::getMusicPlay()
{
    return musicControlStatus;
}

/**
 * @brief CheckerboardScene::getUserChessColor 获取用户棋子颜色
 * @return
 */
int CheckerboardScene::getUserChessColor()
{
    return userChessColor;
}

//判断当前绘制的item，保存坐标
void CheckerboardScene::slotCPaintItem(ChessItem *cItem)
{
    for (int i = 0; i < line_row; i++) {
        for (int j = 0; j < line_col; j++) {
            if (chessItemList.at(i).at(j) == cItem && !chessHasPaint[i][j]) {
                qInfo() << __FUNCTION__ <<  "music play statues: " << musicControlStatus;
                if (musicControlStatus) {
                    //播放落子音效
                    playChessSound->play();
                }
                chessHasPaint[i][j] = true;
                qInfo() << __FUNCTION__ <<  "current chess pos: " << i << j;
                Chess chess(i, j, cItem->getChessColor());
                bool chessPlayer = !cItem->getChessPlayer();
                int chessColor = cItem->getChessColor();
                //反转棋子颜色,显示回合信息
                if (chessColor == chess_black) {
                    chessColor = chess_white;
                } else if (chessColor == chess_white) {
                    chessColor = chess_black;
                }
                playingScreen->setCurrentChessColor(chessPlayer, chessColor);
                emit signalCurrentPoint(chess);
                if (clickPosRow != -1 && clickPosCol != -1) {
                    chessItemList.at(clickPosRow).at(clickPosCol)->setHasPrintChess();
                }
                clickPosRow = i;
                clickPosCol = j;
            }
        }
    }
}

/**
 * @brief CheckerboardScene::startGame 开始游戏
 */
void CheckerboardScene::startGame()
{
    gameControl->setChessColor(aiChessColor, userChessColor);//设置玩家棋子颜色
    initChess();
    //根据用户选择棋子颜色, 设置对局详情
    if (userChessColor == chess_black) {
        playingScreen->setCurrentChessColor(false, userChessColor);
    } else if (userChessColor == chess_white) {
        playingScreen->setCurrentChessColor(true, userChessColor);
    }
    playingScreen->slotStartGame();
    gameReplay = false;
    gameControl->startGame();//开始游戏
}

/**
 * @brief CheckerboardScene::stopGAme 暂停游戏
 */
void CheckerboardScene::stopGAme()
{
    buttonStartPause->setButtonStatus(true);
}

/**
 * @brief CheckerboardScene::setSelectChess 设置棋子颜色
 * @param userColor 用户棋子颜色
 * @param aiColor ai棋子颜色
 */
void CheckerboardScene::setSelectChess(int userColor, int aiColor)
{
    userChessColor = userColor;
    aiChessColor = aiColor;
}

//绘制AI棋子
void CheckerboardScene::slotPaintAIChess(Chess chess)
{
    //保存AI下棋数据
    AIChess.x = chess.x;
    AIChess.y = chess.y;
    AIChess.color = chess.color;
    //游戏暂停不能下棋
    if (!gameReplay && gameStatus) {
        setAIChess(chess);
    } else if (!gameStatus) {
        AIChessStatus = true;
    }
}
