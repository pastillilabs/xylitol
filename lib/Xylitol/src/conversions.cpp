#include "conversions.h"

#include "Xylitol/abstractlistmodel.h"
#include "Xylitol/logging.h"
#include "Xylitol/templates.h"

#include <QBitArray>
#include <QBuffer>
#include <QColor>
#include <QDataStream>
#include <QDate>
#include <QDateTime>
#include <QFont>
#include <QImage>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QLine>
#include <QLineF>
#include <QLocale>
#include <QMatrix4x4>
#include <QMetaProperty>
#include <QPoint>
#include <QPointF>
#include <QQuaternion>
#include <QRect>
#include <QRectF>
#include <QSize>
#include <QSizeF>
#include <QStringList>
#include <QTime>
#include <QTransform>
#include <QUrl>
#include <QUuid>
#include <QVariant>
#include <QVariantMap>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

namespace Xylitol {
namespace Private {

namespace {

QByteArray imageToByteArray(const QImage& image) {
    QByteArray byteArray;

    QBuffer buffer(&byteArray);
    if(buffer.open(QBuffer::WriteOnly)) {
        image.save(&buffer, "ppm");
    }

    return byteArray;
}

QImage byteArrayToImage(const QByteArray& byteArray) {
    return QImage::fromData(byteArray, "ppm");
}

QVariant bitArrayToVariant(const QBitArray& bitArray) {
    QVariantList variantList;
    for(int i = 0; i < bitArray.size(); ++i) {
        variantList.append(bitArray.at(i));
    }

    return variantList;
}

QVariant byteArrayToVariant(const QByteArray& byteArray) {
    return QString::fromLatin1(byteArray.toBase64());
}

QVariant colorToVariant(const QColor& color) {
    return color.isValid() ? color.name(QColor::HexArgb) : QVariant();
}

QVariant dateToVariant(const QDate& date) {
    return date.toString(Qt::DateFormat::ISODate);
}

QVariant dateTimeToVariant(const QDateTime& dateTime) {
#if QT_VERSION < QT_VERSION_CHECK(5, 8, 0)
    const int msec = dateTime.time().msec();
    const QString isoDate = dateTime.toString(Qt::DateFormat::ISODate);
    const QString isoDateWithMs = QStringLiteral("%1.%2").arg(isoDate).arg(msec, 3, 10, QLatin1Char('0'));

    return dateTime.isNull() ? QString() : isoDateWithMs;
#else
    return dateTime.toString(Qt::DateFormat::ISODateWithMs);
#endif
}

QVariant fontToVariant(const QFont& font) {
    return font.toString();
}

QVariant imageToVariant(const QImage& image) {
    return QString::fromLatin1(imageToByteArray(image).toBase64());
}

QVariant jsonArrayToVariant(const QJsonArray& jsonArray) {
    return jsonArray.toVariantList();
};

QVariant jsonObjectToVariant(const QJsonObject& jsonObject) {
    return jsonObject.toVariantMap();
};

QVariant jsonValueToVariant(const QJsonValue& jsonValue) {
    return jsonValue.toVariant();
};

QVariant lineToVariant(const QLine& line) {
    return QVariantList{line.x1(), line.y1(),
                        line.x2(), line.y2()};
}

QVariant lineFToVariant(const QLineF& line) {
    return QVariantList{line.x1(), line.y1(),
                        line.x2(), line.y2()};
}

QVariant localeToVariant(const QLocale& locale) {
    return locale.bcp47Name();
}

QVariant matrix4x4ToVariant(const QMatrix4x4& matrix) {
    return QVariantList{matrix(0, 0), matrix(0, 1), matrix(0, 2), matrix(0, 3),
                        matrix(1, 0), matrix(1, 1), matrix(1, 2), matrix(1, 3),
                        matrix(2, 0), matrix(2, 1), matrix(2, 2), matrix(2, 3),
                        matrix(3, 0), matrix(3, 1), matrix(3, 2), matrix(3, 3)};
}

QVariant pointToVariant(const QPoint& point) {
    return QVariantList{point.x(), point.y()};
}

QVariant pointFToVariant(const QPointF& point) {
    return QVariantList{point.x(), point.y()};
}

QVariant quaternionToVariant(const QQuaternion& quaternion) {
    return QVariantList{quaternion.scalar(), quaternion.x(), quaternion.y(), quaternion.z()};
}

QVariant rectToVariant(const QRect& rect) {
    return QVariantList{rect.x(), rect.y(), rect.width(), rect.height()};
}

QVariant rectFToVariant(const QRectF& rect) {
    return QVariantList{rect.x(), rect.y(), rect.width(), rect.height()};
}

QVariant sizeToVariant(const QSize& size) {
    return QVariantList{size.width(), size.height()};
}

QVariant sizeFToVariant(const QSizeF& size) {
    return QVariantList{size.width(), size.height()};
}

QVariant stringListToVariant(const QStringList& stringList) {
    return stringList;
}

QVariant timeToVariant(const QTime& time) {
#if QT_VERSION < QT_VERSION_CHECK(5, 8, 0)
    const int msec = time.msec();
    const QString isoDate = time.toString(Qt::DateFormat::ISODate);
    const QString isoDateWithMs = QStringLiteral("%1.%2").arg(isoDate).arg(msec, 3, 10, QLatin1Char('0'));

    return time.isNull() ? QString() : isoDateWithMs;
#else
    return time.toString(Qt::DateFormat::ISODateWithMs);
#endif
}

QVariant transformToVariant(const QTransform& transform) {
    return QVariantList{transform.m11(), transform.m12(), transform.m13(),
                        transform.m21(), transform.m22(), transform.m23(),
                        transform.m31(), transform.m32(), transform.m33()};
}

QVariant urlToVariant(const QUrl& url) {
    return url.url();
}

QVariant uuidToVariant(const QUuid& uuid) {
    return uuid.toString();
}

QVariant variantToQVariant(const QVariant& variant) {
    return QVariantMap{{QLatin1String("name"), QString::fromLatin1(variant.typeName())},
                       {QLatin1String("value"), toVariant(variant.value<QVariant>())}};
}

QVariant vector2DToVariant(const QVector2D& vector) {
    return QVariantList{vector.x(), vector.y()};
}

QVariant vector3DToVariant(const QVector3D& vector) {
    return QVariantList{vector.x(), vector.y(), vector.z()};
}

QVariant vector4DToVariant(const QVector4D& vector) {
    return QVariantList{vector.x(), vector.y(), vector.z(), vector.w()};
}

QVariant defaultToVariant(const QVariant& variant) {
    const QMetaType metaType(variant.userType());

    QVariant value;
    if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
        value = Private::toVariant(variant.value<QObject*>());
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
        value = Private::toVariant(variant.value<void*>(), *metaType.metaObject());
    }
#endif
    else if(variant.userType() >= QMetaType::User) {
        if(variant.canConvert<QVariantMap>()) {
            value = variant.toMap();
        }
        else if(variant.canConvert<QVariantList>()) {
            value = variant.toList();
        }
        else {
            value = variant;
        }
    }
    else {
        value = variant;

        if(variant.userType() == QMetaType::Double) {
            if(qIsNaN(value.toDouble())) {
                value.setValue<double>(0);
            }
        }
        else if(variant.userType() == QMetaType::Float) {
            if(qIsNaN(value.toFloat())) {
                value.setValue<float>(0);
            }
        }
    }

