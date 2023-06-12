#include <QtTest>

// add necessary includes here

#include "../App/element.h"

class TestUnitElement: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
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
    testElement1 = new Element(100.0, 100.0, "../../BowserBros/App/Assets/mario/mario1.png");
    image = new QImage(800, 600, QImage::Format_RGB32);
    painter = new QPainter(image);
}

void TestUnitElement::cleanupTestCase()
{
    delete testElement1;
    delete painter;
    delete image;
}

void TestUnitElement::testConstructorWithImage()
{
    QCOMPARE(testElement1->getRect(), QRect(100, 100, testElement1->getRect().width(), testElement1->getRect().height()));
}

void TestUnitElement::testGetRect()
{
    QRect rect = testElement1->getRect();
    QVERIFY(rect.x() == 100 && rect.y() == 100);
}

void TestUnitElement::testDraw()
{
    testElement1->draw(painter);
    // Test passed if no exceptions were thrown and program didn't crash.
}

QTEST_APPLESS_MAIN(TestUnitElement)

#include "tst_testunitelement.moc"
