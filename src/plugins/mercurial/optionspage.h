/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Brian McGillion
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

#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include "ui_optionspage.h"

#include <vcsbase/vcsbaseoptionspage.h>

#include <QWidget>
#include <QPointer>

namespace Mercurial {
namespace Internal {

class MercurialSettings;

class OptionsPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsPageWidget(QWidget *parent = 0);

    MercurialSettings settings() const;
    void setSettings(const MercurialSettings &s);
    QString searchKeywords() const;

private:
    Ui::OptionsPage m_ui;
};


class OptionsPage : public VcsBase::VcsBaseOptionsPage
{
    Q_OBJECT

public:
    OptionsPage();
    QString id() const;
    QString displayName() const;

    QWidget *createPage(QWidget *parent);
    void apply();
    void finish() { }
    bool matches(const QString &s) const;

signals:
    void settingsChanged();

private:
    QString m_searchKeywords;
    QPointer<OptionsPageWidget> optionsPageWidget;
};

} // namespace Internal
} // namespace Mercurial

#endif // OPTIONSPAGE_H
