#include <QtTest>

// add necessary includes here

#include "../App/element.h"

class TestUnitElement: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testConstructorWithDimensions();
    void testConstructorWithImage();
    void testGetRect();
    void testDraw();

private:
    Element *testElement1;
    Element *testElement2;
    QPainter *painter;
    QImage *image;
};

void TestUnitElement::initTestCase()
{
    testElement1 = new Element(50.0, 50.0, 100, 100);
    testElement2 = new Element(100.0, 100.0, "../../BowserBros/App/Assets/mario/mario1.png");
    image = new QImage(800, 600, QImage::Format_RGB32);
    painter = new QPainter(image);
}

void TestUnitElement::cleanupTestCase()
{
    delete testElement1;
    delete testElement2;
    delete painter;
    delete image;
}

void TestUnitElement::testConstructorWithDimensions()
{
    QCOMPARE(testElement1->getRect(), QRect(50, 50, 100, 100));
}

void TestUnitElement::testConstructorWithImage()
{
    QCOMPARE(testElement2->getRect(), QRect(100, 100, testElement2->getRect().width(), testElement2->getRect().height()));
}

void TestUnitElement::testGetRect()
{
    QRect rect = testElement1->getRect();
    QVERIFY(rect.x() == 50 && rect.y() == 50 && rect.width() == 100 && rect.height() == 100);
}

void TestUnitElement::testDraw()
{
    testElement1->draw(painter);
    testElement2->draw(painter);
    // Test passed if no exceptions were thrown and program didn't crash.
}

QTEST_APPLESS_MAIN(TestUnitElement)

#include "tst_testunitelement.moc"
