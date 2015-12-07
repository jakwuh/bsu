import java.io.*;
import java.io.DataInputStream;
import java.io.IOException;
import java.lang.Integer;
import java.time.LocalDate;

public class Entry implements Serializable{

    protected int id;
    protected int bill;
    protected double amount;
    protected LocalDate date;
    protected String customer;
    protected String description;

    public Entry(DataInputStream in) {
        read(in);
    }

    public Entry(Line in) {
        fromString(in);
    }

    public Entry(int id, int bill,double amount, LocalDate date, String customer, String description) {
        this.id = id;
        this.bill = bill;
        this.amount = amount;
        this.date = date;
        this.customer = customer;
        this.description = description;
    }

    public void write(DataOutputStream out) throws IOException{
        out.writeInt(id);
        out.writeInt(bill);
        out.writeDouble(amount);
        out.writeUTF(date.toString());
        out.writeUTF(customer);
        out.writeUTF(description);
    }

    public void read(DataInputStream in) {
        id = in.readInt();
        bill = in.readInt();
        amount = in.readDouble();
        date = LocalDate.parse(in.readUTF);
        customer = in.readUTF();
        description = in.readUTF();
    }

    public void fromString(String line) {
        String[] result = line.split("|");
        id = Integer.valueOf(result[0]);
        bill = Integer.valueOf(result[1);
        amount = Double.valueOf(result[2]);
        date = LocalDate.parse(result[3]);
        customer = result[4];
        description = result[5];
    }

    public String toString() {
        String out = "";
        out.concat(id).concat("|");
        out.concat(bill).concat("|");
        out.concat(amount).concat("|");
        out.concat(date).concat("|");
        out.concat(customer).concat("|");
        out.concat(description);
        return out;
    }
}
