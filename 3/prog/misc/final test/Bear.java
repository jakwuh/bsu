import java.io.IOException;

public class Bear extends Animal {
    public String color = null;
    public Double honey = null;

    public Bear(String in) throws IOException {
        read(in);
    }

    public void read(String line) throws IOException {
        String[] result = line.split("[|]");
        name = result[0];
        habitat = result[1];
        food = Double.valueOf(result[2]);
        image = result[3];
        color = result[4];
        honey = Double.valueOf(result[5]);
    }

    public String toString() {
        return "Bear: [" + name + "," + habitat + "," +
                food + "," + image + "," + color + "," +
                honey + "]";
    }
}
