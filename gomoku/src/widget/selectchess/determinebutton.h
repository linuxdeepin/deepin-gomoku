// Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DETERMINEBUTTON_H
#define DETERMINEBUTTON_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class Determinebutton : public DWidget
{
    Q_OBJECT
public:
    explicit Determinebutton(QWidget *parent = nullptr);

signals:
    void signalButtonOKClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
#if QT_VERSION_MAJOR > 5
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap currentPixmap; //当前图片
    QPixmap buttonNormal; //按钮正常状态
    QPixmap buttonHover; //按钮hover状态
    QPixmap buttonPress; //按钮press状态
    bool buttonPressed = false; //按钮按下标识
};

#endif // DETERMINEBUTTON_H
