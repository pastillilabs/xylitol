#pragma once

#include <QBitArray>
#include <QDate>
#include <QDateTime>
#include <QImage>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QLine>
#include <QLineF>
#include <QLocale>
#include <QMatrix4x4>
#include <QPoint>
#include <QPointF>
#include <QQuaternion>
#include <QRect>
#include <QRectF>
#include <QSize>
#include <QSizeF>
#include <QTime>
#include <QTransform>
#include <QUrl>
#include <QUuid>
#include <QVariant>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include <QList>
#include <QString>
#include <QStringList>
#include <QVariantHash>
#include <QVariantList>
#include <QVariantMap>

/**
 * @brief The Object class
 */
class Object : public QObject {
    Q_OBJECT
    Q_PROPERTY(QBitArray bitArray READ bitArray WRITE setBitArray NOTIFY bitArrayChanged)
    Q_PROPERTY(QByteArray byteArray READ byteArray WRITE setByteArray NOTIFY byteArrayChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QJsonArray jsonArray READ jsonArray WRITE setJsonArray NOTIFY jsonArrayChanged)
    Q_PROPERTY(QJsonObject jsonObject READ jsonObject WRITE setJsonObject NOTIFY jsonObjectChanged)
    Q_PROPERTY(QJsonValue jsonValue READ jsonValue WRITE setJsonValue NOTIFY jsonValueChanged)
    Q_PROPERTY(QLine line READ line WRITE setLine NOTIFY lineChanged)
    Q_PROPERTY(QLineF lineF READ lineF WRITE setLineF NOTIFY lineFChanged)
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QMatrix4x4 matrix4x4 READ matrix4x4 WRITE setMatrix4x4 NOTIFY matrix4x4Changed)
    Q_PROPERTY(QPoint point READ point WRITE setPoint NOTIFY pointChanged)
    Q_PROPERTY(QPointF pointF READ pointF WRITE setPointF NOTIFY pointFChanged)
    Q_PROPERTY(QQuaternion quaternion READ quaternion WRITE setQuaternion NOTIFY quaternionChanged)
    Q_PROPERTY(QRect rect READ rect WRITE setRect NOTIFY rectChanged)
    Q_PROPERTY(QRectF rectF READ rectF WRITE setRectF NOTIFY rectFChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QSizeF sizeF READ sizeF WRITE setSizeF NOTIFY sizeFChanged)
    Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QTransform transform READ transform WRITE setTransform NOTIFY transformChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid NOTIFY uuidChanged)
    Q_PROPERTY(QVariant variant READ variant WRITE setVariant NOTIFY variantChanged)
    Q_PROPERTY(QVector2D vector2D READ vector2D WRITE setVector2D NOTIFY vector2DChanged)
    Q_PROPERTY(QVector3D vector3D READ vector3D WRITE setVector3D NOTIFY vector3DChanged)
    Q_PROPERTY(QVector4D vector4D READ vector4D WRITE setVector4D NOTIFY vector4DChanged)

    Q_PROPERTY(bool boolValue READ boolValue WRITE setBoolValue NOTIFY boolValueChanged)
    Q_PROPERTY(double doubleValue READ doubleValue WRITE setDoubleValue NOTIFY doubleValueChanged)
    Q_PROPERTY(int intValue READ intValue WRITE setIntValue NOTIFY intValueChanged)
    Q_PROPERTY(QString string READ string WRITE setString NOTIFY stringChanged)
    Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList NOTIFY stringListChanged)
    Q_PROPERTY(QVariantList variantList READ variantList WRITE setVariantList NOTIFY variantListChanged)
    Q_PROPERTY(QVariantHash variantHash READ variantHash WRITE setVariantHash NOTIFY variantHashChanged)
    Q_PROPERTY(QVariantMap variantMap READ variantMap WRITE setVariantMap NOTIFY variantMapChanged)
    Q_PROPERTY(QList<int> intList READ intList WRITE setIntList NOTIFY intListChanged)
    Q_PROPERTY(Object::Enum enumeration READ enumeration WRITE setEnumeration NOTIFY enumerationChanged)
    Q_PROPERTY(Object::Flags flags READ flags WRITE setFlags NOTIFY flagsChanged)

    Q_PROPERTY(Object* child READ child WRITE setChild NOTIFY childChanged)

public:
    enum class Enum {
        EnumA,
        EnumB,
        EnumC
    };
    Q_ENUM(Enum)

    enum Flag {
        FlagNone    = 0,
        FlagA       = 1 << 0,
        FlagB       = 1 << 1
    };
    Q_ENUM(Flag)
    Q_DECLARE_FLAGS(Flags, Flag)
    Q_FLAG(Flags)

