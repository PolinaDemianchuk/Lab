package classes;

import abstractclasses.AbsList;
import classes.CoffeeMachineNotAbstr;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.*;

import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

public class Menu
{
    private Scanner scanner;
    private AbsList<CoffeeMachineNotAbstr> coffeeList;
    private AbsList<CoffeeMachineNotAbstr> coffeeMap;
    private FilesMethods FilesAll;

    public Menu(AbsList<CoffeeMachineNotAbstr> coffeeList, AbsList<CoffeeMachineNotAbstr> coffeeMap)
    {
        this.scanner = new Scanner(System.in);
        this.coffeeList = coffeeList;
        this.coffeeMap = coffeeMap;
        this.FilesAll= new FilesMethods();
    }

    public void showMenu()
    {
        while (true)
        {
            System.out.println("Coffee Machine Factory");
            System.out.println("1. Display all machines(List)");
            System.out.println("2. Display all machines(Map)");
            System.out.println("3. Add new machine");
            System.out.println("4. Update machine");
            System.out.println("5. Delete machine");
            System.out.println("6. Sort machines");
            System.out.println("7. Sort machines(By ID)");
            System.out.println("8. Import from txt file");
            System.out.println("9. Export to txt file");
            System.out.println("10. Import from json file");
            System.out.println("11. Export to json file");
            System.out.println("12. Export to xml file");
            System.out.println("13. Import from xml file");
            System.out.println("0. Exit");
            System.out.print("Choose an option: ");

            int choice = IntParsing();
            switch (choice) {
                case 1:
                    coffeeList.displayAll();
                    break;
                case 2:
                    coffeeMap.displayAll();
                    break;
                case 3:
                    addMachine();
                    break;
                case 4:
                    updateMachine();
                    break;

                case 5:
                    deleteMachine();
                    break;

                case 6:
                    sortMachines();
                    break;

                case 7:
                    coffeeMap.sortMapId();
                    break;
                case 8:
                    List<CoffeeMachineNotAbstr> mach = FilesAll.importFromTxt("coffee_machines_info.txt");
                    for (CoffeeMachineNotAbstr machine : mach)
                    {
                        coffeeList.add(machine);
                        coffeeMap.add(machine);
                    }
                    break;

                case 9:
                    FilesAll.exportToTxt(coffeeList.getAll(), "coffee_machines.txt");
                    FilesAll.exportToTxt(coffeeMap.getAll(), "coffee_machinesMap.txt");
                    break;

                case 10:
                    List<CoffeeMachineNotAbstr> machJ  = FilesAll.importFromJSON("coffeeMachines.json");
                    for (CoffeeMachineNotAbstr machine : machJ)
                    {
                        coffeeList.add(machine);
                        coffeeMap.add(machine);
                    }
                    break;
                case 11:
                    FilesAll.exportToJSON(coffeeList.getAll(), "CoffeeMacinesUpdated.json");
                    FilesAll.exportToJSON(coffeeMap.getAll(), "CoffeeMacinesUpdatedMap.json");
                    break;
                case 12:
                    FilesAll.exportToXML(coffeeList.getAll(), "coffee_machines.xml");
                    FilesAll.exportToXML(coffeeMap.getAll(), "coffee_machines_map.xml");
                    break;
                case 13:
                    //ReadfromXml();
                    break;
                case 0:
                    return;

                default:
                    System.out.println("Invalid option");
            }
        }
    }


    private void addMachine()
    {
        System.out.println("Add New Coffee Machine");

        System.out.print("ID: ");
        int id = IntParsing();

        System.out.print("Type: ");
        String type = scanner.nextLine();

        System.out.print("Model: ");
        String model = scanner.nextLine();

        System.out.print("Power: ");
        int power = IntParsing();

        System.out.print("Max coffee capacity: ");
        int coffeeCap = IntParsing();

        System.out.print("Max Water Capacity: ");
        int waterCap = IntParsing();

        System.out.print("Date (dd.MM.yyyy): ");
        Date date = DateParsing();

        System.out.print("Price: ");
        double price = DoubleParsing();

        CoffeeMachineNotAbstr machine = new CoffeeMachineNotAbstr(id, type, model, power, coffeeCap, waterCap, date, price);
        coffeeList.add(machine);
        coffeeMap.add(machine);
        System.out.println("Machine added successfully.");
    }


    private void updateMachine()
    {
        System.out.print("Enter machine ID to update: ");
        int id = IntParsing();
        CoffeeMachineNotAbstr machine = coffeeMap.get(id);

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

        System.out.print("Model : ");
        String model = scanner.nextLine();
        machine.setModel(model);


        System.out.print("Power : ");
        String NewPower = scanner.nextLine();
        machine.setPower(Integer.parseInt(NewPower));


        System.out.print("Max Coffee Capacity : ");
        String NewCap = scanner.nextLine();
        machine.setMaxCoffeeCapacity(Integer.parseInt(NewCap));


        System.out.print("Max Water Capacity : ");
        String NewWater = scanner.nextLine();
        machine.setMaxWaterCapacity(Integer.parseInt(NewWater));


        System.out.print("Price : ");
        String NewPrice = scanner.nextLine();
        machine.setPrice(Double.parseDouble(NewPrice));


        coffeeList.update(machine);
        coffeeMap.add(machine);
        System.out.println("Machine updated successfully.");
    }

    private void deleteMachine()
    {
        System.out.print("Enter machine ID to delete: ");
        int id = IntParsing();
        CoffeeMachineNotAbstr machine = coffeeList.get(id);
        coffeeList.delete(id);
        coffeeMap.delete(id);
    }

    private void sortMachines()
    {
        System.out.println("Choose a way to sort");
        System.out.println("1. By Price (ascending)");
        System.out.println("2. By Price (descending)");
        System.out.println("3. By Power (ascending)");
        System.out.println("4. By Power (descending)");
        System.out.println("5. By Manufacture Date (ascending)");
        System.out.println("6. By Manufacture Date (descending)");
        System.out.print("Choose one: ");

        int sortChoice = IntParsing();
        List<CoffeeMachineNotAbstr> allMachines = coffeeList.getAll();

        switch (sortChoice) {
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
        coffeeList.clear();

        for (CoffeeMachineNotAbstr machine : allMachines)
        {
            coffeeList.add(machine);
        }
    }

    private int IntParsing()
    {
        while (true)
        {
            try
            {
                return Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.print("Invalid input. Enter a number " + e.getMessage());
            }
        }
    }

    private double DoubleParsing()
    {
        while (true)
        {
            try
            {
                return Double.parseDouble(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.print("Invalid input." + e.getMessage());
            }
        }
    }

    private Date DateParsing()
    {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        dateFormat.setLenient(false);
        while (true)
        {
            try
            {
                return dateFormat.parse(scanner.nextLine());
            } catch (ParseException e) {
                System.out.print("Invalid date format. Use dd.MM.yyyy: "+ e.getMessage());
            }
        }
    }

}