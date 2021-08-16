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
#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include <DPalette>
#include <DFrame>

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

class buttonbase : public DFrame
{
    Q_OBJECT
public:
    explicit buttonbase(QWidget *parent = nullptr);

signals:

public slots:

protected:
    virtual void mouseRelease();
    bool mouseReleaseStatus = false;
    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    void initBackground();
};

#endif // BUTTONBASE_H
