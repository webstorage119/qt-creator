/**************************************************************************
**
** Copyright (c) 2014 BogDan Vatra <bog_dan_ro@yahoo.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://www.qt.io/licensing.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "androiddevice.h"
#include "androidconstants.h"
#include "androidsignaloperation.h"

#include <QCoreApplication>

using namespace ProjectExplorer;

namespace Android {
namespace Internal {

AndroidDevice::AndroidDevice()
    : IDevice(Core::Id(Constants::ANDROID_DEVICE_TYPE),
                             IDevice::AutoDetected,
                             IDevice::Hardware,
                             Core::Id(Constants::ANDROID_DEVICE_ID))
{
    setDisplayName(QCoreApplication::translate("Android::Internal::AndroidDevice", "Run on Android"));
    setDeviceState(DeviceReadyToUse);
}

AndroidDevice::AndroidDevice(const AndroidDevice &other)
    : IDevice(other)
{ }


IDevice::DeviceInfo AndroidDevice::deviceInformation() const
{
    return IDevice::DeviceInfo();
}

QString AndroidDevice::displayType() const
{
    return QCoreApplication::translate("Android::Internal::AndroidDevice", "Android");
}

IDeviceWidget *AndroidDevice::createWidget()
{
    return 0;
}

QList<Core::Id> AndroidDevice::actionIds() const
{
    return QList<Core::Id>();
}

QString AndroidDevice::displayNameForActionId(Core::Id actionId) const
{
    Q_UNUSED(actionId)
    return QString();
}

void AndroidDevice::executeAction(Core::Id actionId, QWidget *parent)
{
    Q_UNUSED(actionId)
    Q_UNUSED(parent)
}

bool AndroidDevice::canAutoDetectPorts() const
{
    return true;
}

DeviceProcessSignalOperation::Ptr AndroidDevice::signalOperation() const
{
    return DeviceProcessSignalOperation::Ptr(new AndroidSignalOperation());
}

IDevice::Ptr AndroidDevice::clone() const
{
    return IDevice::Ptr(new AndroidDevice(*this));
}

QString AndroidDevice::qmlProfilerHost() const
{
    return QLatin1String("localhost");
}

} // namespace Internal
} // namespace Android