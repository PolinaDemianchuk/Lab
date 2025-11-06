package classes;

import abstractclasses.AbsList;
import java.util.*;

public class CoffeeMachineMap extends AbsList<CoffeeMachineNotAbstr>
{
    private final Map<Integer, CoffeeMachineNotAbstr> machineMap = new HashMap<>();

    @Override
    public void add(CoffeeMachineNotAbstr machine) {
        machineMap.put(machine.getId(), machine);
    }

    @Override
    public CoffeeMachineNotAbstr get(int id) {
        return machineMap.get(id);
    }

    @Override
    public void update(CoffeeMachineNotAbstr updatedMachine)
    {
        machineMap.put(updatedMachine.getId(), updatedMachine);
    }

    @Override
    public void delete(int id)
    {
        machineMap.remove(id);
    }

    @Override
    public List<CoffeeMachineNotAbstr> getAll()
    {
        return new ArrayList<>(machineMap.values());
    }

    @Override
    public void displayAll() 
    {
        System.out.println(" All Coffee Machines (Map)");
        Iterator<CoffeeMachineNotAbstr> it = machineMap.values().iterator();
        while (it.hasNext())
        {
            CoffeeMachineNotAbstr machine = it.next();
            System.out.println(machine);
        }
    }

    @Override
    public void sortMapId()
    {
        System.out.println("Sorted machines(by ID)");
        SortedMap<Integer,CoffeeMachineNotAbstr> sortMap =new TreeMap <>();

    }
}