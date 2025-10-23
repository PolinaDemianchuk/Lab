package classes;

import abstractclasses.AbsList;
import classes.CoffeeMachineNotAbstr;
import java.util.*;

public class CoffeeMachineMap extends AbsList<CoffeeMachineNotAbstr>
{
    private Map<Integer, CoffeeMachineNotAbstr> machineMap = new HashMap<>();

    @Override
    public void add(CoffeeMachineNotAbstr machine) {
        machineMap.put(machine.getId(), machine);
    }

    @Override
    public CoffeeMachineNotAbstr get(int id) {
        return machineMap.get(id);
    }

    @Override
    public void update(CoffeeMachineNotAbstr updatedMachine) {
        machineMap.put(updatedMachine.getId(), updatedMachine);
    }

    @Override
    public void delete(int id) {
        machineMap.remove(id);
    }

    @Override
    public List<CoffeeMachineNotAbstr> getAll() {
        return new ArrayList<>(machineMap.values());
    }

    @Override
    public void displayAll() 
    {
        System.out.println(" All Coffee Machines (Map)");
        for (CoffeeMachineNotAbstr machine : machineMap.values()) 
        {
            System.out.println(machine);
        }
    }
    public void displayAllSortedById()
    {
        System.out.println("All Coffee Machines (Sorted Map by ID)");
        TreeMap<Integer, CoffeeMachineNotAbstr> sortedMap = new TreeMap<>(machineMap);
        for (CoffeeMachineNotAbstr machine : sortedMap.values())
        {
            System.out.println(machine);
        }
    }
}