    return value;
}

QBitArray variantToBitArray(const QVariant& variant) {
    QBitArray bitArray;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        bitArray.resize(variantList.size());

        int i = 0;
        for(const QVariant& entry : variantList) {
            bitArray.setBit(i, entry.toBool());
            i++;
        }
    }

    return bitArray;
}

QByteArray variantToByteArray(const QVariant& variant) {
    if(variant.isNull()) {
        return QByteArray();
    }
    else {
        return QByteArray::fromBase64(variant.toString().toLatin1());
    }
}

QColor variantToColor(const QVariant& variant) {
    QColor color;
    if(!variant.isNull()) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        color = QColor::fromString(variant.toString());
#else
        color.setNamedColor(variant.toString());
#endif
    }

    return color;
}

QDate variantToDate(const QVariant& variant) {
    QDate date;
    if(!variant.isNull()) {
        date = QDate::fromString(variant.toString(), Qt::DateFormat::ISODate);
    }

    return date;
}

QDateTime variantToDateTime(const QVariant& variant) {
    QDateTime dateTime;
    if(!variant.isNull()) {
#if QT_VERSION < QT_VERSION_CHECK(5, 8, 0)
        dateTime = QDateTime::fromString(variant.toString(), Qt::DateFormat::ISODate);
#else
        dateTime = QDateTime::fromString(variant.toString(), Qt::DateFormat::ISODateWithMs);
#endif
    }

    return dateTime;
}

QFont variantToFont(const QVariant& variant) {
    QFont font;
    if(!variant.isNull()) {
        font.fromString(variant.toString());
    }

    return font;
}

QImage variantToImage(const QVariant& variant) {
    if(variant.isNull()) {
        return QImage();
    }
    else {
        return byteArrayToImage(QByteArray::fromBase64(variant.toString().toLatin1()));
    }

}

