/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QThread>

#include "photobrowser3dview.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(photobrowser3d);

    QGuiApplication app(argc, argv);

    // for QSettings
    QCoreApplication::setOrganizationName("Nokia");
    QCoreApplication::setOrganizationDomain("nokia.com");
    QCoreApplication::setApplicationName("photobrowser3d");

    int result = 0;
    {
        PhotoBrowser3DView view;

        if (view.stereoType() != QGLView::RedCyanAnaglyph)
            view.camera()->setEyeSeparation(0.3f);
        QStringList args = QCoreApplication::arguments();
        int w_pos = args.indexOf("-width");
        int h_pos = args.indexOf("-height");
        if (w_pos >= 0 && h_pos >= 0)
        {
            bool ok = true;
            int w = args.at(w_pos + 1).toInt(&ok);
            if (!ok)
            {
                qWarning() << "Could not parse width argument:" << args;
                return 1;
            }
            int h = args.at(h_pos + 1).toInt(&ok);
            if (!ok)
            {
                qWarning() << "Could not parse height argument:" << args;
                return 1;
            }
            view.resize(w, h);
        }
        else
        {
            view.resize(800, 600);
        }
        view.show();

        result = app.exec();
    }
    return result;
}
