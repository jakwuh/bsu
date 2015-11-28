import java.io.*;
import java.util.Collection;
import java.util.Vector;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class EntryList extends Vector<Entry> {

    public EntryList() {};

    public void save(OutputStream fos) throws IOException {
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this);
        oos.close();
    }

    public void load(InputStream fis) throws IOException, ClassNotFoundException {
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.addAll((EntryList)ois.readObject());
    }

    public String toString(){
        String out = "Total count:" + this.elementCount + "\n";
        for (Entry entry : this) {
            out += entry.toString() + "\n";
        }
        return out;
    }

}
