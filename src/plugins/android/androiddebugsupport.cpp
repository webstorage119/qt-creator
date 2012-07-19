/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 BogDan Vatra <bog_dan_ro@yahoo.com>
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

#include "androiddebugsupport.h"

#include "androiddeploystep.h"
#include "androidglobal.h"
#include "androidrunner.h"
#include "androidmanager.h"

#include <debugger/debuggerengine.h>
#include <debugger/debuggerplugin.h>
#include <debugger/debuggerprofileinformation.h>
#include <debugger/debuggerrunner.h>
#include <debugger/debuggerstartparameters.h>

#include <projectexplorer/target.h>
#include <qt4projectmanager/qt4buildconfiguration.h>
#include <qt4projectmanager/qt4nodes.h>
#include <qt4projectmanager/qt4project.h>
#include <qtsupport/qtprofileinformation.h>

#include <QDir>

using namespace Debugger;
using namespace ProjectExplorer;
using namespace Qt4ProjectManager;

namespace Android {
namespace Internal {

static const char * const qMakeVariables[] = {
         "QT_INSTALL_LIBS",
         "QT_INSTALL_PLUGINS",
         "QT_INSTALL_IMPORTS"
};

static Qt4Project *project(AndroidRunConfiguration *rc)
{ return static_cast<Qt4Project *>(rc->target()->project()); }

RunControl *AndroidDebugSupport::createDebugRunControl(AndroidRunConfiguration *runConfig)
{
    DebuggerStartParameters params;
    params.startMode = AttachToRemoteServer;
    params.displayName = AndroidManager::packageName(runConfig->target());
    params.remoteSetupNeeded = true;

    if (runConfig->debuggerAspect()->useCppDebugger()) {
        params.languages |= CppLanguage;
        Profile *profile = runConfig->target()->profile();
        params.sysRoot = SysRootProfileInformation::sysRoot(profile).toString();
        params.debuggerCommand = DebuggerProfileInformation::debuggerCommand(profile).toString();
        if (ToolChain *tc = ToolChainProfileInformation::toolChain(profile))
            params.toolChainAbi = tc->targetAbi();
        params.dumperLibrary = runConfig->dumperLib();
        params.executable = project(runConfig)->rootQt4ProjectNode()->buildDir() + QLatin1String("/app_process");
        params.remoteChannel = runConfig->remoteChannel();
        params.remoteArchitecture = QLatin1String("arm");
        params.useServerStartScript = true;

        params.solibSearchPath.clear();
        QList<Qt4ProFileNode *> nodes = project(runConfig)->allProFiles();
        foreach (Qt4ProFileNode *node, nodes)
            if (node->projectType() == ApplicationTemplate)
                params.solibSearchPath.append(node->targetInformation().buildDir);
        QtSupport::BaseQtVersion *version = QtSupport::QtProfileInformation::qtVersion(runConfig->target()->profile());
        params.solibSearchPath.append(qtSoPaths(version));
    }
    if (runConfig->debuggerAspect()->useQmlDebugger()) {
        params.languages |= QmlLanguage;
        params.qmlServerAddress = QLatin1String("localhost");
        params.qmlServerPort = runConfig->debuggerAspect()->qmlDebugServerPort();
        //TODO: Not sure if these are the right paths.
        params.projectSourceDirectory = project(runConfig)->projectDirectory();
        params.projectSourceFiles = project(runConfig)->files(Qt4Project::ExcludeGeneratedFiles);
        params.projectBuildDirectory = project(runConfig)->rootQt4ProjectNode()->buildDir();
    }

    DebuggerRunControl * const debuggerRunControl
        = DebuggerPlugin::createDebugger(params, runConfig);
    new AndroidDebugSupport(runConfig, debuggerRunControl);
    return debuggerRunControl;
}

AndroidDebugSupport::AndroidDebugSupport(AndroidRunConfiguration *runConfig,
    DebuggerRunControl *runControl)
    : QObject(runControl), m_runControl(runControl),
      m_runner(new AndroidRunner(this, runConfig, true)),
      m_debuggingType(runConfig->debuggingType()),
      m_gdbServerPort(5039), m_qmlPort(runConfig->debuggerAspect()->qmlDebugServerPort())
{
    Q_ASSERT(runConfig->debuggerAspect()->useCppDebugger() || runConfig->debuggerAspect()->useQmlDebugger());

    connect(m_runControl->engine(), SIGNAL(requestRemoteSetup()),
            m_runner, SLOT(start()));
    connect(m_runControl, SIGNAL(finished()),
            m_runner, SLOT(stop()));

    connect(m_runner, SIGNAL(remoteProcessStarted(int,int)),
        SLOT(handleRemoteProcessStarted(int,int)));
    connect(m_runner, SIGNAL(remoteProcessFinished(const QString &)),
        SLOT(handleRemoteProcessFinished(const QString &)));

    connect(m_runner, SIGNAL(remoteErrorOutput(QByteArray)),
        SLOT(handleRemoteErrorOutput(QByteArray)));
    connect(m_runner, SIGNAL(remoteOutput(QByteArray)),
        SLOT(handleRemoteOutput(QByteArray)));
}

AndroidDebugSupport::~AndroidDebugSupport()
{
}

void AndroidDebugSupport::handleRemoteProcessStarted(int gdbServerPort, int qmlPort)
{
    disconnect(m_runner, SIGNAL(remoteProcessStarted(int,int)),
        this, SLOT(handleRemoteProcessStarted(int,int)));
    m_runControl->engine()->notifyEngineRemoteSetupDone(gdbServerPort, qmlPort);
}

void AndroidDebugSupport::handleRemoteProcessFinished(const QString &errorMsg)
{
    disconnect(m_runner, SIGNAL(remoteProcessFinished(const QString &)),
        this,SLOT(handleRemoteProcessFinished(const QString &)));
    m_runControl->engine()->notifyEngineRemoteSetupFailed(errorMsg);
}

void AndroidDebugSupport::handleRemoteOutput(const QByteArray &output)
{
    if (m_runControl) {
        if (m_runControl->engine())
            m_runControl->engine()->showMessage(QString::fromUtf8(output), AppOutput);
        else
            m_runControl->showMessage(QString::fromUtf8(output), AppOutput);
    }
}

void AndroidDebugSupport::handleRemoteErrorOutput(const QByteArray &output)
{
    if (m_runControl) {
        if (m_runControl->engine())
            m_runControl->engine()->showMessage(QString::fromUtf8(output), AppError);
        else
            m_runControl->showMessage(QString::fromUtf8(output), AppError);
    }
}

QStringList AndroidDebugSupport::qtSoPaths(QtSupport::BaseQtVersion *qtVersion)
{
    if (!qtVersion)
        return QStringList();

    QSet<QString> paths;
    for (uint i = 0; i < sizeof qMakeVariables / sizeof qMakeVariables[0]; ++i) {
        QString path = qtVersion->qmakeProperty(qMakeVariables[i]);
        if (path.isNull())
            continue;
        QDirIterator it(path, QStringList() << QLatin1String("*.so"), QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            paths.insert(it.fileInfo().absolutePath());
        }
    }
    return paths.toList();
}

} // namespace Internal
} // namespace Qt4ProjectManager
