# Xylitol

## Introduction

Provides a mechanism to relay QObject signals, property updates & list model updates over serialized communication channel. Intended for communication over IPC in a trusted environment.

The idea is that with the help of Xylitol, multiple processes can share a common application model library where object properties and list models are automatically kept up-to-date between processes and signals emitted from one process will be visible to all and thus can be used for communication.

This is perhaps somewhat similar to [Qt Remote Objects](https://doc.qt.io/qt-5/qtremoteobjects-index.html), except that there is no need for extra tooling and compiler steps. The model library can be just normal Qt code. On the other hand, the features and use cases are also more limited.

An important design goal is also that Xylitol and the application model based on it can be directly used from both C++ & QML.

Currently the project is only qmake based and actively used on Qt 5.6 (Sailfish OS) & 5.15 (Android, Linux, Windows). It should compile and work, but is not actively used, also on 6.x. CMake support will follow later.

## Usage

User of the library is expected to provide application specific model designed with the constraints of Xylitol & IPC in mind. Also, the IPC mechanism itself must be provided by the user. Good candidates would be [Qt WebSockets](https://doc.qt.io/qt-5/qtwebsockets-index.html) or [jsonipc](https://github.com/pastillilabs/jsonipc).

Each process needs to instantiate a Xylitol::Node and attach the application model to it. And then connect the nodes, preferrably in a client-server fashion, where one process and application model acts as the main instance.

### Properties

Properties can be value types supported or serializable by Xylitol or QObject* based for defining object hierarchies. CONSTANT value properties or properties marked as "STORED false" are not sycnhornized. Synchronizable properties must provide READ, WRITE and NOTIFY accessors.

Following functions can be provided to intercept property access and implement custom behavior, for example to support plugins.
```
Q_INVOKABLE QVariant xylitolFromVariant(const QMetaProperty& metaProperty, const QVariant& variant);
Q_INVOKABLE void xylitolWrite(const QMetaProperty& metaProperty, const QVariant& value);
```

### Signals

A signal emitted in one instance will be called in all other instances. Arbitrary signal arguments are supported although argument types need to be supported and/or serializable by Xylitol. Default arguments should not be used.

### List models

List models need to inherit either from Xylitol::AbstractListModel, where the user is expected to provide much of the serialization, or from Xylitol::ListModel which provides a more automated list model mechanism but may have a bit more verbose C++ interface for accessing model data.

Especially with list models, the user should make sure that there is only one master instance (node) that is resposible for updating the actual list model data. Otherwise the list models between different processes can easily get out of sync, resulting in an undefined state.

## Platform notes

_Sailfish OS_

Installs libxylitol.so to /usr/share/$${HARBOUR_NAME}/lib where HARBOUR_NAME needs to be defined outside this project.

Uses config value "sailfish" to distinguish between Sailfish OS and other linux environments. This also needs to be provided from outseide.

Both can be provided for example by using .qmake.conf file in project root that contains:
```
CONFIG += sailfish
HARBOUR_NAME = myapplicationname
``` 
