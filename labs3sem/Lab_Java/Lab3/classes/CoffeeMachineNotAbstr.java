package classes;

import abstractclasses.CoffeeMachine;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CoffeeMachineNotAbstr extends CoffeeMachine
{
    private int id;
    private String type;
    private String model;
    private int power;
    private int maxCoffeeCapacity;
    private int maxWaterCapacity;
    private Date manufactureDate;
    private double price;

    public CoffeeMachineNotAbstr(int id, String type, String model, int power,
                                 int maxCoffeeCapacity, int maxWaterCapacity,
                                 Date manufactureDate, double price)
    {
        this.id = id;
        this.type = type;
        this.model = model;
        this.power = power;
        this.maxCoffeeCapacity = maxCoffeeCapacity;
        this.maxWaterCapacity = maxWaterCapacity;
        this.manufactureDate = manufactureDate;
        this.price = price;
    }


    @Override
    public int getId() {
        return id;
    }

    @Override
    public String getType() {
        return type;
    }

    @Override
    public String getModel() {
        return model;
    }

    @Override
    public int getPower() {
        return power;
    }

    @Override
    public int getMaxCoffeeCapacity() {
        return maxCoffeeCapacity;
    }

    @Override
    public int getMaxWaterCapacity() {
        return maxWaterCapacity;
    }

    @Override
    public Date getManufactureDate() {
        return manufactureDate;
    }

    @Override
    public double getPrice() {
        return price;
    }

    @Override
    public void setId(int id) {
        this.id=id;
    }

    @Override
    public void setType(String type) {
        this.type = type;

    }

    @Override
    public void setModel(String model) {
        this.model = model;
    }

    @Override
    public void setPower(int power) {
        this.power = power;

    }

    @Override
    public void setMaxCoffeeCapacity(int maxCoffeeCapacity) {
        this.maxCoffeeCapacity = maxCoffeeCapacity;
    }

    @Override
    public void setMaxWaterCapacity(int maxWaterCapacity) {
        this.maxWaterCapacity = maxWaterCapacity;
    }

    @Override
    public void setManufactureDate(Date manufactureDate) {
           this.manufactureDate=manufactureDate;
    }

    @Override
    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public String toString() 
    {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        return String.format("ID: %d || Type: %s || Model: %s || Power: %d || Coffee cap: %d || Water cap: %d || Created: %s || Price: $%.2f",
                id, type, model, power, maxCoffeeCapacity, maxWaterCapacity, dateFormat.format(manufactureDate), price);
    }
}
