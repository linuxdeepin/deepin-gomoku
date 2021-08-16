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
#include "btreplay.h"

#include <QHBoxLayout>

#include <DLabel>

btreplay::btreplay(QWidget *parent)
    : buttonbase(parent)
{
    QPixmap replayButton(":/resources/icon/replay.svg");
    DLabel *pixLabel = new DLabel(this);
    pixLabel->setPixmap(replayButton);

    DLabel *textLabel = new DLabel(this);
    textLabel->setText("重玩");

    QHBoxLayout *SPLayout = new QHBoxLayout(this);
    SPLayout->addSpacing(30);
    SPLayout->addWidget(pixLabel);
    SPLayout->addWidget(textLabel);
    SPLayout->addSpacing(40);
    setLayout(SPLayout);
}
