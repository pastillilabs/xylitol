#pragma once

#include <xylitol/node.h>

#include <QtTest/QtTest>

/**
 * @brief The TestNode class
 */
class TestNode : public QObject {
    Q_OBJECT

public:
    TestNode();

private slots:
    void initTestCase();

    void init();
    void cleanup();

    void testInit();
    void testPropertyUpdates();
    void testSignals();
    void testAbstractListModel();
    void testListModel();
    void testStringListModel();

private:
    Xylitol::Node* mNodeA{nullptr};
    Xylitol::Node* mNodeB{nullptr};
};
