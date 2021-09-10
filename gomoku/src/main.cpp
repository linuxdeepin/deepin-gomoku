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
#include <gomokumainwindow.h>
#include "environments.h"

#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DGuiApplicationHelper>
#include <DApplicationSettings>
#include <DLog>

#include <QAccessible>
#include <QCommandLineParser>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{

//    PERF_PRINT_BEGIN("POINT-01", "");
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    //适配deepin-turbo启动加速
    DApplication *app = nullptr;
#if(DTK_VERSION < DTK_VERSION_CHECK(5,4,0,0))
    app = new DApplication(argc, argv);
#else
    app = DApplication::globalApplication(argc, argv);
#endif

    app->setAutoActivateWindows(true);
    //如果dtk版本为5.2.0.1以上则使用新的dtk接口
#if (DTK_VERSION > DTK_VERSION_CHECK(5, 2, 0, 1))
    //设置为-1将永久等待
    DGuiApplicationHelper::setSingleInstanceInterval(-1);
#endif

    if (DGuiApplicationHelper::setSingleInstance(app->applicationName(), DGuiApplicationHelper::UserScope)) {
//        QAccessible::installFactory(accessibleFactory);
        app->setOrganizationName("deepin");
        app->setApplicationName("deepin-gomoku");
        app->loadTranslator();
        app->setApplicationVersion(VERSION);

        QIcon t_icon = QIcon::fromTheme("deepin-gomoku");
        app->setProductIcon(t_icon);
        app->setProductName(QApplication::translate("GomokuWindow", "Gomoku"));
        app->setApplicationDescription(QApplication::translate("GomokuWindow", "Gomoku is a small chess game for two players."));


        //命令行参数
        QCommandLineParser _commandLine; //建立命令行解析
        _commandLine.addHelpOption(); //增加-h/-help解析命令
        _commandLine.addVersionOption(); //增加-v 解析命令
        _commandLine.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
        _commandLine.process(*app);

        app->setAutoActivateWindows(true);
        //log输出到控制台
        DLogManager::registerConsoleAppender();
        //log输出到日志文件
        DLogManager::registerFileAppender();
        //保存主题
        DApplicationSettings applicationset(app);

        GomokuMainWindow ww;
//        Selectchess *selectChess = new Selectchess;
//        ww.connectSelectChess(selectChess);
        ww.show();

        return app->exec();
    }

    return 0;
}
