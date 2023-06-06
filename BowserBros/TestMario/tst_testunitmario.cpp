#include <QtTest>

// add necessary includes here

#include "../App/mario.h"
#include "../App/entity.h"

class TestUnitMario : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testConstructorWithDimensions();
    void testConstructorWithImage();
    void testJump();
    void testIntersect();

private:
    Mario *testMario1;
    Mario *testMario2;
    QPainter *painter;
    QImage *image;
};

void TestUnitMario::initTestCase()
{
    testMario1 = new Mario(50.0, 50.0, 100, 100);
    testMario2 = new Mario(100.0, 100.0, "../../BowserBros/App/Assets/mario/mario1.png");
    image = new QImage(800, 600, QImage::Format_RGB32);
    painter = new QPainter(image);
}

void TestUnitMario::cleanupTestCase()
{
    delete testMario1;
    delete testMario2;
    delete painter;
    delete image;
}

void TestUnitMario::testConstructorWithDimensions()
{
    QCOMPARE(testMario1->getItsRect(), QRect(50, 50, 100, 100));
    QCOMPARE(testMario1->getYSpeed(), 0.0f);
}

void TestUnitMario::testConstructorWithImage()
{
    QCOMPARE(testMario2->getItsRect(), QRect(100, 100, testMario2->getItsRect().width(), testMario2->getItsRect().height()));
    QCOMPARE(testMario2->getYSpeed(), 0.0f);
}

void TestUnitMario::testJump()
{
    testMario1->jump();
    QCOMPARE(testMario1->getYSpeed(), -8.0f);
}


void TestUnitMario::testIntersect()
{
    QRect obstacle(60, 60, 10, 10);
    bool expected = testMario1->getItsRect().intersects(obstacle);
    QCOMPARE(testMario1->intersect(obstacle), expected);
}

QTEST_APPLESS_MAIN(TestUnitMario)

#include "tst_testunitmario.moc"
