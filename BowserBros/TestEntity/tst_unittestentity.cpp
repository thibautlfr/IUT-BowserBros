#include <QtTest>

// add necessary includes here

#include "../App/entity.h"

class UnitTestEntity : public QObject
{
        Q_OBJECT
    private slots:
        void testConstructor();
        void testReverseXSpeed();
        void testReverseYSpeed();
        void testCalculatePosition();
        void testSettersAndGetters();
    };

    void UnitTestEntity::testConstructor()
    {
        Entity entity(10, 20, 30, 40);
        QCOMPARE(entity.getItsY(), 20.0f);
        QCOMPARE(entity.getXSpeed(), 0.0f);
        QCOMPARE(entity.getYSpeed(), 0.0f);
        QCOMPARE(entity.getItsRect(), QRect(10, 20, 30, 40));
    }

    void UnitTestEntity::testReverseXSpeed()
    {
        Entity entity(0, 0, 0, 0);
        entity.setXSpeed(10.0f);
        entity.reverseXSpeed();
        QCOMPARE(entity.getXSpeed(), -10.0f);
    }

    void UnitTestEntity::testReverseYSpeed()
    {
        Entity entity(0, 0, 0, 0);
        entity.setYSpeed(10.0f);
        entity.reverseYSpeed();
        QCOMPARE(entity.getYSpeed(), -10.0f);
    }

    void UnitTestEntity::testCalculatePosition()
    {
        Entity entity(0, 0, 0, 0);
        entity.setXSpeed(10.0f);
        entity.setYSpeed(20.0f);
        entity.calculatePosition();
        QCOMPARE(entity.getItsY(), 20.0f);
    }

    void UnitTestEntity::testSettersAndGetters()
    {
        Entity entity(0, 0, 0, 0);
        entity.setItsX(10.0f);
        entity.setItsY(20.0f);
        entity.setXSpeed(30.0f);
        entity.setYSpeed(40.0f);
        QCOMPARE(entity.getItsY(), 20.0f);
        QCOMPARE(entity.getXSpeed(), 30.0f);
        QCOMPARE(entity.getYSpeed(), 40.0f);
};

QTEST_APPLESS_MAIN(UnitTestEntity)

#include "tst_unittestentity.moc"
