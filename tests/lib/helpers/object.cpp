#include "object.h"

#include <Xylitol/util.h>

#include <QtTest/QtTest>

Object::Object(QObject* parent)
    : QObject(parent) {}

void Object::compare(const Object& expected) const {
    QCOMPARE(bitArray(), expected.bitArray());
    QCOMPARE(byteArray(), expected.byteArray());
    QCOMPARE(color(), expected.color());
    QCOMPARE(date(), expected.date());
    QCOMPARE(dateTime(), expected.dateTime());
    QCOMPARE(image(), expected.image());
    QCOMPARE(jsonArray(), expected.jsonArray());
    QCOMPARE(jsonObject(), expected.jsonObject());
    QCOMPARE(jsonValue(), expected.jsonValue());
    QCOMPARE(line(), expected.line());
    QCOMPARE(lineF(), expected.lineF());
    QCOMPARE(locale().bcp47Name(), expected.locale().bcp47Name());
    QCOMPARE(matrix4x4(), expected.matrix4x4());
    QCOMPARE(point(), expected.point());
    QCOMPARE(pointF(), expected.pointF());
    QCOMPARE(quaternion(), expected.quaternion());
    QCOMPARE(rect(), expected.rect());
    QCOMPARE(rectF(), expected.rectF());
    QCOMPARE(size(), expected.size());
    QCOMPARE(sizeF(), expected.sizeF());
    QCOMPARE(time(), expected.time());
    QCOMPARE(transform(), expected.transform());
    QCOMPARE(url(), expected.url());
    if(variant().canConvert<Object*>() &&
        variant().value<Object*>() &&
        expected.variant().value<Object*>()) {
        variant().value<Object*>()->compare(*expected.variant().value<Object*>());
    }
    else {
        QCOMPARE(variant(), expected.variant());
    }
    QCOMPARE(vector2D(), expected.vector2D());
    QCOMPARE(vector3D(), expected.vector3D());
    QCOMPARE(vector4D(), expected.vector4D());

    QCOMPARE(boolValue(), expected.boolValue());
    QCOMPARE(doubleValue(), expected.doubleValue());
    QCOMPARE(intValue(), expected.intValue());
    QCOMPARE(string(), expected.string());
    QCOMPARE(stringList(), expected.stringList());
    QCOMPARE(variantList(), expected.variantList());
    QCOMPARE(variantHash(), expected.variantHash());
    QCOMPARE(variantMap(), expected.variantMap());
    QCOMPARE(intList(), expected.intList());
    QCOMPARE(enumeration(), expected.enumeration());
    QCOMPARE(flags(), expected.flags());
}

const QBitArray& Object::bitArray() const {
    return mBitArray;
}

void Object::setBitArray(const QBitArray& bitArray) {
    if(bitArray != mBitArray) {
        mBitArray = bitArray;
        emit bitArrayChanged(bitArray);
    }
}

const QByteArray& Object::byteArray() const {
    return mByteArray;
}

void Object::setByteArray(const QByteArray& byteArray) {
    if(byteArray != mByteArray) {
        mByteArray = byteArray;
        emit byteArrayChanged(byteArray);
    }
}

const QColor& Object::color() const {
    return mColor;
}

void Object::setColor(const QColor& color) {
    if(color != mColor) {
        mColor = color;
        emit colorChanged(color);
    }
}

const QDate& Object::date() const {
    return mDate;
}

void Object::setDate(const QDate& date) {
    if(date != mDate) {
        mDate = date;
        emit dateChanged(date);
    }
}

const QDateTime& Object::dateTime() const {
    return mDateTime;
}

void Object::setDateTime(const QDateTime& dateTime) {
    if(dateTime != mDateTime) {
        mDateTime = dateTime;
        emit dateTimeChanged(dateTime);
    }
}

const QImage& Object::image() const {
    return mImage;
}

void Object::setImage(const QImage& image) {
    if(image != mImage) {
        mImage = image;
        emit imageChanged(image);
    }
}

