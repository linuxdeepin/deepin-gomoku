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
#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "constants.h"
#include "calculatescore.h"


class ArtificialIntelligence
{
public:
    ArtificialIntelligence();

    //根据当前棋局形式，返回计算出的最佳位置
    static Position getPosition(const ChessState chessState, const int color);

};

#endif // ARTIFICIALINTELLIGENCE_H
