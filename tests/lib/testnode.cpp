#include "testnode.h"
#include "helpers/abstractlistmodel.h"
#include "helpers/gadget.h"
#include "helpers/listmodel.h"
#include "helpers/object.h"
#include "helpers/rootobject.h"
#include "helpers/stringlistmodel.h"

#include <xylitol/templates.h>

// clazy:excludeall=non-pod-global-static

namespace {

QImage createTestImage() {
    QImage testImage(10, 10, QImage::Format_RGB32);
    testImage.fill(QColor(Qt::green));
    return testImage;
}

const QBitArray bitArray(4, true);
const QByteArray byteArray("A");
const QColor color(Qt::green);
const QDate date(QDate::currentDate());
const QDateTime dateTime(QDateTime::currentDateTime());
const QImage image(createTestImage());
const QJsonArray jsonArray{{QLatin1String("A")}};
const QJsonObject jsonObject{{QLatin1String("key"), QLatin1String("value")}};
const QJsonValue jsonValue{jsonObject};
const QLine line(1, 2, 3, 4);
const QLineF lineF(1.1, 2.2, 3.3, 4.4);
const QLocale locale(QLocale::Finnish, QLocale::Finland);
const QMatrix4x4 matrix4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f);
const QPoint point(1, 2);
const QPointF pointF(1.1, 2.2);
const QQuaternion quaternion(1.1f, 2.2f, 3.3f, 4.4f);
const QRect rect(1, 2, 3, 4);
const QRectF rectF(1.1, 2.2, 3.3, 4.4);
const QSize size(1, 2);
const QSizeF sizeF(1.1, 2.2);
const QTime qtime(QTime::currentTime());
const QTransform transform(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
const QUrl url(QLatin1String("url"));
const QVariant variant1(QLatin1String("variant"));
const QVariant variant2(123);
const QVariant variant3(date);
const QVector2D vector2D(1.1f, 2.2f);
const QVector3D vector3D(1.1f, 2.2f, 3.3f);
const QVector4D vector4D(1.1f, 2.2f, 3.3f, 4.4f);

const QString string(QLatin1String("string"));
const QStringList stringList{QLatin1String("A"), QLatin1String("B"), QLatin1String("C")};
const QVariantList variantList{QLatin1String("A"), 1.2f, true};
const QVariantHash variantHash{{QLatin1String("true"), true}, {QLatin1String("false"), false}};
const QVariantMap variantMap{{QLatin1String("true"), true}, {QLatin1String("false"), false}};
const QList<int> intList{1, 2, 3};
const QVector<AbstractListModel::Item> abstractListContainer{AbstractListModel::Item(QLatin1String("A"), AbstractListModel::EnumA, nullptr),
                                                             AbstractListModel::Item(QLatin1String("AB"), AbstractListModel::EnumB, nullptr),
                                                             AbstractListModel::Item(QLatin1String("ABC"), AbstractListModel::EnumC, nullptr)};
Object* objectNullptr{nullptr};
const ListModel::Container listContainer{{{ListModel::RoleInteger, 0},
                                          {ListModel::RoleString, QLatin1String("A")},
                                          {ListModel::RoleObject, QVariant::fromValue(objectNullptr)}},
                                         {{ListModel::RoleInteger, 1},
                                          {ListModel::RoleString, QLatin1String("AB")},
                                          {ListModel::RoleObject, QVariant::fromValue(objectNullptr)}},
                                         {{ListModel::RoleInteger, 2},
                                          {ListModel::RoleString, QLatin1String("ABC")},
                                          {ListModel::RoleObject, QVariant::fromValue(objectNullptr)}}};
const Gadget gadget{1, QLatin1String("A"), 123, jsonObject};

void connectSockets(Xylitol::Socket& socketA, Xylitol::Socket& socketB) {
    QObject::connect(&socketA, &Xylitol::Socket::send, &socketB, &Xylitol::Socket::receive);
    QObject::connect(&socketB, &Xylitol::Socket::send, &socketA, &Xylitol::Socket::receive);
}

void initObject(Object& object) {
    object.setBitArray(bitArray);
    object.setByteArray(byteArray);
    object.setColor(color);
    object.setDate(date);
    object.setDateTime(dateTime);
    object.setImage(image);
    object.setJsonArray(jsonArray);
    object.setJsonObject(jsonObject);
    object.setJsonValue(jsonValue);
    object.setLine(line);
    object.setLineF(lineF);
    object.setLocale(locale);
    object.setMatrix4x4(matrix4x4);
    object.setPoint(point);
    object.setPointF(pointF);
    object.setQuaternion(quaternion);
    object.setRect(rect);
    object.setRectF(rectF);
    object.setSize(size);
    object.setSizeF(sizeF);
    object.setTime(qtime);
    object.setTransform(transform);
    object.setUrl(url);
    object.setVariant(variant1);
    object.setVector2D(vector2D);
    object.setVector3D(vector3D);
    object.setVector4D(vector4D);

    object.setBoolValue(true);
    object.setDoubleValue(1.1);
    object.setIntValue(INT_MIN);
    object.setString(string);
    object.setStringList(stringList);
    object.setVariantHash(variantHash);
    object.setVariantList(variantList);
    object.setVariantMap(variantMap);
    object.setIntList(intList);
    object.setEnumeration(Object::Enum::EnumB);
    object.setFlags(Object::Flag::FlagA | Object::Flag::FlagB);
}

} // namespace

