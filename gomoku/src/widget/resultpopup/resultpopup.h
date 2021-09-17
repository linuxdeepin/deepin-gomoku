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
#ifndef RESULTPOPUP_H
#define RESULTPOPUP_H

#include "resultinfo.h"
#include "buttonrest.h"
#include "buttonagain.h"

#include <DDialog>

DWIDGET_USE_NAMESPACE
class Resultpopup : public DWidget
{
    Q_OBJECT
public:
    Resultpopup(bool compositing, QWidget *parent = nullptr);

    void popupShow();
    void setHasWin(bool win);
    void popupClose();

public slots:
    void slotCompositingChanged(bool compositing);

signals:
    void signalGameAgain();
    void signalHaveRest();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void initUI();
    void initBackgroundPix();

private:
    bool hasWin = false; //是否赢
    bool compositingStatus = false; //是否开始特效窗口
    QPixmap winPixmap; //赢的背景图片
    QPixmap failPixmap; //输的背景图片
    Resultinfo *resultInfo = nullptr; //结果信息
    Buttonrest *buttonRest = nullptr; //休息一下按钮
    Buttonagain *buttonAgain = nullptr; //再来一局按钮
};

#endif // RESULTPOPUP_H
