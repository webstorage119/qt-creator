/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
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

#include "maemopackagecreationfactory.h"

#include "maemopackagecreationstep.h"
#include "maddedevice.h"
#include "qt4maemodeployconfiguration.h"

#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/buildsteplist.h>
#include <projectexplorer/deployconfiguration.h>
#include <projectexplorer/profileinformation.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/target.h>

#include <QCoreApplication>

using ProjectExplorer::BuildStepList;
using ProjectExplorer::BuildStep;

namespace Madde {
namespace Internal {
namespace {
const char OldCreatePackageId[] = "Qt4ProjectManager.MaemoPackageCreationStep";
} // anonymous namespace

MaemoPackageCreationFactory::MaemoPackageCreationFactory(QObject *parent)
    : ProjectExplorer::IBuildStepFactory(parent)
{
}

QList<Core::Id> MaemoPackageCreationFactory::availableCreationIds(ProjectExplorer::BuildStepList *parent) const
{
    QList<Core::Id> ids;
    if (!qobject_cast<Qt4MaemoDeployConfiguration *>(parent->parent()))
        return ids;
    Core::Id deviceType = ProjectExplorer::DeviceTypeProfileInformation::deviceTypeId(parent->target()->profile());
    if (MaddeDevice::isDebianBased(deviceType)
            && !parent->contains(MaemoDebianPackageCreationStep::CreatePackageId))
        ids << MaemoDebianPackageCreationStep::CreatePackageId;
    else if (!MaddeDevice::isDebianBased(deviceType)
               && !parent->contains(MaemoRpmPackageCreationStep::CreatePackageId))
        ids << MaemoRpmPackageCreationStep::CreatePackageId;
    return ids;
}

QString MaemoPackageCreationFactory::displayNameForId(const Core::Id id) const
{
    if (id == MaemoDebianPackageCreationStep::CreatePackageId) {
        return QCoreApplication::translate("RemoteLinux::Internal::MaemoPackageCreationFactory",
            "Create Debian Package");
    } else if (id == MaemoRpmPackageCreationStep::CreatePackageId) {
        return QCoreApplication::translate("RemoteLinux::Internal::MaemoPackageCreationFactory",
            "Create RPM Package");
    }
    return QString();
}

bool MaemoPackageCreationFactory::canCreate(ProjectExplorer::BuildStepList *parent, const Core::Id id) const
{
    return availableCreationIds(parent).contains(id);
}

BuildStep *MaemoPackageCreationFactory::create(ProjectExplorer::BuildStepList *parent, const Core::Id id)
{
    Q_ASSERT(canCreate(parent, id));
    if (id == MaemoDebianPackageCreationStep::CreatePackageId)
        return new MaemoDebianPackageCreationStep(parent);
    else if (id == MaemoRpmPackageCreationStep::CreatePackageId)
        return new MaemoRpmPackageCreationStep(parent);
    return 0;
}

bool MaemoPackageCreationFactory::canRestore(ProjectExplorer::BuildStepList *parent,
                                             const QVariantMap &map) const
{
    const Core::Id id = ProjectExplorer::idFromMap(map);
    return canCreate(parent, id) || id == Core::Id(OldCreatePackageId);
}

BuildStep *MaemoPackageCreationFactory::restore(ProjectExplorer::BuildStepList *parent,
                                                const QVariantMap &map)
{
    Q_ASSERT(canRestore(parent, map));
    BuildStep * step = 0;
    Core::Id deviceType
            = ProjectExplorer::DeviceTypeProfileInformation::deviceTypeId(parent->target()->profile());
    const Core::Id id = ProjectExplorer::idFromMap(map);
    if (id == MaemoDebianPackageCreationStep::CreatePackageId
            || (id == Core::Id(OldCreatePackageId)
                && MaddeDevice::isDebianBased(deviceType))) {
        step = new MaemoDebianPackageCreationStep(parent);
    } else if (id == MaemoRpmPackageCreationStep::CreatePackageId
               || (id == Core::Id(OldCreatePackageId)
                   && !MaddeDevice::isDebianBased(deviceType))) {
        step = new MaemoRpmPackageCreationStep(parent);
    }
    Q_ASSERT(step);

    if (!step->fromMap(map)) {
        delete step;
        return 0;
    }
    return step;
}

bool MaemoPackageCreationFactory::canClone(ProjectExplorer::BuildStepList *parent,
                                           ProjectExplorer::BuildStep *product) const
{
    return canCreate(parent, product->id());
}

BuildStep *MaemoPackageCreationFactory::clone(ProjectExplorer::BuildStepList *parent,
                                              ProjectExplorer::BuildStep *product)
{
    Q_ASSERT(canClone(parent, product));
    if (MaemoDebianPackageCreationStep * const debianStep
            = qobject_cast<MaemoDebianPackageCreationStep *>(product)) {
        return new MaemoDebianPackageCreationStep(parent, debianStep);
    }
    if (MaemoRpmPackageCreationStep * const rpmStep
            = qobject_cast<MaemoRpmPackageCreationStep *>(product)) {
        return new MaemoRpmPackageCreationStep(parent, rpmStep);
    }
    return 0;
}

} // namespace Internal
} // namespace Madde