QJsonArray variantToJsonArray(const QVariant& variant) {
    return QJsonArray::fromVariantList(variant.toList());
}

QJsonObject variantToJsonObject(const QVariant& variant) {
    return QJsonObject::fromVariantMap(variant.toMap());
}

QJsonValue variantToJsonValue(const QVariant& variant) {
    return QJsonValue::fromVariant(variant);
}

QLine variantToLine(const QVariant& variant) {
    QLine line;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 4) {
            line.setLine(variantList.at(0).toInt(),
                         variantList.at(1).toInt(),
                         variantList.at(2).toInt(),
                         variantList.at(3).toInt());
        }
    }

    return line;
}

QLineF variantToLineF(const QVariant& variant) {
    QLineF line;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 4) {
            line.setLine(static_cast<qreal>(variantList.at(0).toDouble()),
                         static_cast<qreal>(variantList.at(1).toDouble()),
                         static_cast<qreal>(variantList.at(2).toDouble()),
                         static_cast<qreal>(variantList.at(3).toDouble()));
        }
    }

    return line;
}

QLocale variantToLocale(const QVariant& variant) {
    QLocale locale;
    if(!variant.isNull()) {
        locale = QLocale(variant.toString());
    }

    return locale;
}

QMatrix4x4 variantToMatrix4x4(const QVariant& variant) {
    QMatrix4x4 matrix;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 16) {
            matrix = QMatrix4x4(static_cast<float>(variantList.at(0).toDouble()),
                                static_cast<float>(variantList.at(1).toDouble()),
                                static_cast<float>(variantList.at(2).toDouble()),
                                static_cast<float>(variantList.at(3).toDouble()),
                                static_cast<float>(variantList.at(4).toDouble()),
                                static_cast<float>(variantList.at(5).toDouble()),
                                static_cast<float>(variantList.at(6).toDouble()),
                                static_cast<float>(variantList.at(7).toDouble()),
                                static_cast<float>(variantList.at(8).toDouble()),
                                static_cast<float>(variantList.at(9).toDouble()),
                                static_cast<float>(variantList.at(10).toDouble()),
                                static_cast<float>(variantList.at(11).toDouble()),
                                static_cast<float>(variantList.at(12).toDouble()),
                                static_cast<float>(variantList.at(13).toDouble()),
                                static_cast<float>(variantList.at(14).toDouble()),
                                static_cast<float>(variantList.at(15).toDouble()));
        }
    }

    return matrix;
}

QPoint variantToPoint(const QVariant& variant) {
    QPoint point;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 2) {
            point.setX(variantList.at(0).toInt());
            point.setY(variantList.at(1).toInt());
        }
    }

    return point;
}

QPointF variantToPointF(const QVariant& variant) {
    QPointF point;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 2) {
            point.setX(static_cast<qreal>(variantList.at(0).toDouble()));
            point.setY(static_cast<qreal>(variantList.at(1).toDouble()));
        }
    }

    return point;
}

QQuaternion variantToQuaternion(const QVariant& variant) {
    QQuaternion quaternion;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 4) {
            quaternion.setScalar(static_cast<float>(variantList.at(0).toDouble()));
            quaternion.setX(static_cast<float>(variantList.at(1).toDouble()));
            quaternion.setY(static_cast<float>(variantList.at(2).toDouble()));
            quaternion.setZ(static_cast<float>(variantList.at(3).toDouble()));
        }
    }

    return quaternion;
}

QRect variantToRect(const QVariant& variant) {
    QRect rect;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 4) {
            rect.setX(variantList.at(0).toInt());
            rect.setY(variantList.at(1).toInt());
            rect.setWidth(variantList.at(2).toInt());
            rect.setHeight(variantList.at(3).toInt());
        }
    }

    return rect;
}

QRectF variantToRectF(const QVariant& variant) {
    QRectF rect;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 4) {
            rect.setX(static_cast<qreal>(variantList.at(0).toDouble()));
            rect.setY(static_cast<qreal>(variantList.at(1).toDouble()));
            rect.setWidth(static_cast<qreal>(variantList.at(2).toDouble()));
            rect.setHeight(static_cast<qreal>(variantList.at(3).toDouble()));
        }
    }

    return rect;
}

QSize variantToSize(const QVariant& variant) {
    QSize size;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 2) {
            size.setWidth(variantList.at(0).toInt());
            size.setHeight(variantList.at(1).toInt());
        }
    }

    return size;
}

QSizeF variantToSizeF(const QVariant& variant) {
    QSizeF size;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 2) {
            size.setWidth(static_cast<qreal>(variantList.at(0).toDouble()));
            size.setHeight(static_cast<qreal>(variantList.at(1).toDouble()));
        }
    }

    return size;
}

