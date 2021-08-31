/*
 * Copyright (C) 2021 CutefishOS Team.
 *
 * Author:     Reion Wong <reionwong@gmail.com>
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

#include <QApplication>
#include <QDBusConnection>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "screenshotview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineOption delayOption(QStringList() << "d" << "delay", "Delay Screenshot", "NUM");
    QCommandLineParser parser;
    parser.setApplicationDescription("Cutefish Screenshot");
    parser.addHelpOption();
    parser.addOption(delayOption);
    parser.process(app);

    if (!QDBusConnection::sessionBus().registerService("org.cutefish.Screenshot")) {
        app.exit();
        return 0;
    }

    ScreenshotView view;
    if (parser.isSet(delayOption)) {
        view.delay(parser.value(delayOption).toInt());
    } else {
        view.start();
    }

    return app.exec();
}