const QJsonArray& Object::jsonArray() const {
    return mJsonArray;
}

void Object::setJsonArray(const QJsonArray& array) {
    if(array != mJsonArray) {
        mJsonArray = array;
        emit jsonArrayChanged(array);
    }
}

const QJsonObject& Object::jsonObject() const {
    return mJsonObject;
}

void Object::setJsonObject(const QJsonObject& array) {
    if(array != mJsonObject) {
        mJsonObject = array;
        emit jsonObjectChanged(array);
    }
}

const QJsonValue& Object::jsonValue() const {
    return mJsonValue;
}

void Object::setJsonValue(const QJsonValue& value) {
    if(value != mJsonValue) {
        mJsonValue = value;
        emit jsonValueChanged(value);
    }
}

const QLine& Object::line() const {
    return mLine;
}

void Object::setLine(const QLine& line) {
    if(line != mLine) {
        mLine = line;
        emit lineChanged(line);
    }
}

const QLineF& Object::lineF() const {
    return mLineF;
}

void Object::setLineF(const QLineF& lineF) {
    if(lineF != mLineF) {
        mLineF = lineF;
        emit lineFChanged(lineF);
    }
}

const QLocale& Object::locale() const {
    return mLocale;
}

void Object::setLocale(const QLocale& locale) {
    if(locale != mLocale) {
        mLocale = locale;
        emit localeChanged(locale);
    }
}

const QMatrix4x4& Object::matrix4x4() const {
    return mMatrix4x4;
}

void Object::setMatrix4x4(const QMatrix4x4& matrix4x4) {
    if(matrix4x4 != mMatrix4x4) {
        mMatrix4x4 = matrix4x4;
        emit matrix4x4Changed(matrix4x4);
    }
}

const QPoint& Object::point() const {
    return mPoint;
}

void Object::setPoint(const QPoint& point) {
    if(point != mPoint) {
        mPoint = point;
        emit pointChanged(point);
    }
}

const QPointF& Object::pointF() const {
    return mPointF;
}

void Object::setPointF(const QPointF& pointF) {
    if(pointF != mPointF) {
        mPointF = pointF;
        emit pointFChanged(pointF);
    }
}

const QQuaternion& Object::quaternion() const {
    return mQuaternion;
}

void Object::setQuaternion(const QQuaternion& quaternion) {
    if(quaternion != mQuaternion) {
        mQuaternion = quaternion;
        emit quaternionChanged(quaternion);
    }
}

const QRect& Object::rect() const {
    return mRect;
}

void Object::setRect(const QRect& rect) {
    if(rect != mRect) {
        mRect = rect;
        emit rectChanged(rect);
    }
}

const QRectF& Object::rectF() const {
    return mRectF;
}

void Object::setRectF(const QRectF& rectF) {
    if(rectF != mRectF) {
        mRectF = rectF;
        emit rectFChanged(rectF);
    }
}

const QSize& Object::size() const {
    return mSize;
}

void Object::setSize(const QSize& size) {
    if(size != mSize) {
        mSize = size;
        emit sizeChanged(size);
    }
}

const QSizeF& Object::sizeF() const {
    return mSizeF;
}

void Object::setSizeF(const QSizeF& sizeF) {
    if(sizeF != mSizeF) {
        mSizeF = sizeF;
        emit sizeFChanged(sizeF);
    }
}

const QTime& Object::time() const {
    return mTime;
}

void Object::setTime(const QTime& time) {
    if(time != mTime) {
        mTime = time;
        emit timeChanged(time);
    }
}

const QTransform& Object::transform() const {
    return mTransform;
}

void Object::setTransform(const QTransform& transform) {
    if(transform != mTransform) {
        mTransform = transform;
        emit transformChanged(transform);
    }
}

const QUrl& Object::url() const {
    return mUrl;
}

void Object::setUrl(const QUrl& url) {
    if(url != mUrl) {
        mUrl = url;
        emit urlChanged(url);
    }
}

