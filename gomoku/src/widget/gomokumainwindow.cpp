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
#include <DFrame>

#include <QPushButton>
#include <QHBoxLayout>

const int widgetWidth = 1024;
const int widgetHeight = 768;

gomokumainwindow::gomokumainwindow(QWidget *parent)
    : DMainWindow(parent)
{
    setContentsMargins(QMargins(0, 0, 0, 0));

    setWindowTitle(tr("deepin-gomoku"));

    initUI();

    Dtk::Widget::moveToCenter(this);
}

gomokumainwindow::~gomokumainwindow()
{
    delete mTitleBar;
}

//初始化界面
void gomokumainwindow::initUI()
{
    DWidget *maincentralWidget = new DWidget(this);
    QHBoxLayout *mainlayout = new QHBoxLayout();

    //background
    QPixmap backgroundImage(":/resources/background.svg");
    DPalette palette;
    palette.setColor(DPalette::Background, Qt::transparent);
    palette.setBrush(QPalette::Background, QBrush(backgroundImage));
    setPalette(palette);

    mTitleBar = titlebar();
    mTitleBar->setFrameShape(DFrame::NoFrame);
    mTitleBar->installEventFilter(this);
    //目前系统中没有游戏的图标，先这样设置
    mTitleBar->setIcon(QIcon(":/resources/logo.svg"));
    mTitleBar->setAutoFillBackground(true);
    mTitleBar->setAttribute(Qt::WA_TranslucentBackground);
    mTitleBar->setWindowOpacity(0.5);
    mTitleBar->setBackgroundTransparent(true);
    mTitleBar->setMenuVisible(false);

    maincentralWidget->setLayout(mainlayout);
    setCentralWidget(maincentralWidget);
    setFixedSize(QSize(widgetWidth, widgetHeight));
}

//绘制titlebar背景
void gomokumainwindow::paintTitleBar(QWidget *titlebar)
{
    QPainter painter(titlebar);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    QLinearGradient linearGradient;
    QColor topColor("#232323");
    topColor.setAlphaF(0.3);
    QColor bottomColor("#1C1C1C");
    bottomColor.setAlphaF(0.3);
    linearGradient.setColorAt(0, topColor);
    linearGradient.setColorAt(1, bottomColor);
    painter.setPen(Qt::NoPen);
    painter.setBrush(linearGradient);
    painter.fillRect(titlebar->rect(), linearGradient);
    painter.drawRect(titlebar->rect());
    painter.restore();
}

//过滤titlebar绘制事件
bool gomokumainwindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == mTitleBar) {
        if (event->type() == QEvent::Paint) {
            paintTitleBar(mTitleBar);
        }
    }
    return QWidget::eventFilter(watched, event);
}
