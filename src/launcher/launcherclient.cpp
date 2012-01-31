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

#include <QDebug>

#include "launcherclient.h"
#include "processbackend.h"
#include "processbackendmanager.h"

QT_BEGIN_NAMESPACE_PROCESSMANAGER

/*!
  \class LauncherClient
  \brief The LauncherClient class handles a single Launcher client.
 */

/*!
  Create a new LauncherClient with ProcessBackendManager \a manager
 */

LauncherClient::LauncherClient(ProcessBackendManager *manager)
    : QObject(manager)
    , m_manager(manager)
{
}

/*!
  Process an incoming \a message
 */

void LauncherClient::receive(const QJsonObject& message)
{
    qDebug() << Q_FUNC_INFO << message;
    QString cmd = message.value("command").toString();
    int id = message.value("id").toDouble();
    if ( cmd == "start" ) {
        ProcessInfo info(message.value("info").toObject().toVariantMap());
        ProcessBackend *backend = m_manager->create(info, this);
        if (backend) {
            connect(backend, SIGNAL(started()), SLOT(started()));
            connect(backend, SIGNAL(finished(int, QProcess::ExitStatus)),
                    SLOT(finished(int, QProcess::ExitStatus)));
            connect(backend, SIGNAL(error(QProcess::ProcessError)), SLOT(error(QProcess::ProcessError)));
            connect(backend, SIGNAL(stateChanged(QProcess::ProcessState)),
                    SLOT(stateChanged(QProcess::ProcessState)));
            connect(backend, SIGNAL(standardOutput(const QByteArray&)),
                    SLOT(standardOutput(const QByteArray&)));
            connect(backend, SIGNAL(standardError(const QByteArray&)),
                    SLOT(standardError(const QByteArray&)));
            m_idToBackend.insert(id, backend);
            m_backendToId.insert(backend, id);
            backend->start();
        }
    }
    else if ( cmd == "stop" ) {
        ProcessBackend *backend = m_idToBackend.value(id);
        if (backend) {
            int timeout = message.value("timeout").toDouble();
            backend->stop(timeout);
        }
    }
    else if ( cmd == "set" ) {
        ProcessBackend *backend = m_idToBackend.value(id);
        if (backend) {
            QString key = message.value("key").toString();
            int value   = message.value("value").toDouble();
            if (key == "priority")
                backend->setDesiredPriority(value);
            else if (key == "oomAdjustment")
                backend->setDesiredOomAdjustment(value);
        }
    }
    else if ( cmd == "write" ) {
        QByteArray data = message.value("data").toString().toLocal8Bit();
        ProcessBackend *backend = m_idToBackend.value(id);
        if (backend)
            backend->write(data);
    }
}

static const QLatin1String kEvent("event");
static const QLatin1String kId("id");

/*!
  \internal
 */

void LauncherClient::started()
{
    ProcessBackend *backend = qobject_cast<ProcessBackend *>(sender());
    QJsonObject msg;
    msg.insert(kEvent, QLatin1String("started"));
    msg.insert(kId, m_backendToId.value(backend));
    msg.insert("pid", (double) backend->pid());
    emit send(msg);
}

/*!
  \internal
 */

void LauncherClient::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ProcessBackend *backend = qobject_cast<ProcessBackend *>(sender());
    QJsonObject msg;
    msg.insert(kEvent, QLatin1String("finished"));
    msg.insert(kId, m_backendToId.value(backend));
    msg.insert("exitCode", exitCode);
    msg.insert("exitStatus", exitStatus);
    emit send(msg);
}

/*!
  \internal
 */

void LauncherClient::error(QProcess::ProcessError err)
{
    ProcessBackend *backend = qobject_cast<ProcessBackend *>(sender());
    QJsonObject msg;
    msg.insert(kEvent, QLatin1String("error"));
    msg.insert(kId, m_backendToId.value(backend));
    msg.insert("error", err);
    emit send(msg);
}

/*!
  \internal
 */

void LauncherClient::stateChanged(QProcess::ProcessState state)
{
    ProcessBackend *backend = qobject_cast<ProcessBackend *>(sender());
    QJsonObject msg;
    msg.insert(kEvent, QLatin1String("stateChanged"));
    msg.insert(kId, m_backendToId.value(backend));
    msg.insert("stateChanged", state);
    emit send(msg);
}

/*!
  \internal
 */

void LauncherClient::standardOutput(const QByteArray& data)
{
    ProcessBackend *backend = qobject_cast<ProcessBackend *>(sender());
    QJsonObject msg;
    msg.insert(kEvent, QLatin1String("standardOutput"));
    msg.insert(kId, m_backendToId.value(backend));
    msg.insert(QLatin1String("data"), QString::fromLocal8Bit(data.data(), data.size()));
    emit send(msg);
}

/*!
  \internal
 */

void LauncherClient::standardError(const QByteArray& data)
{
    ProcessBackend *backend = qobject_cast<ProcessBackend *>(sender());
    QJsonObject msg;
    msg.insert(kEvent, QLatin1String("standardError"));
    msg.insert(kId, m_backendToId.value(backend));
    msg.insert(QLatin1String("data"), QString::fromLocal8Bit(data.data(), data.size()));
    emit send(msg);
}

/*!
  \fn void LauncherClient::send(const QJsonObject& message)

  Send a \a message to the remote controller.
*/

#include "moc_launcherclient.cpp"

QT_END_NAMESPACE_PROCESSMANAGER
