import java.io.IOException;

public class Elk extends Animal {
    public String horns = null;

    public Elk(String in) throws IOException {
        read(in);
    }

    public void read(String line) throws IOException {
        String[] result = line.split("[|]");
        name = result[0];
        habitat = result[1];
        food = Double.valueOf(result[2]);
        image = result[3];
        horns = result[4];
    }

    public String toString() {
        return "Elk: [" + name + "," + habitat + "," +
                food + "," + image + "," + horns + "]";
    }
}
