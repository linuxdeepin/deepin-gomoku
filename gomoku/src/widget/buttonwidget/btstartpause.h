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
#ifndef BTSTARTPAUSE_H
#define BTSTARTPAUSE_H

#include "buttonbase.h"

#include <DLabel>

class btstartpause : public buttonbase
{
public:
    btstartpause(QWidget *parent = nullptr);
    ~btstartpause();

    // QWidget interface
protected:
private:
    void mouseRelease() override;
private:
    DLabel *pixLabel = nullptr;
    bool isStart = true;
    QPixmap startPix;
    QPixmap stopPix;
};

#endif // BTSTARTPAUSE_H
