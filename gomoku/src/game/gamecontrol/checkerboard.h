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
#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include "constants.h"
#include "pub.h"

#include <QObject>

/**
 * @brief The Checkerboard class 棋盘类 管理棋盘中的数组状态
 */
class Checkerboard : public QObject
{
    Q_OBJECT
public:
    explicit Checkerboard(QObject *parent = nullptr);

    void insertChess(Chess chess);

    const ChessState & getChessState();

    void initCheckerboard();

    void resetCheckerboard();

private:
    ChessState chessState;

signals:


public slots:
};

#endif // CHECKERBOARD_H
