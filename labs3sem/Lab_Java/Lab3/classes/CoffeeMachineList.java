package classes;

import abstractclasses.AbsList;
import abstractclasses.CoffeeMachine;
import classes.CoffeeMachineNotAbstr;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class CoffeeMachineList extends AbsList<CoffeeMachineNotAbstr>
{
    private List<CoffeeMachineNotAbstr> machines = new ArrayList<>();
    
    @Override
    public void add(CoffeeMachineNotAbstr machine)
    {
        machines.add(machine);
    }


    @Override
    public CoffeeMachineNotAbstr get(int id)
    {
        for (CoffeeMachineNotAbstr machine : machines) 
        {
            if (machine.getId() == id) 
            {
                return machine;
            }
        }
        return null;
    }

    @Override
    public void update(CoffeeMachineNotAbstr updatedMachine) 
    {
        for (int i = 0; i < machines.size(); i++) 
        {
            if (machines.get(i).getId() == updatedMachine.getId()) 
            {
                machines.set(i, updatedMachine);
                return;
            }
        }
    }

    @Override
    public void delete(int id) 
    {
        Iterator<CoffeeMachineNotAbstr> iterator = machines.iterator();
        while (iterator.hasNext()) 
        {
            if (iterator.next().getId() == id) 
            {
                iterator.remove();
                return;
            }
        }
    }

    @Override
    public List<CoffeeMachineNotAbstr> getAll() 
    {
        return new ArrayList<>(machines);
    }

    @Override
    public void displayAll() 
    {
        Iterator<CoffeeMachineNotAbstr> iterator = machines.iterator();
        System.out.println("All Coffee Machines (List)");
        while (iterator.hasNext()) 
        {
            System.out.println(iterator.next());
        }
    }
}