QStringList variantToStringList(const QVariant& variant) {
    QStringList stringList;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        stringList.reserve(variantList.size());

        for(const QVariant& entry : variantList) {
            stringList.append(entry.toString());
        }
    }

    return stringList;
}

QTime variantToTime(const QVariant& variant) {
    QTime time;
    if(!variant.isNull()) {
#if QT_VERSION < QT_VERSION_CHECK(5, 8, 0)
        time = QTime::fromString(variant.toString(), Qt::DateFormat::ISODate);
#else
        time = QTime::fromString(variant.toString(), Qt::DateFormat::ISODateWithMs);
#endif
    }

    return time;
}

QTransform variantToTransform(const QVariant& variant) {
    QTransform transform;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 9) {
            transform.setMatrix(static_cast<qreal>(variantList.at(0).toDouble()),
                                static_cast<qreal>(variantList.at(1).toDouble()),
                                static_cast<qreal>(variantList.at(2).toDouble()),
                                static_cast<qreal>(variantList.at(3).toDouble()),
                                static_cast<qreal>(variantList.at(4).toDouble()),
                                static_cast<qreal>(variantList.at(5).toDouble()),
                                static_cast<qreal>(variantList.at(6).toDouble()),
                                static_cast<qreal>(variantList.at(7).toDouble()),
                                static_cast<qreal>(variantList.at(8).toDouble()));
        }
    }

    return transform;
}

QUrl variantToUrl(const QVariant& variant) {
    QUrl url;
    if(!variant.isNull()) {
        url.setUrl(variant.toString());
    }

    return url;
}

QUuid variantToUuid(const QVariant& variant) {
    QUuid uuid;
    if(!variant.isNull()) {
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
        uuid = QUuid(variant.toString());
#else
        uuid = QUuid::fromString(variant.toString());
#endif
    }

    return uuid;
}

QVariant variantToVariant(const QVariant& variant, QObject* parent) {
    const QVariantMap variantMap = variant.toMap();
    const QString typeName = variantMap.value(QLatin1String("name")).toString();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    const int metaTypeId = QMetaType::fromName(typeName.toLatin1()).id();
#else
    const int metaTypeId = QMetaType::type(typeName.toLatin1());
#endif

    return (metaTypeId == QMetaType::UnknownType) ? QVariant() : Private::fromVariant(variantMap.value(QLatin1String("value")), metaTypeId, parent);
}

QVector2D variantToVector2D(const QVariant& variant) {
    QVector2D vector;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 2) {
            vector.setX(static_cast<float>(variantList.at(0).toDouble()));
            vector.setY(static_cast<float>(variantList.at(1).toDouble()));
        }
    }

    return vector;
}

QVector3D variantToVector3D(const QVariant& variant) {
    QVector3D vector;
    if(!variant.isNull()) {
        const QVariantList variantList = variant.toList();
        if(variantList.count() == 3) {
            vector.setX(static_cast<float>(variantList.at(0).toDouble()));
            vector.setY(static_cast<float>(variantList.at(1).toDouble()));
            vector.setZ(static_cast<float>(variantList.at(2).toDouble()));
        }
    }

    return vector;
}

QVector4D variantToVector4D(const QVariant& variant) {
    QVector4D vector;
    if(!variant.isNull()) {
        const QVariantList variantlist = variant.toList();
        if(variantlist.count() == 4) {
            vector.setX(static_cast<float>(variantlist.at(0).toDouble()));
            vector.setY(static_cast<float>(variantlist.at(1).toDouble()));
            vector.setZ(static_cast<float>(variantlist.at(2).toDouble()));
            vector.setW(static_cast<float>(variantlist.at(3).toDouble()));
        }
    }

    return vector;
}

QVariant variantToDefault(const QVariant& variant, int metaTypeId, QObject* parent) {
    QVariant value;

    const QMetaType metaType(metaTypeId);
    if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
        value = Private::fromVariant(nullptr, variant, metaTypeId, parent);
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
        value = Private::fromVariant(nullptr, metaTypeId, variant);
    }
#endif
    else if(metaTypeId == QMetaType::UnknownType) {
        value = variant;
    }
    else {
        // Try to use supported QVariant conversions
        value = variant;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        if(value.canConvert(metaType)) {
            value.convert(metaType);
        }
#else
        if(value.canConvert(metaTypeId)) {
            value.convert(metaTypeId);
        }
#endif
        else {
            value.clear();
            qCWarning(category) << Q_FUNC_INFO << "Cannot convert value" << variant << "to type" << metaTypeId;
        }
    }

    return value;
}

