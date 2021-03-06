/****************************************************************************
**
** Copyright (C) 2016 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#ifndef GDBSERVERPROVIDERPROCESS_H
#define GDBSERVERPROVIDERPROCESS_H

#include <projectexplorer/devicesupport/deviceprocess.h>

namespace ProjectExplorer { class Runnable; }
namespace Utils { class QtcProcess; }

namespace BareMetal {
namespace Internal {

class GdbServerProviderProcess : public ProjectExplorer::DeviceProcess
{
    Q_OBJECT
public:
    explicit GdbServerProviderProcess(
            const QSharedPointer<const ProjectExplorer::IDevice> &device,
            QObject *parent = 0);

    void start(const ProjectExplorer::Runnable &runnable);
    void interrupt();
    void terminate();
    void kill();

    QProcess::ProcessState state() const;
    QProcess::ExitStatus exitStatus() const;
    int exitCode() const;
    QString errorString() const;

    QByteArray readAllStandardOutput();
    QByteArray readAllStandardError();

    qint64 write(const QByteArray &data);

private:
    Utils::QtcProcess *m_process;
};

} // namespace Internal
} // namespace BareMetal

#endif // GDBSERVERPROVIDERPROCESS_H
