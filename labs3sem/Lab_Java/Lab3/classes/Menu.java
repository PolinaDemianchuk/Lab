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


public class Menu
{
    private Scanner scanner;
    private AbsList<CoffeeMachineNotAbstr> coffeeList;
    private AbsList<CoffeeMachineNotAbstr> coffeeMap;

    public Menu(AbsList<CoffeeMachineNotAbstr> coffeeList, AbsList<CoffeeMachineNotAbstr> coffeeMap)
    {
        this.scanner = new Scanner(System.in);
        this.coffeeList = coffeeList;
        this.coffeeMap = coffeeMap;
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
                    readFile();
                    break;

                case 9:
                    writeFile();
                    break;

                case 10:
                    importFromJSON();
                    break;
                case 11:
                    writeToJSON();
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

        for (CoffeeMachineNotAbstr machine : allMachines) {
            coffeeList.add(machine);
        }

        for (CoffeeMachineNotAbstr machine : allMachines)
        {
            coffeeMap.add(machine);
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

    private void writeFile()
    {
        try (FileWriter writer = new FileWriter("coffee_machines.txt"))
        {
            List<CoffeeMachineNotAbstr> allMachines = coffeeList.getAll();
            Iterator<CoffeeMachineNotAbstr> it = allMachines.iterator();
            while (it.hasNext()) {
                CoffeeMachineNotAbstr machine = it.next();
                writer.write(machine.getId() + " || " +
                        machine.getType() + " || " +
                        machine.getModel() + " || " +
                        machine.getPower() + " || " +
                        machine.getMaxCoffeeCapacity() + " || " +
                        machine.getMaxWaterCapacity() + " || " +
                        new SimpleDateFormat("dd.MM.yyyy").format(machine.getManufactureDate()) + " || " +
                        machine.getPrice() + "\n");
            }
            System.out.println("Saved " + allMachines.size() + " machines to coffee_machines.txt");
        } catch (IOException e)
        {
            System.out.println("Error saving file: " + e.getMessage());
        }

        try (FileWriter writer = new FileWriter("coffee_machinesMap.txt"))
        {
            List<CoffeeMachineNotAbstr> allMachinesMap = coffeeMap.getAll();
            Iterator<CoffeeMachineNotAbstr> itM = allMachinesMap.iterator();
            while (itM.hasNext())
            {
                CoffeeMachineNotAbstr machine = itM.next();
                writer.write(machine.getId() + " || " +
                        machine.getType() + " || " +
                        machine.getModel() + " || " +
                        machine.getPower() + " || " +
                        machine.getMaxCoffeeCapacity() + " || " +
                        machine.getMaxWaterCapacity() + " || " +
                        new SimpleDateFormat("dd.MM.yyyy").format(machine.getManufactureDate()) + " || " +
                        machine.getPrice() + "\n");
            }
            System.out.println("Saved " + allMachinesMap.size() + " machines to coffee_machines.txt");
        }
        catch (IOException e)
        {
            System.out.println("Error saving file: " + e.getMessage());
        }
    }

    private void readFile()
    {
        try (Scanner fileScanner = new Scanner(new FileReader("coffee_machines_info.txt")))
        {
            SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");

            while (fileScanner.hasNextLine())
            {
                String line = fileScanner.nextLine();
                if (line.isEmpty()) continue;

                String[] elems = line.split(",");
                if (elems.length == 8)
                {
                    try
                    {
                        int id = Integer.parseInt(elems[0]);
                        String type = elems[1];
                        String model = elems[2];
                        int power = Integer.parseInt(elems[3]);
                        int coffeeCap = Integer.parseInt(elems[4]);
                        int waterCap = Integer.parseInt(elems[5]);
                        Date date = dateFormat.parse(elems[6]);
                        double price = Double.parseDouble(elems[7]);

                        CoffeeMachineNotAbstr machine = new CoffeeMachineNotAbstr(
                                id, type, model, power, coffeeCap, waterCap, date, price);
                        coffeeList.add(machine);
                        coffeeMap.add(machine);

                    } catch (Exception e)
                    {
                        System.out.println("Error parsing line" + e.getMessage());
                    }
                }
            }
            System.out.println("Loaded machines from file");

        }
        catch (IOException e)
        {
            System.out.println("Error loading file " + e.getMessage());
        }
    }

    private void importFromJSON()
    {
        String path = "coffeeMachines.json";

        try
        {
            JSONParser parser = new JSONParser();
            Object obj = parser.parse(new FileReader(path));
            JSONObject JsonFile = (JSONObject) obj;
            JSONArray machinesArray = (JSONArray) JsonFile.get("coffeeMachines");
            int count = 0;

            Iterator<Object> it = machinesArray.iterator();
            while (it.hasNext())
            {
                Object item = it.next();
                JSONObject machineJson = (JSONObject) item;

                try
                {
                    int id = Integer.parseInt(machineJson.get("id").toString());
                    String type = (String) machineJson.get("type");
                    String model = (String) machineJson.get("model");
                    int power = Integer.parseInt(machineJson.get("power").toString());
                    int maxCoffeeCapacity = Integer.parseInt(machineJson.get("maxCoffeeCapacity").toString());
                    int maxWaterCapacity = Integer.parseInt(machineJson.get("maxWaterCapacity").toString());
                    String dateStr = (String) machineJson.get("Created");
                    double price = Double.parseDouble(machineJson.get("price").toString());

                    Date manufactureDate = new SimpleDateFormat("dd.MM.yyyy").parse(dateStr);

                    CoffeeMachineNotAbstr machine = new CoffeeMachineNotAbstr(
                            id, type, model, power, maxCoffeeCapacity, maxWaterCapacity, manufactureDate, price);
                    coffeeList.add(machine);
                    coffeeMap.add(machine);
                    count++;

                } catch (Exception e) {
                    System.out.println("Error parsing machine from JSON: " + e.getMessage());
                }
            }

            System.out.println("Imported " + count + " machines from " + path);

        } catch (Exception e)
        {
            System.out.println("Error importing from JSON: " + e.getMessage());
        }
    }

    private void writeToJSON()
    {
        String pathList = "CoffeeMacinesUpdated.json";
        String pathMap = "CoffeeMacinesUpdatedMap.json";

        try
        {
            JSONArray machinesArray = new JSONArray();
            List<CoffeeMachineNotAbstr> allMachinesList = coffeeList.getAll();
            List<CoffeeMachineNotAbstr> allMachinesMap = coffeeMap.getAll();

            Iterator<CoffeeMachineNotAbstr> it = allMachinesList.iterator();

            while (it.hasNext())
            {
                CoffeeMachineNotAbstr machine = it.next();
                JSONObject machineJson = new JSONObject();
                machineJson.put("id", machine.getId());
                machineJson.put("type", machine.getType());
                machineJson.put("model", machine.getModel());
                machineJson.put("power", machine.getPower());
                machineJson.put("maxCoffeeCapacity", machine.getMaxCoffeeCapacity());
                machineJson.put("maxWaterCapacity", machine.getMaxWaterCapacity());
                machineJson.put("Created", new SimpleDateFormat("dd.MM.yyyy").format(machine.getManufactureDate()));
                machineJson.put("price", machine.getPrice());

                machinesArray.add(machineJson);
            }

            JSONObject j = new JSONObject();
            j.put("coffeeMachines", machinesArray);

            try (PrintWriter out = new PrintWriter(new FileWriter(pathList)))
            {
                out.write(j.toString());
                System.out.println("Exported " + allMachinesList.size() + " machines to " + pathList);
            }

        }
        catch (Exception e)
        {
            System.out.println("Error exporting to JSON: " + e.getMessage());
        }

        JSONArray mapArray = new JSONArray();
        List<CoffeeMachineNotAbstr> allMachinesMap = coffeeMap.getAll();
        Iterator<CoffeeMachineNotAbstr> itM = allMachinesMap.iterator();

        while (itM.hasNext())
        {
            CoffeeMachineNotAbstr machine = itM.next();
            JSONObject machineJson = new JSONObject();
            machineJson.put("id", machine.getId());
            machineJson.put("type", machine.getType());
            machineJson.put("model", machine.getModel());
            machineJson.put("power", machine.getPower());
            machineJson.put("maxCoffeeCapacity", machine.getMaxCoffeeCapacity());
            machineJson.put("maxWaterCapacity", machine.getMaxWaterCapacity());
            machineJson.put("created", new SimpleDateFormat("dd.MM.yyyy").format(machine.getManufactureDate()));
            machineJson.put("price", machine.getPrice());
            mapArray.add(machineJson);
        }

        JSONObject mapJson = new JSONObject();
        mapJson.put("coffeeMachines", mapArray);

        try (PrintWriter out = new PrintWriter(new FileWriter(pathMap)))
        {
            out.write(mapJson.toJSONString());
            System.out.println("Exported " + allMachinesMap.size() + " machines from MAP to " + pathMap);
        }
        catch(Exception e)
    {
        System.out.println("Error exporting to JSON: " + e.getMessage());
    }
    }


}