import java.io.*;
import java.time.LocalDate;

public class Entry implements Serializable{

    protected LocalDate date;
    protected int id;
    protected String description;
    protected String customer;
    protected int bill;
    protected double amount;

    public Entry(LocalDate date, int id, String description, String customer, int bill, double amount) {
        this.date = date;
        this.id = id;
        this.description = description;
        this.customer = customer;
        this.bill = bill;
        this.amount = amount;
    }

   public String toString() {
        String out = "";
        out += date + " " + id + " " + description + " " + customer + " " + bill + " " + amount;
        return out;
    }
}
