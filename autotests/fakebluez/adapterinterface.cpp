#include "adapterinterface.h"

#include <QTimer>
#include <QDBusConnection>

// AdapterObject
AdapterObject::AdapterObject(const QDBusObjectPath &path, QObject *parent)
    : QObject(parent)
{
    QDBusConnection::sessionBus().registerObject(path.path(), this);
}

// AdapterInterface
AdapterInterface::AdapterInterface(const QDBusObjectPath &path, const QVariantMap &properties, QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    setPath(path);
    setProperties(properties);
    setName(QStringLiteral("org.bluez.Adapter1"));
}

QString AdapterInterface::address() const
{
    return Object::property(QStringLiteral("Address")).toString();
}

QString AdapterInterface::name() const
{
    return Object::property(QStringLiteral("Name")).toString();
}

QString AdapterInterface::alias() const
{
    return Object::property(QStringLiteral("Alias")).toString();
}

void AdapterInterface::setAlias(const QString &alias)
{
    Object::setProperty(QStringLiteral("Alias"), alias);
}

quint32 AdapterInterface::adapterClass() const
{
    return Object::property(QStringLiteral("Class")).toUInt();
}

bool AdapterInterface::powered() const
{
    return Object::property(QStringLiteral("Powered")).toBool();
}

void AdapterInterface::setPowered(bool powered)
{
    Object::setProperty(QStringLiteral("Powered"), powered);
}

bool AdapterInterface::discoverable() const
{
    return Object::property(QStringLiteral("Discoverable")).toBool();
}

void AdapterInterface::setDiscoverable(bool discoverable)
{
    Object::setProperty(QStringLiteral("Discoverable"), discoverable);

    if (discoverable && discoverableTimeout() != 0) {
        QTimer::singleShot(discoverableTimeout() * 1000, this, SLOT(resetDiscoverable()));
    }
}

bool AdapterInterface::pairable() const
{
    return Object::property(QStringLiteral("Pairable")).toBool();
}

void AdapterInterface::setPairable(bool pairable)
{
    Object::setProperty(QStringLiteral("Pairable"), pairable);

    if (pairable && pairableTimeout() != 0) {
        QTimer::singleShot(pairableTimeout() * 1000, this, SLOT(resetPairable()));
    }
}

quint32 AdapterInterface::pairableTimeout() const
{
    return Object::property(QStringLiteral("PairableTimeout")).toUInt();
}

void AdapterInterface::setPairableTimeout(quint32 timeout)
{
    Object::setProperty(QStringLiteral("PairableTimeout"), timeout);
}

quint32 AdapterInterface::discoverableTimeout() const
{
    return Object::property(QStringLiteral("DiscoverableTimeout")).toUInt();
}

void AdapterInterface::setDiscoverableTimeout(quint32 timeout)
{
    Object::setProperty(QStringLiteral("DiscoverableTimeout"), timeout);
}

bool AdapterInterface::discovering() const
{
    return Object::property(QStringLiteral("Discovering")).toBool();
}

QStringList AdapterInterface::uuids() const
{
    return Object::property(QStringLiteral("UUIDs")).toStringList();
}

QString AdapterInterface::modalias() const
{
    return Object::property(QStringLiteral("Modalias")).toString();
}

void AdapterInterface::StartDiscovery()
{
    Object::setProperty(QStringLiteral("Discovering"), true);
}

void AdapterInterface::StopDiscovery()
{
    Object::setProperty(QStringLiteral("Discovering"), false);
}

void AdapterInterface::RemoveDevice(const QDBusObjectPath &device)
{
    // TODO
    Q_UNUSED(device)
}

void AdapterInterface::resetPairable()
{
    setPairable(false);
}

void AdapterInterface::resetDiscoverable()
{
    setDiscoverable(false);
}