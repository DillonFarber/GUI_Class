/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Assignment4/network.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_network_t {
    const uint offsetsAndSize[18];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_network_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_network_t qt_meta_stringdata_network = {
    {
QT_MOC_LITERAL(0, 7), // "network"
QT_MOC_LITERAL(8, 6), // "allSet"
QT_MOC_LITERAL(15, 0), // ""
QT_MOC_LITERAL(16, 20), // "sensingDistanceTicks"
QT_MOC_LITERAL(37, 13), // "lengthOfCable"
QT_MOC_LITERAL(51, 13), // "numberOfTicks"
QT_MOC_LITERAL(65, 13), // "messageLength"
QT_MOC_LITERAL(79, 20), // "probabilityOfMessage"
QT_MOC_LITERAL(100, 3) // "run"

    },
    "network\0allSet\0\0sensingDistanceTicks\0"
    "lengthOfCable\0numberOfTicks\0messageLength\0"
    "probabilityOfMessage\0run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_network[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   59,    2, 0x0a,    3 /* Public */,
       4,    1,   62,    2, 0x0a,    5 /* Public */,
       5,    1,   65,    2, 0x0a,    7 /* Public */,
       6,    1,   68,    2, 0x0a,    9 /* Public */,
       7,    1,   71,    2, 0x0a,   11 /* Public */,
       8,    0,   74,    2, 0x0a,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<network *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->allSet((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->sensingDistanceTicks((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->lengthOfCable((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->numberOfTicks((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->messageLength((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->probabilityOfMessage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (network::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&network::allSet)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject network::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_network.offsetsAndSize,
    qt_meta_data_network,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_network_t
, QtPrivate::TypeAndForceComplete<network, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_network.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void network::allSet(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
