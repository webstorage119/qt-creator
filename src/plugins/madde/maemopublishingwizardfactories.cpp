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
#include "maemopublishingwizardfactories.h"

#include "maemoconstants.h"
#include "maemoglobal.h"
#include "maemopublishingwizardfremantlefree.h"

#include <projectexplorer/target.h>
#include <qt4projectmanager/qmakestep.h>
#include <qt4projectmanager/qt4project.h>
#include <qt4projectmanager/qt4projectmanagerconstants.h>
#include <qt4projectmanager/qt4buildconfiguration.h>
#include <qtsupport/baseqtversion.h>
#include <qtsupport/qtprofileinformation.h>
#include <qtsupport/qtsupportconstants.h>

using namespace ProjectExplorer;
using namespace Qt4ProjectManager;

namespace Madde {
namespace Internal {

MaemoPublishingWizardFactoryFremantleFree::MaemoPublishingWizardFactoryFremantleFree(QObject *parent)
    : IPublishingWizardFactory(parent)
{
}

QString MaemoPublishingWizardFactoryFremantleFree::displayName() const
{
    return tr("Publish for \"Fremantle Extras-devel free\" repository");
}

QString MaemoPublishingWizardFactoryFremantleFree::description() const
{
    return tr("This wizard will create a source archive and optionally upload "
              "it to a build server, where the project will be compiled and "
              "packaged and then moved to the \"Extras-devel free\" "
              "repository, from where users can install it onto their N900 "
              "devices. For the upload functionality, an account at "
              "garage.maemo.org is required.");
}

bool MaemoPublishingWizardFactoryFremantleFree::canCreateWizard(const Project *project) const
{
    if (!qobject_cast<const Qt4Project *>(project))
        return false;
    foreach (const Target *const target, project->targets()) {
        QtSupport::BaseQtVersion *version = QtSupport::QtProfileInformation::qtVersion(target->profile());
        const QString &platform = version ? version->platformName() : QString();
        if (platform == QLatin1String(QtSupport::Constants::MAEMO_FREMANTLE_PLATFORM))
            return true;
    }
    return false;
}

QWizard *MaemoPublishingWizardFactoryFremantleFree::createWizard(const Project *project) const
{
    Q_ASSERT(canCreateWizard(project));
    return new MaemoPublishingWizardFremantleFree(project);
}

} // namespace Internal
} // namespace Madde
