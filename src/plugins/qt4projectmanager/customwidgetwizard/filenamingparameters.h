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

#ifndef FILENAMINGPARAMETERS_H
#define FILENAMINGPARAMETERS_H

#include <QString>
#include <QFileInfo>

namespace Qt4ProjectManager {
namespace Internal {

/* Helper struct specifying how to generate file names
 * from class names according to the CppTools settings. */

struct FileNamingParameters
{
    FileNamingParameters(const QString &headerSuffixIn = QString(QLatin1Char('h')),
                         const QString &sourceSuffixIn = QLatin1String("cpp"),
                         bool lowerCaseIn = true) :
        headerSuffix(headerSuffixIn),
        sourceSuffix(sourceSuffixIn),
        lowerCase(lowerCaseIn) {}

    inline QString sourceFileName(const QString &className) const {
        QString rc = lowerCase ? className.toLower() : className;
        rc += QLatin1Char('.');
        rc += sourceSuffix;
        return rc;
    }

    inline QString headerFileName(const QString &className) const {
        QString rc = lowerCase ? className.toLower() : className;
        rc += QLatin1Char('.');
        rc += headerSuffix;
        return rc;
    }

    inline QString sourceToHeaderFileName(const QString &source) const {
        QString rc = QFileInfo(source).completeBaseName();
        rc += QLatin1Char('.');
        rc += headerSuffix;
        return rc;
    }

    inline QString headerToSourceFileName(const QString &header) const {
        QString rc = QFileInfo(header).completeBaseName();
        rc += QLatin1Char('.');
        rc += sourceSuffix;
        return rc;
    }

    QString headerSuffix;
    QString sourceSuffix;
    bool lowerCase;
};

}
}
#endif // FILENAMINGPARAMETERS_H
