package abstractclasses;

import java.util.Date;

public abstract class CoffeeMachine 
{
    protected int id;
    protected String type;
    protected String model;
    protected int power;
    protected int maxCoffeeCapacity;
    protected int maxWaterCapacity;
    protected Date manufactureDate;
    protected double price;

    public abstract int getId();
    public abstract String getType();
    public abstract String getModel();
    public abstract int getPower();
    public abstract int getMaxCoffeeCapacity();
    public abstract int getMaxWaterCapacity();
    public abstract Date getManufactureDate();
    public abstract double getPrice();
    
    public abstract void setId(int id);
    public abstract void setType(String type);
    public abstract void setModel(String model);
    public abstract void setPower(int power);
    public abstract void setMaxCoffeeCapacity(int maxCoffeeCapacity);
    public abstract void setMaxWaterCapacity(int maxWaterCapacity);
    public abstract void setManufactureDate(Date manufactureDate);
    public abstract void setPrice(double price);

    @Override
    public abstract String toString();
}