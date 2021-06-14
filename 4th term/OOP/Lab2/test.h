#ifndef TEST_H
#define TEST_H
#include <QtTest/QtTest>
#include "solve.h"
#include "factory.h"
#include "strategy.h"

class Test: public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);

signals:

private slots:
    void test_Kramer();
    void test_Jacobi();
    void test_Zeidel();
};

#endif // TEST_H
