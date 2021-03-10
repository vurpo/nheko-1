#include <QObject>
#include <QDBusConnection>

#include "UnifiedPushConnector.h"
#include "Logging.h"

UnifiedPushConnectorAdaptor::UnifiedPushConnectorAdaptor(QSharedPointer<UserSettings> userSettings, QObject* parent)
    : QDBusAbstractAdaptor(parent)
    , userSettings_{userSettings}
{
}

void UnifiedPushConnectorAdaptor::Message(const QString &token, const QString &message, const QString &id)
{
    if (userSettings_->unifiedPushRegistered() && token == userSettings_->unifiedPushToken()) {
        nhlog::net()->info(QString("New UP push message: %1").arg(message).toStdString());
    }
}

void UnifiedPushConnectorAdaptor::NewEndpoint(const QString &token, const QString &endpoint)
{
    if (token == userSettings_->unifiedPushToken()) {
        nhlog::net()->info(QString("Received new UP endpoint: %1").arg(endpoint).toStdString());
        userSettings_->setUnifiedPushEndpoint(endpoint);
        // TODO: Update the pusher on the Matrix homeserver here!
        userSettings_->setUnifiedPushRegistered(true);
    }
}

void UnifiedPushConnectorAdaptor::Unregister(const QString &token)
{
    if (userSettings_->unifiedPushRegistered() && token == userSettings_->unifiedPushToken()) {
        nhlog::net()->info("Unregistered from UP");
        userSettings_->setUnifiedPushRegistered(false);
    }
}