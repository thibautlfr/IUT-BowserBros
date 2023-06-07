#include <QtTest>

// add necessary includes here

#include "../App/bowser.h"
#include "../App/fireball.h"


class TestUnitBowser : public QObject
{
    Q_OBJECT

private slots:
    void testBowserConstructor();
    void testFireBallConstructor();
    void testDropFireBall();
    void testFireBallCalculatePosition();
    void testFireBallGetItsRect();
    void testBowserDestructor();
};

void TestUnitBowser::testBowserConstructor()
{
    Bowser bowser(0, 0, 100, 100, "../../BowserBros/App/Assets/mario/mario1.png");
    QCOMPARE(bowser.getItsFireBalls()->size(), 0); // On s'attend à ce qu'aucune boule de feu n'ait été créée au départ.
}

void TestUnitBowser::testFireBallConstructor()
{
    FireBall fireball(0, 0);
    QCOMPARE(fireball.getItsRect().y(), 0.0); // On s'attend à ce que la position y initiale soit 0.
}

void TestUnitBowser::testDropFireBall()
{
    Bowser bowser(0, 0, 100, 100, "../../BowserBros/App/Assets/mario/mario1.png");
    int initialSize = bowser.getItsFireBalls()->size();
    bowser.dropFireBall();
    int newSize = bowser.getItsFireBalls()->size();
    QCOMPARE(newSize, initialSize + 1);
}

void TestUnitBowser::testFireBallCalculatePosition()
{
    FireBall fireball(0, 0);
    float initialY = fireball.getItsRect().y();
    fireball.calculatePosition();
    float newY = fireball.getItsRect().y();
    QCOMPARE(newY, initialY + 2);
}

void TestUnitBowser::testFireBallGetItsRect()
{
    FireBall fireball(0, 0);
    QRect rect = fireball.getItsRect();
    QCOMPARE(rect.x(), 0.0); // On s'attend à ce que la position x soit 0.
    QCOMPARE(rect.y(), 0.0); // On s'attend à ce que la position y soit 0.
}

void TestUnitBowser::testBowserDestructor()
{
    Bowser* bowser = new Bowser(0, 0, 100, 100, "../../BowserBros/App/Assets/mario/mario1.png");
    bowser->dropFireBall();
    delete bowser;
    // Le test est réussi si aucun problème de mémoire n'est détecté (fuites de mémoire, etc.)
}
QTEST_APPLESS_MAIN(TestUnitBowser)

#include "tst_testunitbowser.moc"
