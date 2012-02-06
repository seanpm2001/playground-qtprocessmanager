/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PROCUTILS_H
#define PROCUTILS_H

#include <QString>

QT_FORWARD_DECLARE_CLASS(QLocalSocket)

#include "processmanager-global.h"

QT_BEGIN_NAMESPACE_PROCESSMANAGER

class Q_ADDON_PROCESSMANAGER_EXPORT ProcUtils
{
    ProcUtils();
    Q_DISABLE_COPY(ProcUtils)
public:
    static QString execNameForPid(qint64 pid);
    static qint64 ppidForPid(pid_t pid);
    static qint64 pidForFilename(const QString &filename);
    static qint64 pidForLocalSocket(const QLocalSocket *socket);
    static QByteArray cmdlineForPid(qint64 pid);

    static qint32 oomAdjustment(pid_t pid, bool *ok=NULL);
    static bool   setOomAdjustment(pid_t pid, qint32 oomAdjustment);
};

QT_END_NAMESPACE_PROCESSMANAGER

#endif // PROCUTILS_H
