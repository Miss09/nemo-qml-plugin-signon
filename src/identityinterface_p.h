/*
 * Copyright (C) 2012 Jolla Ltd. <chris.adams@jollamobile.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef IDENTITYINTERFACE_P_H
#define IDENTITYINTERFACE_P_H

#include "identityinterface.h"

#include <QtCore/QObject>

//libsignon-qt
#include <SignOn/Identity>
#include <SignOn/identityinfo.h>

using namespace SignOn;

class IdentityInterfacePrivate : public QObject
{
    Q_OBJECT

public:
    IdentityInterfacePrivate(SignOn::Identity *ident, IdentityInterface *parent);
    ~IdentityInterfacePrivate();

    void setStatus(IdentityInterface::Status newStatus, const QString &message = QString());
    void setIdentity(SignOn::Identity *ident);

    IdentityInterface *q;

    SignOn::Identity *identity;
    SignOn::AuthSession *session;
    SignOn::IdentityInfo info;
    bool componentComplete;
    bool initializationComplete;
    bool pendingSync;

    // we keep a cache of the info's property data.
    // we only write to the info when we want to sync.
    QString userName;
    QString secret;
    QString caption;
    QStringList realms;
    QString owner;
    QStringList accessControlList;
    QMap<QString, QStringList> methodMechanisms;
    bool userNamePendingInit;
    bool secretPendingInit;
    bool captionPendingInit;
    bool realmsPendingInit;
    bool ownerPendingInit;
    bool accessControlListPendingInit;
    bool methodMechanismsPendingInit;

    // non-info property data.
    int identifier;
    bool identifierPending;
    IdentityInterface::Status status;
    IdentityInterface::ErrorType error;
    QString statusMessage;
    QString errorMessage;

    // auth session related data.
    QString currentMethod;
    QString currentMechanism;

public Q_SLOTS:
    void asyncQueryInfo();
    void handleInfo(const SignOn::IdentityInfo &retInfo);
    void handleCredentialsStored(quint32 newId);
    void handleRemoved();
    void handleError(SignOn::Error error);

    // auth session related
    void handleResponse(const SignOn::SessionData &sd);
    void handleStateChanged(AuthSession::AuthSessionState newState, const QString &message);

public:
    void setUpSessionSignals();
};



#endif
