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
#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include <DWidget>

#include <QRadioButton>

DWIDGET_USE_NAMESPACE

class Selectbutton : public QRadioButton
{
public:
    Selectbutton(QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap selectNormal; //选择按钮正常状态
    QPixmap selectHover; //选择按钮hover状态
    QPixmap selectPress; //选择按钮press状态
    QPixmap currentStatus; //目前的状态
    bool pressStatus = false; //鼠标点击状态
};

#endif // SELECTBUTTON_H