TestNode::TestNode()
    : QObject(nullptr) {}

void TestNode::initTestCase() {
    Xylitol::registerContainer<QList<int>>();
    Xylitol::registerGadget<Gadget>();
    qRegisterMetaType<Object::Enum>();
}

void TestNode::init() {
    mNodeA = new Xylitol::Node(this);
    mNodeB = new Xylitol::Node(this);
}

void TestNode::cleanup() {
    delete mNodeA;
    mNodeA = nullptr;

    delete mNodeB;
    mNodeB = nullptr;
}

void TestNode::testInit() {
    RootObject rootA;
    RootObject rootB;

    // Init rootA before connection with rootB
    initObject(rootA);
    initObject(*rootA.childA());
    initObject(*rootA.childB());
    Object* child = new Object(&rootA);
    Gadget* gadgetPtr = new Gadget();
    initObject(*child);
    rootA.setChild(child);
    rootA.setGadget(gadget);
    rootA.setGadgetPtr(gadgetPtr);
    rootA.stringListModel()->reset(stringList);

    // Connect rootB with rootA
    mNodeA->setTarget(&rootA);
    mNodeB->setTarget(&rootB);

    Xylitol::Socket socketAB;
    Xylitol::Socket socketBA;
    connectSockets(socketAB, socketBA);

    mNodeB->setParentSocket(&socketBA);
    mNodeA->addChildSocket(&socketAB);

    // Verify rootB is initialized & same state with rootA
    QVERIFY(mNodeB->isInitialized());

    rootB.compare(rootA);
    QVERIFY(rootB.child() != nullptr);
    rootB.child()->compare(*rootA.child());
    rootB.childA()->compare(*rootA.childA());
    rootB.childB()->compare(*rootA.childB());

    QCOMPARE(rootB.stringListModel()->container(), rootA.stringListModel()->container());
    QCOMPARE(rootB.gadget(), rootA.gadget());
    QCOMPARE(*rootB.gadgetPtr(), *rootA.gadgetPtr());

    delete rootA.gadgetPtr();
    delete rootB.gadgetPtr();
}

