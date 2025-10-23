package org.example;

import static org.example.PrWr.Atan;
import static org.junit.jupiter.api.Assertions.*;

class PrWrTest {

    @org.junit.jupiter.api.Test
    void atan()
    {
        double x = 0.5;
        int k=6;
        double result=Atan(x,k);
        assertEquals(0.46364769089584895,result);
    }
    void atanNegative()
    {
        double x = -0.2;
        int k=6;
        double result=Atan(x,k);
        assertEquals(-0.19739556165079364,result);
    }

    @org.junit.jupiter.api.Test
    void main()
    {

    }
}