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
#include "exitdialog.h"
#include "cancelbutton.h"
#include "exitbutton.h"
#include "exitlabel.h"
#include "resultpopup/closepopup.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <DHiDPIHelper>
#include <DApplication>
#include <QPainter>
ExitDialog::ExitDialog(QWidget *parent)
    : QDialog(parent)
    , result(BTType::BTCancel)
    , backgroundQPixmap(DHiDPIHelper::loadNxPixmap(":/resources/exitdialog/close-dialog.svg"))
{
    setFixedSize(372, 219);
    setAttribute(Qt::WA_TranslucentBackground); //背景透明
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //取消标题栏

    initUI();
}

/**
 * @brief ExitDialog::initUI  初始化ui界面
 */
void ExitDialog::initUI()
{
    //上层关闭按钮布局
    QHBoxLayout *titleLayout = new QHBoxLayout();
    Closepopup *closeButton = new Closepopup(this);
    connect(closeButton, &Closepopup::signalCloseClicked, this, &ExitDialog::soltDialogClose);

    titleLayout->addStretch();
    titleLayout->addWidget(closeButton);
    titleLayout->addSpacing(10); //关闭按钮距离右边界的距离


    //中层标签布局
    QHBoxLayout *textLayout = new QHBoxLayout();
    textLayout->addStretch();

    ExitLabel *exitLabel = new ExitLabel(this);
    textLayout->addWidget(exitLabel);
    textLayout->addStretch();

    //下层按钮布局
    QHBoxLayout *BTLayout = new QHBoxLayout();
    BTLayout->addSpacing(7); //按钮距离左边界的距离

    CancelButton *cancelButton = new CancelButton();
    ExitButton *exitButton = new ExitButton();
    connect(cancelButton, &CancelButton::signalButtonOKClicked, this, &ExitDialog::soltDialogClose);
    connect(exitButton, &ExitButton::signalButtonOKClicked, this, &ExitDialog::soltGameExit);

    BTLayout->addWidget(cancelButton);
    BTLayout->addWidget(exitButton);
    BTLayout->addSpacing(9);//按钮距离右边界的距离

    //主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(5);//上层布局离中间布局的距离
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(textLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(BTLayout);
    mainLayout->addSpacing(20); //按钮距离下边界的距离
}

/**
 * @brief ExitDialog::soltDialogClose 槽函数：处理取消按钮和关闭dialog的信号
 */
void ExitDialog::soltDialogClose()
{
    setResult(BTType::BTCancel); //将状态设置为取消
    emit signalClicked();
    this->done(0);
}

/**
 * @brief ExitDialog::soltGameExit 槽函数：处理退出游戏的信号
 */
void ExitDialog::soltGameExit()
{
    setResult(BTType::BTExit); //将状态设置为退出
    emit signalClicked();
    this->done(0);
}


/**
 * @brief ExitDialog::paintEvent 重写绘画事件
 * @param event
 */
void ExitDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(this->rect(), backgroundQPixmap);
    painter.restore();
    QDialog::paintEvent(event);
}
