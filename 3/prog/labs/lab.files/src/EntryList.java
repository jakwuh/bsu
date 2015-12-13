import java.io.*;
import java.io.IOException;
import java.util.Collection;
import java.util.Vector;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.time.LocalDate;

public class EntryList extends Vector<Entry> {

    public EntryList() {};

    public String toString(){
        String out = "";
        for (int i = 0; i < this.size(); ++i) {
            out += this.elementAt(i) + (i == this.size() - 1 ? "" : "\n");
        }
        return out;
    }

    public void toFile(BufferedWriter out) throws IOException {
        out.write(this.toString());
        out.flush();
    }

    public void fromFile(BufferedReader in) throws IOException {
        this.clear();
        String line;
        while ((line = in.readLine()) != null) {
            this.add(new Entry(line));
        }
    }

    public void toStream(DataOutputStream out) throws IOException {
        for (Entry entry : this) entry.write(out);
    }
    
    public void fromStream(DataInputStream in) throws IOException {
        this.clear();
        while (in.available() != 0) {
            this.add(new Entry(in));
        }
    }

    public static void generateDefaultData(BufferedWriter out) throws IOException {
        EntryList temp = new EntryList();
        temp.add(new Entry(2733, 176, 8000000, LocalDate.of(2013, 11, 13), "СООО \"Саммит технологиз\"", "Безвозмездная спонсорская помощь"));
        temp.add(new Entry(2788, 176, -120128, LocalDate.of(2013, 11, 27), "СООО \"Саммит технологиз\"", "Возврат неиспользуемой суммы"));
        temp.add(new Entry(6677, 232, 12660000, LocalDate.of(2013, 8, 16), "Институт физико-органической химии", "За выполнение НИР по договору "));
        temp.add(new Entry(6678, 232, 19000000, LocalDate.of(2013, 5, 9), "Институт физико-органической химии", "Аванс на выполнение НИР"));
        temp.add(new Entry(237, 155, 4572000, LocalDate.of(2014, 11, 1), "ООО “Тритекс трейд”", "Проведение испытаний на пожарную опасность"));
        temp.add(new Entry(2111, 155, 89000000, LocalDate.of(2013, 12, 5), "ГП \"Академфарм\"","Проведение биоаналитических биостатических опытов"));
        temp.add(new Entry(8189, 155, 4572000, LocalDate.of(2013, 12, 2), "УП “Брестоблгаз”", "Проведение испытаний гранул древесных гранул"));
        temp.toFile(out);
    }

}