const QUuid& Object::uuid() const {
    return mUuid;
}

void Object::setUuid(const QUuid& uuid) {
    if(uuid != mUuid) {
        mUuid = uuid;
        emit uuidChanged(uuid);
    }
}

const QVariant& Object::variant() const {
    return mVariant;
}

void Object::setVariant(const QVariant& variant) {
    if(variant != mVariant) {
        mVariant = variant;
        emit variantChanged(variant);
    }
}

const QVector2D& Object::vector2D() const {
    return mVector2D;
}

void Object::setVector2D(const QVector2D& vector2D) {
    if(vector2D != mVector2D) {
        mVector2D = vector2D;
        emit vector2DChanged(vector2D);
    }
}

const QVector3D& Object::vector3D() const {
    return mVector3D;
}

void Object::setVector3D(const QVector3D& vector3D) {
    if(vector3D != mVector3D) {
        mVector3D = vector3D;
        emit vector3DChanged(vector3D);
    }
}

const QVector4D& Object::vector4D() const {
    return mVector4D;
}

void Object::setVector4D(const QVector4D& vector4D) {
    if(vector4D != mVector4D) {
        mVector4D = vector4D;
        emit vector4DChanged(vector4D);
    }
}

bool Object::boolValue() const {
    return mBool;
}

void Object::setBoolValue(bool value) {
    if(value != mBool) {
        mBool = value;
        emit boolValueChanged(value);
    }
}

double Object::doubleValue() const {
    return mDouble;
}

void Object::setDoubleValue(double value) {
    if(value != mDouble) {
        mDouble = value;
        emit doubleValueChanged(value);
    }
}

int Object::intValue() const {
    return mInt;
}

void Object::setIntValue(int value) {
    if(value != mInt) {
        mInt = value;
        emit intValueChanged(value);
    }
}

const QString& Object::string() const {
    return mString;
}

void Object::setString(const QString& string) {
    if(string != mString) {
        mString = string;
        emit stringChanged(string);
    }
}

const QStringList& Object::stringList() const {
    return mStringList;
}

void Object::setStringList(const QStringList& stringList) {
    if(stringList != mStringList) {
        mStringList = stringList;
        emit stringListChanged(stringList);
    }
}

const QVariantList& Object::variantList() const {
    return mVariantList;
}

void Object::setVariantList(const QVariantList& variantList) {
    if(variantList != mVariantList) {
        mVariantList = variantList;
        emit variantListChanged(variantList);
    }
}

const QVariantHash& Object::variantHash() const {
    return mVariantHash;
}

void Object::setVariantHash(const QVariantHash& variantHash) {
    if(variantHash != mVariantHash) {
        mVariantHash = variantHash;
        emit variantHashChanged(variantHash);
    }
}

const QVariantMap& Object::variantMap() const {
    return mVariantMap;
}

void Object::setVariantMap(const QVariantMap& variantMap) {
    if(variantMap != mVariantMap) {
        mVariantMap = variantMap;
        emit variantMapChanged(variantMap);
    }
}

const QList<int>& Object::intList() const {
    return mIntList;
}

void Object::setIntList(const QList<int>& intList) {
    if(intList != mIntList) {
        mIntList = intList;
        emit intListChanged(intList);
    }
}

Object::Enum Object::enumeration() const {
    return mEnumeration;
}

void Object::setEnumeration(Enum enumeration) {
    if(enumeration != mEnumeration) {
        mEnumeration = enumeration;
        emit enumerationChanged(enumeration);
    }
}

const Object::Flags& Object::flags() const {
    return mFlags;
}

void Object::setFlags(const Flags& flags) {
    if(flags != mFlags) {
        mFlags = flags;
        emit flagsChanged(flags);
    }
}

Object* Object::child() const {
    return mChild;
}

void Object::setChild(Object* child) {
    if(child != mChild) {
        mChild = child;
        emit childChanged(child);
    }
}