void TestNode::testPropertyUpdates() {
    RootObject rootA;
    RootObject rootB;

    mNodeA->setTarget(&rootA);
    mNodeB->setTarget(&rootB);

    Xylitol::Socket socketAB;
    Xylitol::Socket socketBA;
    connectSockets(socketAB, socketBA);

    Xylitol::Socket socketAC;
    Xylitol::Socket socketCA;
    connectSockets(socketAC, socketCA);

    mNodeB->setParentSocket(&socketBA);
    mNodeA->addChildSocket(&socketAB);
    mNodeA->addChildSocket(&socketAC);

    QVERIFY(mNodeB->isInitialized());

    // Init rootA after connection with rootB
    initObject(rootA);
    initObject(*rootA.childA());
    initObject(*rootA.childB());
    Object* object = new Object(&rootA);
    rootA.setChild(object);
    initObject(*object);
    rootA.setGadget(gadget);

    // Verify rootB is same state with rootA
    rootB.compare(rootA);
    QVERIFY(rootB.child() != nullptr);
    rootB.child()->compare(*rootA.child());
    rootB.childA()->compare(*rootA.childA());
    rootB.childB()->compare(*rootA.childB());

    QCOMPARE(rootB.gadget(), rootA.gadget());

    // Update variant property
    rootA.setVariant(variant2);
    rootB.compare(rootA);
    rootA.setVariant(variant3);
    rootB.compare(rootA);
    Object* varObj = new Object(&rootA);
    rootA.setVariant(QVariant::fromValue(varObj));
    rootB.compare(rootA);
    QSignalSpy spyVarObjB(varObj, &Object::destroyed);
    rootA.setVariant(QVariant::fromValue(objectNullptr));
    delete varObj;
    rootB.compare(rootA);
    QVERIFY(!spyVarObjB.isEmpty());

    // Update flag property
    rootA.setFlags(Object::Flag::FlagA);
    rootB.compare(rootA);
    rootA.setFlags(Object::Flag::FlagNone);
    rootB.compare(rootA);

    // Update child property
    rootA.child()->setIntValue(123);
    rootB.child()->compare(*rootA.child());

    // Update child
    Object* object2 = new Object(&rootA);
    initObject(*object2);
    rootA.setChild(object2);
    rootB.compare(rootA);

    // Update gadget
    rootA.setGadget(Gadget({123, QLatin1String("4"),5,{{QLatin1String("6"), 7}}}));
    QCOMPARE(rootA.gadget(), rootB.gadget());

    // Update gadget pointer
    Gadget* gadgetPtr = new Gadget({123, QLatin1String("4"),5,{{QLatin1String("6"), 7}}});
    rootA.setGadgetPtr(gadgetPtr);
    QCOMPARE(*rootA.gadgetPtr(), *rootB.gadgetPtr());

    // Reset child
    rootA.setChild(nullptr);
    rootB.compare(rootA);

    // Reset gadget pointer
    rootA.setGadgetPtr(nullptr);
    QCOMPARE(rootA.gadgetPtr(), rootB.gadgetPtr());

    delete gadgetPtr;
}

void TestNode::testSignals() {
    RootObject rootA;
    RootObject rootB;

    mNodeA->setTarget(&rootA);
    mNodeB->setTarget(&rootB);

    Xylitol::Socket socketAB;
    Xylitol::Socket socketBA;
    connectSockets(socketAB, socketBA);

    mNodeB->setParentSocket(&socketBA);
    mNodeA->addChildSocket(&socketAB);

    QVERIFY(mNodeB->isInitialized());

    QSignalSpy spyB0(&rootB, &RootObject::testEmpty);
    QSignalSpy spyC0(&rootA, &RootObject::testEmpty);
    emit rootA.testEmpty();
    QVERIFY(!spyB0.isEmpty());
    QVERIFY(!spyC0.isEmpty());

    QSignalSpy spyB1(&rootB, &RootObject::testGadget);
    QSignalSpy spyC1(&rootA, &RootObject::testGadget);
    emit rootA.testGadget(gadget);
    QVERIFY(!spyB1.isEmpty());
    QVERIFY(!spyC1.isEmpty());

    QSignalSpy spyA2(&rootA, &RootObject::testGadget);
    emit rootB.testGadget(gadget);
    QVERIFY(!spyA2.isEmpty());

    QSignalSpy spyA31(&rootA, &RootObject::testA);
    emit rootB.testA();
    QVERIFY(!spyA31.isEmpty());

    QSignalSpy spyA32(&rootA, &RootObject::testB);
    emit rootB.testB(1, QLatin1String("A"));
    QVERIFY(!spyA32.isEmpty());
    const QList<QVariant> argA32 = spyA32.takeFirst();
    QVERIFY(argA32.at(0) == 1);
    QVERIFY(argA32.at(1) == QLatin1String("A"));

    QSignalSpy spyA33(&rootA, &RootObject::testC);
    emit rootB.testC(Object::Enum::EnumB);
    QVERIFY(!spyA33.isEmpty());
    const QList<QVariant> argA33 = spyA33.takeFirst();
    QVERIFY(argA33.at(0).toInt() == static_cast<int>(Object::Enum::EnumB));

    QSignalSpy spyA31Child(rootA.childA(), &RootObject::testA);
    emit rootB.childA()->testA();
    QVERIFY(!spyA31Child.isEmpty());

    QSignalSpy spyAD(&rootA, &RootObject::testD);
    emit rootB.testD(variant1);
    QVERIFY(!spyAD.isEmpty());
    const QList<QVariant> argAD = spyAD.takeFirst();
    QVERIFY(argAD.at(0) == variant1);

    QSignalSpy spyAE(&rootA, &RootObject::testE);
    emit rootB.testE(string, string, jsonObject);
    QVERIFY(!spyAE.isEmpty());
    const QList<QVariant> argAE = spyAE.takeFirst();
    QVERIFY(argAE.at(0) == string);
    QVERIFY(argAE.at(1) == string);
    QVERIFY(argAE.at(2) == jsonObject);
}

