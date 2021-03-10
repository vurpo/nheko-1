#pragma once

#include <QObject>
#include <QDBusConnection>
#include <QDBusAbstractAdaptor>
#include <QSharedPointer>

#include "UserSettingsPage.h"

class UnifiedPushConnectorAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.unifiedpush.Connector1")

    public:
        UnifiedPushConnectorAdaptor(QSharedPointer<UserSettings> userSettings, QObject *parent);

    public slots:
        Q_NOREPLY void Message(const QString &token, const QString &message, const QString &id);
        Q_NOREPLY void NewEndpoint(const QString &token, const QString &endpoint);
        Q_NOREPLY void Unregister(const QString &token);
    
    private:
        QSharedPointer<UserSettings> userSettings_;
};