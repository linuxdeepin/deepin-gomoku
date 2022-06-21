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
#ifndef BUTTONAGAIN_H
#define BUTTONAGAIN_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class Buttonagain : public DWidget
{
    Q_OBJECT
public:
    explicit Buttonagain(QWidget *parent = nullptr);

    void setResult(bool result);

signals:
    void signalButtonAnginClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap currentPixmap; //当前图片
    QPixmap againNormal; //再来一局正常状态
    QPixmap againHover; //再来一局hover状态
    QPixmap againPress; //再来一局press状态
    QPixmap failAgainPress; //再来一局press状态-fail
    bool mResult; //对局结果
    bool buttonPressed = false; //按钮按下标识
};

#endif // BUTTONAGAIN_H