public:
    Q_INVOKABLE explicit Object(QObject* parent = nullptr);

    void compare(const Object& expected) const;

    const QBitArray& bitArray() const;
    void setBitArray(const QBitArray& bitArray);

    const QByteArray& byteArray() const;
    void setByteArray(const QByteArray& byteArray);

    const QColor& color() const;
    void setColor(const QColor& color);

    const QDate& date() const;
    void setDate(const QDate& date);

    const QDateTime& dateTime() const;
    void setDateTime(const QDateTime& dateTime);

    const QImage& image() const;
    void setImage(const QImage& image);

    const QJsonArray& jsonArray() const;
    void setJsonArray(const QJsonArray& array);

    const QJsonObject& jsonObject() const;
    void setJsonObject(const QJsonObject& array);

    const QJsonValue& jsonValue() const;
    void setJsonValue(const QJsonValue& value);

    const QLine& line() const;
    void setLine(const QLine& line);

    const QLineF& lineF() const;
    void setLineF(const QLineF& lineF);

    const QLocale& locale() const;
    void setLocale(const QLocale& locale);

    const QMatrix4x4& matrix4x4() const;
    void setMatrix4x4(const QMatrix4x4& matrix4x4);

    const QPoint& point() const;
    void setPoint(const QPoint& point);

    const QPointF& pointF() const;
    void setPointF(const QPointF& pointF);

    const QQuaternion& quaternion() const;
    void setQuaternion(const QQuaternion& quaternion);

    const QRect& rect() const;
    void setRect(const QRect& rect);

    const QRectF& rectF() const;
    void setRectF(const QRectF& rectF);

    const QSize& size() const;
    void setSize(const QSize& size);

    const QSizeF& sizeF() const;
    void setSizeF(const QSizeF& sizeF);

    const QTime& time() const;
    void setTime(const QTime& time);

    const QTransform& transform() const;
    void setTransform(const QTransform& transform);

    const QUrl& url() const;
    void setUrl(const QUrl& url);

    const QUuid& uuid() const;
    void setUuid(const QUuid& uuid);

    const QVariant& variant() const;
    void setVariant(const QVariant& variant);

    const QVector2D& vector2D() const;
    void setVector2D(const QVector2D& vector2D);

    const QVector3D& vector3D() const;
    void setVector3D(const QVector3D& vector3D);

    const QVector4D& vector4D() const;
    void setVector4D(const QVector4D& vector4D);

    bool boolValue() const;
    void setBoolValue(bool value);

    double doubleValue() const;
    void setDoubleValue(double value);

    int intValue() const;
    void setIntValue(int value);

    const QString& string() const;
    void setString(const QString& string);

    const QStringList& stringList() const;
    void setStringList(const QStringList& stringList);

    const QVariantList& variantList() const;
    void setVariantList(const QVariantList& variantList);

    const QVariantHash& variantHash() const;
    void setVariantHash(const QVariantHash& variantHash);

    const QVariantMap& variantMap() const;
    void setVariantMap(const QVariantMap& variantMap);

    const QList<int>& intList() const;
    void setIntList(const QList<int>& intList);

    Enum enumeration() const;
    void setEnumeration(Enum enumeration);

    const Flags& flags() const;
    void setFlags(const Flags& flags);

    Object* child() const;
    void setChild(Object* child);

signals:
    void bitArrayChanged(const QBitArray& bitArray);
    void byteArrayChanged(const QByteArray& byteArray);
    void colorChanged(const QColor& color);
    void dateChanged(const QDate& date);
    void dateTimeChanged(const QDateTime& dateTime);
    void imageChanged(const QImage& image);
    void jsonArrayChanged(const QJsonArray& array);
    void jsonObjectChanged(const QJsonObject& array);
    void jsonValueChanged(const QJsonValue& value);
    void lineChanged(const QLine& line);
    void lineFChanged(const QLineF& lineF);
    void localeChanged(const QLocale& locale);
    void matrix4x4Changed(const QMatrix4x4& matrix4x4);
    void pointChanged(const QPoint& point);
    void pointFChanged(const QPointF& pointF);
    void quaternionChanged(const QQuaternion& quaternion);
    void rectChanged(const QRect& rect);
    void rectFChanged(const QRectF& rectF);
    void sizeChanged(const QSize& size);
    void sizeFChanged(const QSizeF& sizeF);
    void timeChanged(const QTime& time);
    void transformChanged(const QTransform& transform);
    void urlChanged(const QUrl& url);
    void uuidChanged(const QUuid& uuid);
    void variantChanged(const QVariant& variant);
    void vector2DChanged(const QVector2D& vector2D);
    void vector3DChanged(const QVector3D& vector3D);
    void vector4DChanged(const QVector4D& vector4D);

    void boolValueChanged(bool value);
    void doubleValueChanged(double value);
    void intValueChanged(int value);
    void stringChanged(const QString& string);
    void stringListChanged(const QStringList& stringList);
    void variantListChanged(const QVariantList& variantList);
    void variantHashChanged(const QVariantHash& variantHash);
    void variantMapChanged(const QVariantMap& variantMap);
    void intListChanged(const QList<int>& intList);
    void enumerationChanged(Object::Enum enumeration);
    void flagsChanged(Object::Flags flags);

    void childChanged(Object* child);

    // Non-property signals
    void testA();
    void testB(int a, const QString& b);
    void testC(Object::Enum e);
    void testD(const QVariant& variant);

private:
    QBitArray mBitArray;
    QByteArray mByteArray;
    QColor mColor;
    QDate mDate;
    QDateTime mDateTime;
    QImage mImage;
    QJsonArray mJsonArray;
    QJsonObject mJsonObject;
    QJsonValue mJsonValue;
    QLine mLine;
    QLineF mLineF;
    QLocale mLocale;
    QMatrix4x4 mMatrix4x4;
    QPoint mPoint;
    QPointF mPointF;
    QQuaternion mQuaternion;
    QRect mRect;
    QRectF mRectF;
    QSize mSize;
    QSizeF mSizeF;
    QTime mTime;
    QTransform mTransform;
    QUrl mUrl;
    QUuid mUuid;
    QVariant mVariant;
    QVector2D mVector2D;
    QVector3D mVector3D;
    QVector4D mVector4D;

    bool mBool{false};
    double mDouble{0.0};
    int mInt{0};
    QString mString;
    QStringList mStringList;
    QVariantList mVariantList;
    QVariantHash mVariantHash;
    QVariantMap mVariantMap;
    QList<int> mIntList;
    Enum mEnumeration{Enum::EnumA};
    Flags mFlags{Flag::FlagNone};

    Object* mChild{nullptr};
};

Q_DECLARE_METATYPE(Object*)
Q_DECLARE_OPERATORS_FOR_FLAGS(Object::Flags)
