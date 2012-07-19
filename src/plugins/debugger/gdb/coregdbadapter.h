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

#ifndef DEBUGGER_COREGDBADAPTER_H
#define DEBUGGER_COREGDBADAPTER_H

#include "gdbengine.h"
#include "localgdbprocess.h"

namespace Debugger {
namespace Internal {

///////////////////////////////////////////////////////////////////////
//
// CoreGdbAdapter
//
///////////////////////////////////////////////////////////////////////

class GdbCoreEngine : public GdbEngine
{
    Q_OBJECT

public:
    GdbCoreEngine(const DebuggerStartParameters &startParameters,
        DebuggerEngine *masterEngine);
    ~GdbCoreEngine();

private:
    DumperHandling dumperHandling() const { return DumperNotAvailable; }

    void setupEngine();
    void setupInferior();
    void runEngine();
    void interruptInferior();
    void shutdownEngine();

    AbstractGdbProcess *gdbProc() { return &m_gdbProc; }

    void handleFileExecAndSymbols(const GdbResponse &response);
    void handleTargetCore(const GdbResponse &response);
    void handleRoundTrip(const GdbResponse &response);
    void unpackCoreIfNeeded();
    QString coreFileName() const;
    Q_SLOT void continueSetupEngine();
    QString coreName() const;

    QString m_executable;
    QString m_coreName;
    LocalGdbProcess m_gdbProc;
    QString m_tempCoreName;
};

} // namespace Internal
} // namespace Debugger

#endif // DEBUGGER_COREDBADAPTER_H
