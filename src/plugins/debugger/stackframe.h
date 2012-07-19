/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/

#ifndef DEBUGGER_STACKFRAME_H
#define DEBUGGER_STACKFRAME_H

#include <QList>
#include <QMetaType>
#include <QString>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE
class QDebug;
QT_END_NAMESPACE

namespace Debugger {
namespace Internal {

class StackFrame
{
public:
    StackFrame();
    void clear();
    bool isUsable() const;
    QString toToolTip() const;
    QString toString() const;

public:
    qint32 level;
    QString function;
    QString file;  // We try to put an absolute file name in there.
    QString from;  // Sometimes something like "/usr/lib/libstdc++.so.6"
    QString to;    // Used in ScriptEngine only.
    qint32 line;
    quint64 address;
    bool usable;

    Q_DECLARE_TR_FUNCTIONS(StackHandler)
};

QDebug operator<<(QDebug d, const StackFrame &frame);

typedef QList<StackFrame> StackFrames;

} // namespace Internal
} // namespace Debugger

Q_DECLARE_METATYPE(Debugger::Internal::StackFrame)

#endif // DEBUGGER_STACKFRAME_H
