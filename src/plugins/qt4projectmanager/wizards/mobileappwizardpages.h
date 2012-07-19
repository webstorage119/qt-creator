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

#ifndef MOBILEAPPWIZARDPAGES_H
#define MOBILEAPPWIZARDPAGES_H

#include "abstractmobileapp.h"

#include <QWizardPage>

namespace Qt4ProjectManager {
namespace Internal {

class MobileAppWizardGenericOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit MobileAppWizardGenericOptionsPage(QWidget *parent = 0);
    virtual ~MobileAppWizardGenericOptionsPage();

    void setOrientation(AbstractMobileApp::ScreenOrientation orientation);
    AbstractMobileApp::ScreenOrientation orientation() const;

private:
    class MobileAppWizardGenericOptionsPagePrivate *d;
};

class MobileAppWizardSymbianOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit MobileAppWizardSymbianOptionsPage(QWidget *parent = 0);
    virtual ~MobileAppWizardSymbianOptionsPage();

    QString svgIcon() const;
    void setSvgIcon(const QString &icon);
    QString symbianUid() const;
    void setNetworkEnabled(bool enableIt);
    bool networkEnabled() const;
    void setSymbianUid(const QString &uid);

private slots:
    void openSvgIcon(); // Via file open dialog

private:
    class MobileAppWizardSymbianOptionsPagePrivate *d;
};

class MobileAppWizardMaemoOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit MobileAppWizardMaemoOptionsPage(QWidget *parent = 0);
    virtual ~MobileAppWizardMaemoOptionsPage();

    QString pngIcon() const;
    void setPngIcon(const QString &icon);

private slots:
    void openPngIcon();

private:
    class MobileAppWizardMaemoOptionsPagePrivate *d;
};

class MobileAppWizardHarmattanOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit MobileAppWizardHarmattanOptionsPage(QWidget *parent = 0);
    virtual ~MobileAppWizardHarmattanOptionsPage();

    QString pngIcon() const;
    void setPngIcon(const QString &icon);

    void setBoosterOptionEnabled(bool enable);
    bool supportsBooster() const;

private slots:
    void openPngIcon();

private:
    class MobileAppWizardHarmattanOptionsPagePrivate *d;
};

} // namespace Internal
} // namespace Qt4ProjectManager

#endif // MOBILEAPPWIZARDPAGES_H
