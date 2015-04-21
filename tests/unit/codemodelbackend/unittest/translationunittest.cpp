/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"
#include "gmock/gmock.h"

#include <clang-c/Index.h>

#include <translationunit.h>
#include <unsavedfiles.h>
#include <utf8string.h>
#include <project.h>

#include "translationunitisnullexception.h"
#include "translationunitfilenotexitsexception.h"

using CodeModelBackEnd::TranslationUnit;
using CodeModelBackEnd::UnsavedFiles;
using CodeModelBackEnd::Project;

using testing::IsNull;
using testing::NotNull;

namespace {

TEST(TranslationUnit, DefaultTranslationUnitIsInvalid)
{
    TranslationUnit translationUnit;

    ASSERT_TRUE(translationUnit.isNull());
}

TEST(TranslationUnit, ThrowExceptionForNonExistingFilePath)
{
    ASSERT_THROW(TranslationUnit(Utf8StringLiteral("file.cpp"), UnsavedFiles(), Project(Utf8StringLiteral("/path/to/projectfile"))), CodeModelBackEnd::TranslationUnitFileNotExitsException);
}

TEST(TranslationUnit, TranslationUnitIsValid)
{
    TranslationUnit translationUnit(Utf8StringLiteral("data/complete_testfile_1.cpp"), UnsavedFiles(), Project(Utf8StringLiteral("/path/to/projectfile")));

    ASSERT_FALSE(translationUnit.isNull());
}


TEST(TranslationUnit, ThrowExceptionForGettingIndexForInvalidUnit)
{
    TranslationUnit translationUnit;

    ASSERT_THROW(translationUnit.index(), CodeModelBackEnd::TranslationUnitIsNullException);
}

TEST(TranslationUnit, IndexGetterIsNonNullForValidUnit)
{
    TranslationUnit translationUnit(Utf8StringLiteral("data/complete_testfile_1.cpp"), UnsavedFiles(), Project(Utf8StringLiteral("/path/to/projectfile")));

    ASSERT_THAT(translationUnit.index(), NotNull());
}

TEST(TranslationUnit, ThrowExceptionForGettingCxTranslationUnitForInvalidUnit)
{
    TranslationUnit translationUnit;

    ASSERT_THROW(translationUnit.cxTranslationUnit(), CodeModelBackEnd::TranslationUnitIsNullException);
}

TEST(TranslationUnit, CxTranslationUnitGetterIsNonNullForValidUnit)
{
    UnsavedFiles unsavedFiles;
    TranslationUnit translationUnit(Utf8StringLiteral("data/complete_testfile_1.cpp"), unsavedFiles, Project(Utf8StringLiteral("/path/to/projectfile")));

    ASSERT_THAT(translationUnit.cxTranslationUnit(), NotNull());
}

TEST(TranslationUnit, ThrowExceptionIfGettingFilePathForNullUnit)
{
    TranslationUnit translationUnit;

    ASSERT_THROW(translationUnit.filePath(), CodeModelBackEnd::TranslationUnitIsNullException);
}

TEST(TranslationUnit, ResetedTranslationUnitIsNull)
{
    TranslationUnit translationUnit(Utf8StringLiteral("data/complete_testfile_1.cpp"), UnsavedFiles(), Project(Utf8StringLiteral("/path/to/projectfile")));

    translationUnit.reset();

    ASSERT_TRUE(translationUnit.isNull());
}
}
