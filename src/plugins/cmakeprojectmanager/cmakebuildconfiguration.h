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

#ifndef CMAKEBUILDCONFIGURATION_H
#define CMAKEBUILDCONFIGURATION_H

#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/abi.h>

namespace ProjectExplorer {
class ToolChain;
}

namespace CMakeProjectManager {
namespace Internal {

class CMakeBuildConfigurationFactory;

class CMakeBuildConfiguration : public ProjectExplorer::BuildConfiguration
{
    Q_OBJECT
    friend class CMakeBuildConfigurationFactory;

public:
    CMakeBuildConfiguration(ProjectExplorer::Target *parent);
    ~CMakeBuildConfiguration();

    ProjectExplorer::BuildConfigWidget *createConfigWidget();
    QString buildDirectory() const;

    void setBuildDirectory(const QString &buildDirectory);

    QVariantMap toMap() const;

    ProjectExplorer::IOutputParser *createOutputParser() const;

    Utils::Environment baseEnvironment() const;

    BuildType buildType() const;

protected:
    CMakeBuildConfiguration(ProjectExplorer::Target *parent, CMakeBuildConfiguration *source);
    virtual bool fromMap(const QVariantMap &map);

private:
    QString m_buildDirectory;
    QString m_msvcVersion;
};

class CMakeBuildConfigurationFactory : public ProjectExplorer::IBuildConfigurationFactory
{
    Q_OBJECT

public:
    CMakeBuildConfigurationFactory(QObject *parent = 0);
    ~CMakeBuildConfigurationFactory();

    QList<Core::Id> availableCreationIds(const ProjectExplorer::Target *parent) const;
    QString displayNameForId(const Core::Id id) const;

    bool canCreate(const ProjectExplorer::Target *parent, const Core::Id id) const;
    CMakeBuildConfiguration *create(ProjectExplorer::Target *parent, const Core::Id id, const QString &name = QString());
    bool canClone(const ProjectExplorer::Target *parent, ProjectExplorer::BuildConfiguration *source) const;
    CMakeBuildConfiguration *clone(ProjectExplorer::Target *parent, ProjectExplorer::BuildConfiguration *source);
    bool canRestore(const ProjectExplorer::Target *parent, const QVariantMap &map) const;
    CMakeBuildConfiguration *restore(ProjectExplorer::Target *parent, const QVariantMap &map);

private:
    bool canHandle(const ProjectExplorer::Target *t) const;
};

} // namespace Internal
} // namespace CMakeProjectManager

#endif // CMAKEBUILDCONFIGURATION_H
