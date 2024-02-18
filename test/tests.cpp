#include <gtest/gtest.h>
#include "../headers/FuncionesMath.h"
#include <cmath>

// Pruebas para cosMath
// Verificar que el resultado de la función cosMath(0.0) sea igual a 1.0.
TEST(CosMathTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(cosMath(0.0), 1.0);
}

TEST(CosMathTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(cosMath(-1.0), 0.54030230586813977);
}

// Pruebas para senMath
TEST(SenMathTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(senMath(0.0), 0.0);
}

TEST(SenMathTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(senMath(-1.0), -0.8414709848078965);
}

// Pruebas para customCos
TEST(CustomCosTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(customCos(0.0), 1.0);
}

TEST(CustomCosTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(customCos(-1.0), 0.54030230586813977);
}

// Pruebas para customSen
TEST(CustomSenTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(customSen(0.0), 0.0);
}

TEST(CustomSenTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(customSen(-1.0), -0.8414709848078965);
}

// Otros tests de operaciones combinadas de las funciones

TEST(OperacionesCombinadasTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(customCos(0.0) + customSen(0.0), 1.0);
}

TEST(OperacionesCombinadasTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(customCos(-1.0) + customSen(-1.0), 0.54030230586813977 - 0.8414709848078965);
}

// Custom cos y cos de math.h

TEST(CustomCosMathTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(customCos(0.0), cos(0.0));
}

TEST(CustomCosMathTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(customCos(-1.0), cos(-1.0));
}

// Custom sen y sen de math.h

TEST(CustomSenMathTest, TestPositivo) {
    EXPECT_DOUBLE_EQ(customSen(0.0), sin(0.0));
}

TEST(CustomSenMathTest, TestNegativo) {
    EXPECT_DOUBLE_EQ(customSen(-1.0), sin(-1.0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}