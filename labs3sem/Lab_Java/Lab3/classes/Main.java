package classes;

import classes.CoffeeMachineList;
import classes.Menu;

public class Main
{
    public static void main(String[] args)
    {
        CoffeeMachineList storage = new CoffeeMachineList();
        Menu menu = new Menu(storage);
        menu.showMenu();
    }
}