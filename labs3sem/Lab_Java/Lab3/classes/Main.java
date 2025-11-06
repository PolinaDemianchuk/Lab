package classes;


public class Main
{
    public static void main(String[] args)
    {
        CoffeeMachineList coffeeList = new CoffeeMachineList();
        CoffeeMachineMap coffeeMap = new CoffeeMachineMap();
        Menu menu = new Menu(coffeeList, coffeeMap);
        menu.showMenu();
    }
}