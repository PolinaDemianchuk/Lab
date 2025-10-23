package org.example;

import java.io.*;
import java.util.Formatter;
import java.util.Scanner;

class PrWr
{
    static double Atan(double s, int k)
    {
        double sum=0;
        int sign=1;
        if(s<0)
        {
            sign=-1;
        }
        double prom = 0;
        double p = Math.pow(10, (-1) * k);
        for (int i = 1; i > 0; i++)
        {
            prom = sign*(Math.pow(-1, i - 1) * (Math.pow(Math.abs(s), 2 * i - 1)) / (2 * i - 1));
            sum = sum + prom;
            if (Math.abs(prom) < p)
                break;
        }
        return sum;
    }
    public static void main(String[] args) throws IOException
    {

        double s;
        double sum=0;
        Scanner scan=new Scanner(System.in);
        System.out.println("Введите x в диапазоне (-1,1)");
        s=scan.nextDouble();
        if(s<=-1 || s>=1)
        {
            System.out.println("Нет в диапазоне");
        }
        else
        {
            System.out.println("arctan x=" + Math.atan(s));
            int k;
            double p;
            System.out.println("Введите k");
            k = scan.nextInt();
            double res=Atan(s,k);

            System.out.println(Atan(s,k));

            Formatter form=new Formatter();
            form.format("Hex k: %x,  Oct k: %o%n",k,k);
            form.format("k с нулями: %03d%n", k);
            form.format("k со знаком: %+d%n", k);
            form.format("Результат c #: %#3.2e%n", res);
            form.format("Результат (): (%07.3f)%n", res);

            System.out.println(form);

        }
    }
}