void TestNode::testAbstractListModel() {
    AbstractListModel modelA;
    AbstractListModel modelB;

    mNodeA->setTarget(&modelA);
    mNodeB->setTarget(&modelB);

    Xylitol::Socket socketAB;
    Xylitol::Socket socketBA;
    connectSockets(socketAB, socketBA);

    Xylitol::Socket socketAC;
    Xylitol::Socket socketCA;
    connectSockets(socketAC, socketCA);

    mNodeB->setParentSocket(&socketBA);
    mNodeA->addChildSocket(&socketAB);
    mNodeA->addChildSocket(&socketAC);

    QVERIFY(mNodeB->isInitialized());

    // reset
    {
        modelA.reset(abstractListContainer);
        QCOMPARE(modelB.container(), modelA.container());

        modelA.reset({});
        QVERIFY(modelB.container().isEmpty());
    }

    // append
    {
        modelA.append({QLatin1String("A"), AbstractListModel::EnumA, new Object(&modelA)});
        const QVector<AbstractListModel::Item> expected1 = modelA.container();
        QVERIFY(modelB.container().at(0).mObject != modelA.container().at(0).mObject);
        QCOMPARE(modelB.container(), expected1);

        modelA.append({QLatin1String("AB"), AbstractListModel::EnumB, new Object(&modelA)});
        const QVector<AbstractListModel::Item> expected2 = modelA.container();
        QVERIFY(modelB.container().at(1).mObject != modelA.container().at(1).mObject);
        QCOMPARE(modelB.container(), expected2);
    }

    // remove
    {
        modelA.reset(abstractListContainer);
        QVector<AbstractListModel::Item> expected = modelA.container();

        modelA.remove(0, 0);
        expected.takeFirst();
        QCOMPARE(modelB.container(), expected);

        modelA.remove(1, 1);
        expected.takeLast();
        QCOMPARE(modelB.container(), expected);

        modelA.remove(0, 0);
        QVERIFY(modelB.container().isEmpty());
    }

    // move
    {
        modelA.reset(abstractListContainer);
        QVector<AbstractListModel::Item> expected = modelA.container();

        modelA.move(0, 1, 3);
        expected.move(2, 0);
        QCOMPARE(modelB.container(), expected);

        modelA.move(1, 2, 0);
        expected.move(0, 2);
        QCOMPARE(modelB.container(), expected);
    }

    // set
    {
        modelA.reset(abstractListContainer);
        QVector<AbstractListModel::Item> expected = modelA.container();

        modelA.set(0, {QLatin1String("D"), AbstractListModel::EnumUndefined, nullptr});
        expected.replace(0, {QLatin1String("D"), AbstractListModel::EnumUndefined, nullptr});
        QCOMPARE(modelB.container(), expected);
    }
}

