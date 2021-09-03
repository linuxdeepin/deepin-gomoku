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
#ifndef DETERMINEBUTTON_H
#define DETERMINEBUTTON_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class Determinebutton : public DWidget
{
    Q_OBJECT
public:
    Determinebutton(QWidget *parent = nullptr);

signals:
    void signalButtonOKClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap currentPixmap; //当前图片
    QPixmap buttonNormal; //按钮正常状态
    QPixmap buttonHover; //按钮hover状态
    QPixmap buttonPress; //按钮press状态
};

#endif // DETERMINEBUTTON_H
