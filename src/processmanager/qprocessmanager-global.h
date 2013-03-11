/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtAddOn.JsonStream module of the Qt.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef PROCESSMANAGER_GLOBAL_H
#define PROCESSMANAGER_GLOBAL_H

#include "qglobal.h"

#if defined(QT_ADDON_PROCESSMANAGER_LIB)
#  define Q_ADDON_PROCESSMANAGER_EXPORT Q_DECL_EXPORT
#else
#  define Q_ADDON_PROCESSMANAGER_EXPORT Q_DECL_IMPORT
#endif

#if defined(QT_NAMESPACE)
#  define QT_BEGIN_NAMESPACE_PROCESSMANAGER namespace QT_NAMESPACE { namespace QtAddOn { namespace QtProcessManager {
#  define QT_END_NAMESPACE_PROCESSMANAGER } } }
#  define QT_USE_NAMESPACE_PROCESSMANAGER using namespace QT_NAMESPACE::QtAddOn::QtProcessManager;
#  define QT_PREPEND_NAMESPACE_PROCESSMANAGER(name) ::QT_NAMESPACE::QtAddOn::QtProcessManager::name
#else
#  define QT_BEGIN_NAMESPACE_PROCESSMANAGER namespace QtAddOn { namespace QtProcessManager {
#  define QT_END_NAMESPACE_PROCESSMANAGER } }
#  define QT_USE_NAMESPACE_PROCESSMANAGER using namespace QtAddOn::QtProcessManager;
#  define QT_PREPEND_NAMESPACE_PROCESSMANAGER(name) ::QtAddOn::QtProcessManager::name
#endif

#define QT_PROCESSMANAGER_DECLARE_METATYPE_PTR(name)  Q_DECLARE_METATYPE(QtAddOn::QtProcessManager::name *)
#define QT_PROCESSMANAGER_DECLARE_METATYPE_CONST_PTR(name)  Q_DECLARE_METATYPE(const QtAddOn::QtProcessManager::name *)

// a workaround for moc - if there is a header file that doesn't use processmanager
// namespace, we still force moc to do "using namespace" but the namespace have to
// be defined, so let's define an empty namespace here
QT_BEGIN_NAMESPACE_PROCESSMANAGER
QT_END_NAMESPACE_PROCESSMANAGER

#endif // PROCESSMANAGER_GLOBAL_H