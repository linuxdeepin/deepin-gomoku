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
#include "gomokumainwindow.h"

#include <DWidgetUtil>
#include <DWidget>
#include <DTitlebar>

#include <QPushButton>
#include <QHBoxLayout>

const int widgetWidth = 1024;
const int widgetHeight = 768;

gomokumainwindow::gomokumainwindow(QWidget *parent)
    : DMainWindow(parent)
{
    setContentsMargins(QMargins(0, 0, 0, 0));

    setWindowTitle(tr("deepin-gomoku"));
    setAutoFillBackground(true);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
//    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(1);

    initUI();

    Dtk::Widget::moveToCenter(this);
}

gomokumainwindow::~gomokumainwindow()
{

}

void gomokumainwindow::initUI()
{
    DWidget *maincentralWidget = new DWidget(this);
    QHBoxLayout *mainlayout = new QHBoxLayout(this);

    //background
    QPixmap backgroundImage(":/resources/background.svg");
    DPalette palette;
    palette.setColor(DPalette::Background, Qt::transparent);
    palette.setBrush(QPalette::Background, QBrush(backgroundImage));
    setPalette(palette);

    DTitlebar *tbar = titlebar();
    //目前系统中没有游戏的图标，先这样设置
    tbar->setIcon(QIcon(":/resources/logo.svg"));
    tbar->setAutoFillBackground(true);
    tbar->setWindowOpacity(1);
    tbar->setAttribute(Qt::WA_TranslucentBackground);
    tbar->setBackgroundTransparent(true);
    DPalette pa(tbar->palette());
    QLinearGradient linearGradient;
    QColor topColor("#232323");
    topColor.setAlphaF(0.5);
    linearGradient.setColorAt(0, topColor);
    QColor bottomColor("#1C1C1C");
    bottomColor.setAlphaF(0.5);
    linearGradient.setColorAt(1, bottomColor);
    pa.setBrush(DPalette::Background, linearGradient);
//    pa.setBrush(DPalette::Normal, DPalette::Dark, linearGradient);
    tbar->setPalette(pa);


    maincentralWidget->setLayout(mainlayout);
    setCentralWidget(maincentralWidget);
    setFixedSize(QSize(widgetWidth, widgetHeight));
}