void writeGadgetProperty(void* gadget, const QMetaObject& metaObject, const QMetaProperty& metaProperty, const QVariant& variant) {
    QVariant value;

    // Try custom conversion
    const int convertIndex = metaObject.indexOfMethod("xylitolFromVariant(QMetaProperty,QVariant)");
    if(convertIndex != -1) {
        metaObject.method(convertIndex).invokeOnGadget(gadget, Q_RETURN_ARG(QVariant, value), Q_ARG(QMetaProperty, metaProperty), Q_ARG(QVariant, variant));
    }

    if(!value.isValid()) {
        // Try default conversion
        if(Private::canConvertToByteArray(variant)) {
            value = variant;;
        }
        else {
            value = fromVariant(variant, metaProperty.userType());
        }
    }

    // Try default write
    if(metaProperty.isWritable()) {
        metaProperty.writeOnGadget(gadget, value);
    }
    else {
        // Try custom write
        const int methodIndex = metaObject.indexOfMethod("xylitolWrite(QMetaProperty,QVariant)");
        if(methodIndex != -1) {
            metaObject.method(methodIndex).invokeOnGadget(gadget, Q_ARG(QMetaProperty, metaProperty), Q_ARG(QVariant, value));
        }
        else {
            qCWarning(category) << "Property" << metaProperty.name() << "of" << metaObject.className() << "is not writable";
        }
    }
}

} // namespace

bool canConvertToByteArray(const QVariant& variant) {
    switch(variant.userType()) {
    case QMetaType::QByteArray:
    case QMetaType::QImage:
        return true;
    default:
        return false;
    }
}

QByteArray toByteArray(const QVariant& variant) {
    switch(variant.userType()) {
    case QMetaType::QByteArray:
        return variant.value<QByteArray>();
    case QMetaType::QImage:
        return imageToByteArray(variant.value<QImage>());
    default:
        return QByteArray();
    }
}

QVariant fromByteArray(const QByteArray& byteArray, int metaTypeId) {
    switch(metaTypeId) {
    case QMetaType::QByteArray:
        return byteArray;
    case QMetaType::QImage:
        return byteArrayToImage(byteArray);
    default:
        return QVariant();
    }
}

QVariant toVariant(const QVariant& variant) {
    switch(variant.userType()) {
    case QMetaType::QBitArray:
        return bitArrayToVariant(variant.value<QBitArray>());
    case QMetaType::QByteArray:
        return byteArrayToVariant(variant.value<QByteArray>());
    case QMetaType::QColor:
        return colorToVariant(variant.value<QColor>());
    case QMetaType::QDate:
        return dateToVariant(variant.value<QDate>());
    case QMetaType::QDateTime:
        return dateTimeToVariant(variant.value<QDateTime>());
    case QMetaType::QFont:
        return fontToVariant(variant.value<QFont>());
    case QMetaType::QImage:
        return imageToVariant(variant.value<QImage>());
    case QMetaType::QJsonArray:
        return jsonArrayToVariant(variant.value<QJsonArray>());
    case QMetaType::QJsonObject:
        return jsonObjectToVariant(variant.value<QJsonObject>());
    case QMetaType::QJsonValue:
        return jsonValueToVariant(variant.value<QJsonValue>());
    case QMetaType::QLine:
        return lineToVariant(variant.value<QLine>());
    case QMetaType::QLineF:
        return lineFToVariant(variant.value<QLineF>());
    case QMetaType::QLocale:
        return localeToVariant(variant.value<QLocale>());
    case QMetaType::QMatrix4x4:
        return matrix4x4ToVariant(variant.value<QMatrix4x4>());
    case QMetaType::QPoint:
        return pointToVariant(variant.value<QPoint>());
    case QMetaType::QPointF:
        return pointFToVariant(variant.value<QPointF>());
    case QMetaType::QQuaternion:
        return quaternionToVariant(variant.value<QQuaternion>());
    case QMetaType::QRect:
        return rectToVariant(variant.value<QRect>());
    case QMetaType::QRectF:
        return rectFToVariant(variant.value<QRectF>());
    case QMetaType::QSize:
        return sizeToVariant(variant.value<QSize>());
    case QMetaType::QSizeF:
        return sizeFToVariant(variant.value<QSizeF>());
    case QMetaType::QStringList:
        return stringListToVariant(variant.value<QStringList>());
    case QMetaType::QTime:
        return timeToVariant(variant.value<QTime>());
    case QMetaType::QTransform:
        return transformToVariant(variant.value<QTransform>());
    case QMetaType::QUrl:
        return urlToVariant(variant.value<QUrl>());
    case QMetaType::QUuid:
        return uuidToVariant(variant.value<QUuid>());
    case QMetaType::QVariant:
        return variantToQVariant(variant.value<QVariant>());
    case QMetaType::QVector2D:
        return vector2DToVariant(variant.value<QVector2D>());
    case QMetaType::QVector3D:
        return vector3DToVariant(variant.value<QVector3D>());
    case QMetaType::QVector4D:
        return vector4DToVariant(variant.value<QVector4D>());
    default:
        return defaultToVariant(variant);
    }
}

