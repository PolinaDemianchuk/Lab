package classes;

import abstractclasses.AbsList;
import classes.CoffeeMachineNotAbstr;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class Menu
{
    private Scanner scanner;
    private AbsList<CoffeeMachineNotAbstr> storage;

    public Menu(AbsList<CoffeeMachineNotAbstr> storage)
    {
        this.scanner = new Scanner(System.in);
        this.storage = storage;
    }

    public void showMenu()
    {
        while (true)
        {
            System.out.println("Coffee Machine Factory");
            System.out.println("1. Display all machines");
            System.out.println("2. Add new machine");
            System.out.println("3. Update machine");
            System.out.println("4. Delete machine");
            System.out.println("5. Sort machines");
            System.out.println("6. Exit");
            System.out.print("Choose an option: ");

            int choice = getIntInput();
            switch (choice)
            {
                case 1:
                    storage.displayAll();
                    break;
                case 2:
                    addMachine();
                    break;
                case 3:
                    updateMachine();
                    break;
                case 4:
                    deleteMachine();
                    break;
                case 5:
                    sortMachines();
                    break;
                case 6:
                    return;
                default:
                    System.out.println("Invalid option. Try again.");
            }
        }
    }

    private void addMachine()
    {
        System.out.println("Add New Coffee Machine");

        System.out.print("ID: ");
        int id = getIntInput();

        System.out.print("Type: ");
        String type = scanner.nextLine();

        System.out.print("Model: ");
        String model = scanner.nextLine();

        System.out.print("Power: ");
        int power = getIntInput();

        System.out.print("Max coffee capacity: ");
        int coffeeCap = getIntInput();

        System.out.print("Max Water Capacity: ");
        int waterCap = getIntInput();

        System.out.print("Date (dd.MM.yyyy): ");
        Date date = getDateInput();

        System.out.print("Price: ");
        double price = getDoubleInput();

        CoffeeMachineNotAbstr machine = new CoffeeMachineNotAbstr(id, type, model, power, coffeeCap, waterCap, date, price);
        storage.add(machine);
        System.out.println("Machine added successfully.");
    }

    private void updateMachine()
    {
        System.out.print("Enter machine ID to update: ");
        int id = getIntInput();
        CoffeeMachineNotAbstr machine = storage.get(id);

        if (machine == null)
        {
            System.out.println("Machine with ID " + id + " not found.");
            return;
        }

        System.out.println("Current data: " + machine);
        System.out.println("Enter new data:");

        System.out.print("Type: ");
        String type = scanner.nextLine();
            machine.setType(type);

        System.out.print("Model ]: ");
        String model = scanner.nextLine();
            machine.setModel(model);


        System.out.print("Power : ");
        String powerInput = scanner.nextLine();
            machine.setPower(Integer.parseInt(powerInput));


        System.out.print("Max Coffee Capacity : ");
        String coffeeCapInput = scanner.nextLine();
            machine.setMaxCoffeeCapacity(Integer.parseInt(coffeeCapInput));


        System.out.print("Max Water Capacity : ");
        String waterCapInput = scanner.nextLine();
            machine.setMaxWaterCapacity(Integer.parseInt(waterCapInput));


        System.out.print("Price : ");
        String priceInput = scanner.nextLine();
            machine.setPrice(Double.parseDouble(priceInput));


        storage.update(machine);
        System.out.println("Machine updated successfully.");
    }

    private void deleteMachine()
    {
        System.out.print("Enter machine ID to delete: ");
        int id = getIntInput();
        CoffeeMachineNotAbstr machine = storage.get(id);
            storage.delete(id);
    }

    private void sortMachines()
    {
        System.out.println("\n--- Sort Machines ---");
        System.out.println("1. By Price (ascending)");
        System.out.println("2. By Price (descending)");
        System.out.println("3. By Power (ascending)");
        System.out.println("4. By Power (descending)");
        System.out.println("5. By Manufacture Date (ascending)");
        System.out.println("6. By Manufacture Date (descending)");
        System.out.print("Choose one: ");

        int choice = getIntInput();
        List<CoffeeMachineNotAbstr> allMachines = storage.getAll();

        switch (choice)
        {
            case 1:
                allMachines.sort((m1, m2) -> Double.compare(m1.getPrice(), m2.getPrice()));
                break;
            case 2:
                allMachines.sort((m1, m2) -> Double.compare(m2.getPrice(), m1.getPrice()));
                break;
            case 3:
                allMachines.sort((m1, m2) -> Integer.compare(m1.getPower(), m2.getPower()));
                break;
            case 4:
                allMachines.sort((m1, m2) -> Integer.compare(m2.getPower(), m1.getPower()));
                break;
            case 5:
                allMachines.sort((m1, m2) -> m1.getManufactureDate().compareTo(m2.getManufactureDate()));
                break;
            case 6:
                allMachines.sort((m1, m2) -> m2.getManufactureDate().compareTo(m1.getManufactureDate()));
                break;
            default:
                System.out.println("Invalid choice.");
                return;
        }

        System.out.println("Sorted Machines: ");
        for (CoffeeMachineNotAbstr machine : allMachines) {
            System.out.println(machine);
        }
    }
    
    private int getIntInput()
    {
        while (true) 
        {
            try 
            {
                return Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) 
            {
                System.out.print("Invalid input. Enter a number: ");
            }
        }
    }

    private double getDoubleInput() 
    {
        while (true) 
        {
            try
            {
                return Double.parseDouble(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.print("Invalid input. Enter a decimal number: ");
            }
        }
    }

    private Date getDateInput()
    {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        while (true)
        {
            try 
            {
                return dateFormat.parse(scanner.nextLine());
            } catch (ParseException e) {
                System.out.print("Invalid date format. Use dd.MM.yyyy: ");
            }
        }
    }

    public String readFile(String filename)
    {
        String str = "";
        try (FileReader fr = new FileReader(filename))
        {
            int i;
            while ((i = fr.read()) != -1)
            {
                str += (char) i;
            }
        } catch (IOException e)
        {
            System.out.println("Ошибка чтения файла");
        }
        return str;
    }

    public void writeFile(String info)
    {
        try (FileWriter writer = new FileWriter("output.txt", true))
        {
            writer.write(info + "\n");
        } catch (IOException e)
        {
            System.out.println("Ошибка при записи в файл: ");
        }
    }
}