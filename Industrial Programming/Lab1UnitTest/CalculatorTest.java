import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CalculatorTest {
    void testCalculation(double x, int k) {
        Calculator C = new Calculator(k, x);
        assertTrue(Math.abs(C.calculation() - Math.sin(x)) < Math.pow(10, -k));
    }

    @Test
    void testCalculationXX() {
        for (double i = -100; i < 100; i += 0.37) {
            for (int j = 0; j < 5; j++) {
                testCalculation(i, j);
            }
        }
    }
    @Test
    void testCalculation1000() {
        double x = 1000; int k = 5;
        Calculator C = new Calculator(k, x);
        assertTrue(Math.abs(C.calculation() - Math.sin(x)) < Math.pow(10, -k));
    }
}