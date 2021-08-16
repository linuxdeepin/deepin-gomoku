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
#include "btstartpause.h"

#include <QHBoxLayout>
#include <QMouseEvent>

btstartpause::btstartpause(QWidget *parent)
    : buttonbase(parent)
    , startPix(":/resources/icon/begin.svg")
    , stopPix(":/resources/icon/stop.svg")
{
    setMouseTracking(true);
    pixLabel = new DLabel(this);
    pixLabel->setPixmap(startPix);

    DLabel *textLabel = new DLabel(this);
    textLabel->setText("开始/暂停");

    QHBoxLayout *SPLayout = new QHBoxLayout(this);
    SPLayout->addSpacing(30);
    SPLayout->addWidget(pixLabel);
    SPLayout->addWidget(textLabel);
    SPLayout->addSpacing(40);
    setLayout(SPLayout);
}

btstartpause::~btstartpause()
{
}

void btstartpause::mouseRelease()
{
    if (mouseReleaseStatus) {
        if (isStart) {
            pixLabel->setPixmap(stopPix);
            isStart = false;
        } else {
            pixLabel->setPixmap(startPix);
            isStart = true;
        }
    }
}