void TestNode::testListModel() {
    ListModel modelA;
    ListModel modelB;

    mNodeA->setTarget(&modelA);
    mNodeB->setTarget(&modelB);

    Xylitol::Socket socketAB;
    Xylitol::Socket socketBA;
    connectSockets(socketAB, socketBA);

    Xylitol::Socket socketAC;
    Xylitol::Socket socketCA;
    connectSockets(socketAC, socketCA);

    mNodeB->setParentSocket(&socketBA);
    mNodeA->addChildSocket(&socketAB);
    mNodeA->addChildSocket(&socketAC);

    QVERIFY(mNodeB->isInitialized());

    // reset
    {
        modelA.reset(listContainer);

        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(Xylitol::toVariantList(modelA.roleNames().keys()))),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(Xylitol::toVariantList(modelB.roleNames().keys()))));

        modelA.reset({});
        QVERIFY(modelB.container().isEmpty());
    }

    // append
    {
        modelA.append({{ListModel::RoleInteger, QLatin1String("100")},
                       {ListModel::RoleString, QLatin1String("A")},
                       {ListModel::RoleObject, QVariant::fromValue(new Object(this))}});
        QVERIFY(modelB.container().at(0).value(ListModel::RoleObject) != modelA.container().at(0).value(ListModel::RoleObject));
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(Xylitol::toVariantList(modelA.roleNames().keys()))),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(Xylitol::toVariantList(modelB.roleNames().keys()))));

        modelA.append({{ListModel::RoleInteger, QLatin1String("200")},
                       {ListModel::RoleString, QLatin1String("B")},
                       {ListModel::RoleObject, QVariant::fromValue(new Object(this))}});
        QVERIFY(modelB.container().at(1).value(ListModel::RoleObject) != modelA.container().at(1).value(ListModel::RoleObject));
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(Xylitol::toVariantList(modelA.roleNames().keys()))),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(Xylitol::toVariantList(modelB.roleNames().keys()))));
    }

    // remove
    {
        modelA.reset(listContainer);

        modelA.remove(0, 0);
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));

        modelA.remove(1, 1);
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));

        modelA.remove(0, 0);
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));
    }

    // move
    {
        modelA.reset(listContainer);

        modelA.move(0, 1, 3);
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));

        modelA.move(1, 2, 0);
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));
    }

    // set
    {
        modelA.reset(listContainer);

        modelA.set(0, {{ListModel::RoleInteger, QLatin1String("4")},
                       {ListModel::RoleString, QLatin1String("D")},
                       {ListModel::RoleObject, QVariant::fromValue(new Object(this))}});
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));

        modelA.setString(1, QString());
        QCOMPARE(modelA.xylitolToVariantList(0, modelA.container().count() - 1, Xylitol::toVariantList(modelA.roleNames().keys())),
                 modelB.xylitolToVariantList(0, modelB.container().count() - 1, Xylitol::toVariantList(modelB.roleNames().keys())));
    }
}

void TestNode::testStringListModel() {
    StringListModel modelA;
    StringListModel modelB;

    mNodeA->setTarget(&modelA);
    mNodeB->setTarget(&modelB);

    Xylitol::Socket socketAB;
    Xylitol::Socket socketBA;
    connectSockets(socketAB, socketBA);

    Xylitol::Socket socketAC;
    Xylitol::Socket socketCA;
    connectSockets(socketAC, socketCA);

    mNodeB->setParentSocket(&socketBA);
    mNodeA->addChildSocket(&socketAB);
    mNodeA->addChildSocket(&socketAC);

    QVERIFY(mNodeB->isInitialized());

    // reset
    {
        modelA.reset(stringList);
        QCOMPARE(modelB.container(), stringList);

        modelA.reset(QStringList{});
        QVERIFY(modelB.container().isEmpty());
    }

    // append
    {
        modelA.append(QLatin1String("A"));
        const QStringList expected1{QLatin1String("A")};
        QCOMPARE(modelB.container(), expected1);

        modelA.append(QLatin1String("B"));
        const QStringList expected2{QLatin1String("A"), QLatin1String("B")};
        QCOMPARE(modelB.container(), expected2);
    }

    // remove
    {
        modelA.reset(stringList);
        QStringList expected = stringList;

        modelA.remove(0, 0);
        expected.takeFirst();
        QCOMPARE(modelB.container(), expected);

        modelA.remove(1, 1);
        expected.takeLast();
        QCOMPARE(modelB.container(), expected);

        modelA.remove(0, 0);
        QVERIFY(modelB.container().isEmpty());
    }

    // set
    {
        modelA.reset(stringList);
        QStringList expected = stringList;

        modelA.set(0, QLatin1String("D"));
        expected.replace(0, QLatin1String("D"));
        QCOMPARE(modelB.container(), expected);
    }

    // move
    {
        modelA.reset(stringList);
        QStringList expected = stringList;

        modelA.move(0, 1, 3);
        expected.move(2, 0);
        QCOMPARE(modelB.container(), expected);

        modelA.move(1, 2, 0);
        expected.move(0, 2);
        QCOMPARE(modelB.container(), expected);
    }
}