QVariant fromVariant(const QVariant& variant, int metaTypeId, QObject* parent) {
    switch(metaTypeId) {
    case QMetaType::QBitArray:
        return QVariant(variantToBitArray(variant));
    case QMetaType::QByteArray:
        return QVariant(variantToByteArray(variant));
    case QMetaType::QColor:
        return QVariant(variantToColor(variant));
    case QMetaType::QDate:
        return QVariant(variantToDate(variant));
    case QMetaType::QDateTime:
        return QVariant(variantToDateTime(variant));
    case QMetaType::QFont:
        return QVariant(variantToFont(variant));
    case QMetaType::QImage:
        return QVariant(variantToImage(variant));
    case QMetaType::QJsonArray:
        return QVariant(variantToJsonArray(variant));
    case QMetaType::QJsonObject:
        return QVariant(variantToJsonObject(variant));
    case QMetaType::QJsonValue:
        return QVariant(variantToJsonValue(variant));
    case QMetaType::QLine:
        return QVariant(variantToLine(variant));
    case QMetaType::QLineF:
        return QVariant(variantToLineF(variant));
    case QMetaType::QLocale:
        return QVariant(variantToLocale(variant));
    case QMetaType::QMatrix4x4:
        return QVariant(variantToMatrix4x4(variant));
    case QMetaType::QPoint:
        return QVariant(variantToPoint(variant));
    case QMetaType::QPointF:
        return QVariant(variantToPointF(variant));
    case QMetaType::QQuaternion:
        return QVariant(variantToQuaternion(variant));
    case QMetaType::QRect:
        return QVariant(variantToRect(variant));
    case QMetaType::QRectF:
        return QVariant(variantToRectF(variant));
    case QMetaType::QSize:
        return QVariant(variantToSize(variant));
    case QMetaType::QSizeF:
        return QVariant(variantToSizeF(variant));
    case QMetaType::QStringList:
        return QVariant(variantToStringList(variant));
    case QMetaType::QTime:
        return QVariant(variantToTime(variant));
    case QMetaType::QTransform:
        return QVariant(variantToTransform(variant));
    case QMetaType::QUrl:
        return QVariant(variantToUrl(variant));
    case QMetaType::QUuid:
        return QVariant(variantToUuid(variant));
    case QMetaType::QVariant:
        return QVariant(variantToVariant(variant, parent));
    case QMetaType::QVector2D:
        return QVariant(variantToVector2D(variant));
    case QMetaType::QVector3D:
        return QVariant(variantToVector3D(variant));
    case QMetaType::QVector4D:
        return QVariant(variantToVector4D(variant));
    default:
        return variantToDefault(variant, metaTypeId, parent);
    }
}

QVariant toVariant(const QObject* object) {
    QVariant value;

    if(object) {
        const QMetaObject* metaObject = object->metaObject();

        QVariantMap objectMap;

        // Get correct property offset
        int propertyOffset = QObject::staticMetaObject.propertyCount();

        // Serialize model
        const AbstractListModel* model = qobject_cast<const AbstractListModel*>(object);
        if(model) {
            metaObject = model->metaObject();
            propertyOffset = AbstractListModel::staticMetaObject.propertyCount();

            // Serialize model data
            const QVariantList roles = toVariantList(model->roleNames().keys());
            objectMap[QLatin1String("items")] = model->xylitolToVariantList(0, model->rowCount() - 1, roles);
            objectMap[QLatin1String("roles")] = roles;
        }

        // Serialize properties
        QVariantMap propertyMap;

        const int propertyCount = metaObject->propertyCount();
        for(int i = propertyOffset; i < propertyCount; ++i) {
            const QMetaProperty metaProperty = metaObject->property(i);

            // Only stored properties are serialized
            if(metaProperty.isStored()) {
                const QString name = QString::fromLatin1(metaProperty.name());
                const QVariant readValue = metaProperty.read(object);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                const QVariant variant((metaProperty.userType() == QMetaType::QVariant) ? QVariant(metaProperty.metaType(), &readValue) : readValue);
#else
                const QVariant variant((metaProperty.userType() == QMetaType::QVariant) ? QVariant(metaProperty.userType(), &readValue) : readValue);
#endif

                const QMetaType metaType(metaProperty.userType());

                if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
                    propertyMap[name] = toVariant(variant.value<QObject*>());
                }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
                else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
                    propertyMap[name] = toVariant(variant.value<void*>(), *metaType.metaObject());
                }
#endif
                else {
                    propertyMap[name] = toVariant(variant);
                }
            }
        }

        objectMap[QLatin1String("properties")] = propertyMap;
        value = objectMap;
    }

    return value;
}

