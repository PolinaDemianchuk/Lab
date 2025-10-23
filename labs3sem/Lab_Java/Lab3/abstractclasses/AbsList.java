package abstractclasses;

import java.util.List;

public abstract class AbsList<T>
{
    public abstract void add(T item);
    public abstract T get(int id);
    public abstract void update(T item);
    public abstract void delete(int id);
    public abstract List<T> getAll();
    public abstract void displayAll();
}