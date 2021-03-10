#include <QObject>
#include <QDBusConnection>
#include <mtx/requests.hpp>
#include <mtx/responses.hpp>

#include "UnifiedPushConnector.h"
#include "ChatPage.h"

UnifiedPushConnectorAdaptor::UnifiedPushConnectorAdaptor(QObject* parent)
    : QDBusAbstractAdaptor(parent)
{
}

void UnifiedPushConnectorAdaptor::Message(const QString &token, const QString &message, const QString &id) {
    ((ChatPage *)parent())->pushMessageReceived(token, message, id);
}

void UnifiedPushConnectorAdaptor::NewEndpoint(const QString &token, const QString &endpoint) {
    ((ChatPage *)parent())->pushNewEndpoint(token, endpoint);
}

void UnifiedPushConnectorAdaptor::Unregister(const QString &token) {
    ((ChatPage *)parent())->pushUnregistered(token);
}