QVariant fromVariant(QObject* object, const QVariant& variant, int metaTypeId, QObject* parent) {
    if(!variant.isNull()) {
        if(!object) {
            const QMetaObject* metaObject = QMetaType(metaTypeId).metaObject();
            object = metaObject->newInstance(Q_ARG(QObject*, parent));
            if(!object) {
                object = metaObject->newInstance(Q_ARG(QVariant, variant), Q_ARG(QObject*, parent));
                if(!object) {
                    qCWarning(category) << "Unable to create instance of" << metaObject->className();
                }
            }
        }

        if(object) {
            const QMetaObject* metaObject = object->metaObject();

            const QVariantMap objectMap = variant.toMap();
            const QVariantMap propertyMap = objectMap.value(QLatin1String("properties")).toMap();

            QVariantMap constantPropertyMap;
            QVariantMap pointerPropertyMap;

            // Write properties
            for(QVariantMap::ConstIterator i = propertyMap.constBegin(); i != propertyMap.constEnd(); ++i) {
                const QString propertyName = i.key();
                const QVariant propertyValue = i.value();

                const int index = metaObject->indexOfProperty(propertyName.toLatin1().constData());
                if(index >= 0) {
                    const QMetaProperty metaProperty = metaObject->property(index);

                    // Only stored properties are written
                    if(metaProperty.isStored()) {
                        const QVariant value = metaProperty.read(object);
                        const QMetaType metaType(metaProperty.userType());

                        if(metaProperty.isConstant()) {
                            // Handle constant property later
                            constantPropertyMap[propertyName] = propertyValue;
                        }
                        else {
                            if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
                                // Destroy previous value & handle QObject* property later
                                delete value.value<QObject*>();
                                pointerPropertyMap[propertyName] = propertyValue;
                            }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
                            else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
                                // Destroy previous value & handle Gadget* property later
                                metaType.destroy(value.value<void*>());
                                pointerPropertyMap[propertyName] = propertyValue;
                            }
#endif
                            else {
                                writeObjectProperty(*object, metaProperty, propertyValue);
                            }
                        }
                    }
                }
                else {
                    qCWarning(category) << "Property not found:" << propertyName;
                }
            }

            // Write pointer properties
            for(QVariantMap::ConstIterator i = pointerPropertyMap.constBegin(); i != pointerPropertyMap.constEnd(); ++i) {
                const QString propertyName = i.key();
                const QVariant propertyValue = i.value();

                const int index = metaObject->indexOfProperty(propertyName.toLatin1().constData());
                if(index >= 0) {
                    const QMetaProperty metaProperty = metaObject->property(index);

                    writeObjectProperty(*object, metaProperty, propertyValue);
                }
            }

            // Write structure (constant pointer properties)
            for(QVariantMap::ConstIterator i = constantPropertyMap.constBegin(); i != constantPropertyMap.constEnd(); ++i) {
                const QString propertyName = i.key();
                const QVariant propertyValue = i.value();

                const int index = metaObject->indexOfProperty(propertyName.toLatin1().constData());
                if(index >= 0) {
                    const QMetaProperty metaProperty = metaObject->property(index);
                    const QVariant value = metaProperty.read(object);
                    const QMetaType metaType(metaProperty.userType());

                    // If constant property is pointer type, write to the object
                    if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
                        QObject* objectValue = value.value<QObject*>();
                        if(objectValue) {
                            Private::fromVariant(objectValue, propertyValue);
                        }
                    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
                    else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
                        void* gadgetValue = value.value<void*>();
                        if(gadgetValue) {
                            Private::fromVariant(gadgetValue, metaType.id(), propertyValue);
                        }
                    }
#endif
                }
            }

            // Write model data
            AbstractListModel* model = qobject_cast<AbstractListModel*>(object);
            if(model) {
                const QVariantList items = objectMap.value(QLatin1String("items")).toList();
                const QVariantList roles = objectMap.value(QLatin1String("roles")).toList();

                model->xylitolFromVariantList(items, roles);
            }
        }
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return QVariant(QMetaType(metaTypeId), &object);
#else
    return QVariant(metaTypeId, &object);
