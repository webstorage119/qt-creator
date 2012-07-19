/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "completecomponentcommand.h"

namespace QmlDesigner {

CompleteComponentCommand::CompleteComponentCommand()
{
}

CompleteComponentCommand::CompleteComponentCommand(const QVector<qint32> &container)
    : m_instanceVector(container)
{
}

QVector<qint32> CompleteComponentCommand::instances() const
{
    return m_instanceVector;
}

QDataStream &operator<<(QDataStream &out, const CompleteComponentCommand &command)
{
    out << command.instances();

    return out;
}

QDataStream &operator>>(QDataStream &in, CompleteComponentCommand &command)
{
    in >> command.m_instanceVector;

    return in;
}

} // namespace QmlDesigner
