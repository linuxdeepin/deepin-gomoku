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
#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QWidget>
#include <DDialog>
#include <QPixmap>
#include <QMessageBox>
#include "constants.h"
class ExitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExitDialog(bool compositing, QWidget *parent = nullptr);
    inline BTType getResult() {return result;}
    inline void setResult(BTType r) {result = r;}

public:
    BTType result; //用于区分那个按钮的点击，让主界面退出游戏

private:
    QPixmap backgroundQPixmap;
    bool compositingStatus = false; //是否开启特效窗口

private:
    void initUI();
    void initBackgroundPix();
    void paintEvent(QPaintEvent *event);

signals:
    void signalClicked(); //点击信号

public slots:
    void soltDialogClose();
    void soltGameExit();
    void slotCompositingChanged(bool compositing);

};

#endif // EXITDIALOG_H