#endif
}

QVariant toVariant(const void* gadget, const QMetaObject& metaObject) {
    QVariant value;

    if(gadget) {
        QVariantMap objectMap;

        int propertyOffset = metaObject.propertyOffset();

        // Serialize properties
        QVariantMap propertyMap;

        const int propertyCount = metaObject.propertyCount();
        for(int i = propertyOffset; i < propertyCount; ++i) {
            const QMetaProperty metaProperty = metaObject.property(i);

            // Only stored properties are serialized
            if(metaProperty.isStored()) {
                const QString name = QString::fromLatin1(metaProperty.name());
                const QVariant readValue = metaProperty.readOnGadget(gadget);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                const QVariant propertyValue((metaProperty.userType() == QMetaType::QVariant) ? QVariant(metaProperty.metaType(), &readValue) : readValue);
#else
                const QVariant propertyValue((metaProperty.userType() == QMetaType::QVariant) ? QVariant(metaProperty.userType(), &readValue) : readValue);
#endif

                propertyMap[name] = toVariant(propertyValue);
            }
        }

        objectMap[QLatin1String("properties")] = propertyMap;
        value = objectMap;
    }

    return value;
}

QVariant fromVariant(void* gadget, int metaTypeId, const QVariant& variant) {
    const QMetaObject* metaObject = QMetaType(metaTypeId).metaObject();

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    const int metaObjectTypeId = metaObject->metaType().id();
#else
    const int metaObjectTypeId = QMetaType::type(metaObject->className());
#endif

    const bool pointer = (metaTypeId != metaObjectTypeId);

    if(!variant.isNull()) {
        if(!gadget) {
            gadget = QMetaType(metaObjectTypeId).create();
            if(!gadget) {
                qCWarning(category) << "Unable to create instance of" << metaObject->className();
            }
        }

        if(gadget) {
            const QVariantMap objectMap = variant.toMap();
            const QVariantMap propertyMap = objectMap.value(QLatin1String("properties")).toMap();

            // Initialize properties
            for(QVariantMap::ConstIterator i = propertyMap.constBegin(); i != propertyMap.constEnd(); ++i) {
                const QString propertyName = i.key();
                const QVariant propertyValue = i.value();

                const int index = metaObject->indexOfProperty(propertyName.toLatin1().constData());
                if(index >= 0) {
                    const QMetaProperty metaProperty = metaObject->property(index);

                    // Only stored properties are initialized
                    if(metaProperty.isStored()) {
                        if(metaProperty.isConstant()) {
                            // Do nothing with gadget constant properties
                        }
                        else {
                            writeGadgetProperty(gadget, *metaObject, metaProperty, propertyValue);
                        }
                    }
                }
                else {
                    qCWarning(category) << "Property" << propertyName << "not found!";
                }
            }
        }
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    if(pointer) {
        return QVariant(QMetaType(metaTypeId), &gadget);
    }
    else {
        return QVariant(QMetaType(metaTypeId), gadget);
    }
#else
    if(pointer) {
        return QVariant(metaTypeId, &gadget);
    }
    else {
        return QVariant(metaTypeId, gadget);
    }
#endif
}

void writeObjectProperty(QObject& object, const QMetaProperty& metaProperty, const QVariant& variant) {
    const QMetaObject* metaObject = object.metaObject();

    QVariant value;

    // Try custom conversion
    const int convertIndex = metaObject->indexOfMethod("xylitolFromVariant(QMetaProperty,QVariant)");
    if(convertIndex != -1) {
        metaObject->method(convertIndex).invoke(&object, Q_RETURN_ARG(QVariant, value), Q_ARG(QMetaProperty, metaProperty), Q_ARG(QVariant, variant));
    }

    if(!value.isValid()) {
        // Try default conversion
        if(Private::canConvertToByteArray(variant)) {
            value = variant;;
        }
        else {
            value = fromVariant(variant, metaProperty.userType(), &object);
        }
    }

    // Try default write
    if(metaProperty.isWritable()) {
        metaProperty.write(&object, value);
    }
    else {
        // Try custom write
        const int writeIndex = metaObject->indexOfMethod("xylitolWrite(QMetaProperty,QVariant)");
        if(writeIndex != -1) {
            metaObject->method(writeIndex).invoke(&object, Q_ARG(QMetaProperty, metaProperty), Q_ARG(QVariant, value));
        }
        else {
            qCWarning(category) << "Property" << metaProperty.name() << "of" << metaObject->className() << "is not writable";
        }
    }
}

} // namespace Private
} // namespace Xylitol
