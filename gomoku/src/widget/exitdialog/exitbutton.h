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
#ifndef EXITBUTTON_H
#define EXITBUTTON_H

#include <QWidget>
#include <QPixmap>
#include <DWidget>

DWIDGET_USE_NAMESPACE
class ExitButton : public QWidget
{
Q_OBJECT
 public:
     explicit ExitButton(QWidget *parent = nullptr);

 private:
     void mouseReleaseEvent(QMouseEvent *event);
     void enterEvent(QEvent *event);
     void leaveEvent(QEvent *event);
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *event);

 private:
     QPixmap buttonNormal;
     QPixmap buttonHover;
     QPixmap buttonPress;
     QPixmap currentPixmap;

 signals:
     void signalButtonOKClicked();
 public slots:
};

#endif // EXITBUTTON_H
