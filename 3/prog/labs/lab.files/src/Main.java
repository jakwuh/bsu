import java.io.*;
import java.time.LocalDate;
import java.util.*;

public class Main {

    protected static EntryList entries;
    protected static Scanner sc;

    protected static boolean action(int input) throws IOException {
        int id, minIndex, maxIndex;
        double min, max;
        String str;
        Entry minEntry, maxEntry;
        EntryList temp = (EntryList)entries.clone();
        switch (input) {
            case 1:
                System.out.println("Enter customer's name:");
                str = sc.nextLine();
                temp.removeIf(entry -> !entry.customer.contains(str));
                break;
            case 2:
                System.out.println("Enter amount range (min max - 2 integers):");
                min = sc.nextInt(); max = sc.nextInt();
                temp.removeIf(e -> !(min <= e.amount && e.amount <= max));
                break;
            case 3:
                System.out.println("Enter new amount and id:");
                double amount = sc.nextDouble();
                id = sc.nextInt();
                for (Entry e : temp) if (e.id == id) e.amount = amount;
                break;
            case 4:
                System.out.println("Enter bill id:");
                id = sc.nextInt();
                temp.removeIf(entry -> entry.bill == id);
                break;
            case 5:
                minEntry = Collections.min(temp, (e1, e2) -> Double.compare(e1.amount, e2.amount));
                maxEntry = Collections.max(temp, (e1, e2) -> Double.compare(e1.amount, e2.amount));
                minIndex = temp.indexOf(minEntry);
                maxIndex = temp.indexOf(maxEntry);
                temp.set(minIndex, maxEntry);
                temp.set(maxIndex, minEntry);
                break;
            case 6:
                temp.sort((e1, e2) -> e1.date.compareTo(e2.date));
                break;
            case 7:
                return false;
        }

        saveStep(temp);
        printMenu();
        return true;
    }

    protected static void saveStep(EntryList el) throws IOException {
        FileOutputStream fos = new FileOutputStream("current.bin");
        PrintWriter pw = new PrintWriter("current.txt");
        el.save(fos);
        pw.print(el);
        System.out.print(el);
        pw.close();
        fos.close();
    }

    protected static void printMenu() {
        System.out.println("Choose the action:");
        System.out.println("[1] - Filter by customer");
        System.out.println("[2] - Filter by amount range");
        System.out.println("[3] - Change amount by id");
        System.out.println("[4] - Remove entries by bill");
        System.out.println("[5] - Swap max & min entries");
        System.out.println("[6] - Sort by date");
        System.out.println("[7] - Exit\n");
    }

    public static void generateData() throws IOException {
        EntryList temp = new EntryList();
        temp.add(new Entry(LocalDate.of(2013, 11, 13), 2733, "Безвозмездная спонсорская помощь", "СООО \"Саммит технологиз\"", 176, 8000000));
        temp.add(new Entry(LocalDate.of(2013, 11, 27), 2788, "Возврат неиспользуемой суммы", "СООО \"Саммит технологиз\"", 176, -120128));
        temp.add(new Entry(LocalDate.of(2013, 8, 16), 6677, "За выполнение НИР по договору ", "Институт физико-органической химии", 232, 12660000));
        temp.add(new Entry(LocalDate.of(2013, 5, 9), 6678, "Аванс на выполнение НИР", "Институт физико-органической химии", 232, 19000000));
        temp.add(new Entry(LocalDate.of(2014, 11, 1), 237, "Проведение испытаний на пожарную опасность", "ООО “Тритекс трейд”", 155, 4572000));
        temp.add(new Entry(LocalDate.of(2013, 12, 5), 2111, "Проведение биоаналитических биостатических опытов", "ГП \"Академфарм\"", 155, 89000000));
        temp.add(new Entry(LocalDate.of(2013, 12, 2), 8189, "Проведение испытаний гранул древесных гранул", "УП “Брестоблгаз”", 155, 4572000));
        FileOutputStream fos = new FileOutputStream("current.bin");
        temp.save(fos);
        fos.close();
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        Locale.setDefault(new Locale("ru", "RU"));
        generateData();
        printMenu();

        entries = new EntryList();
        sc = new Scanner(System.in);
        FileInputStream in = new FileInputStream("default.bin");
        entries.load(in);
        in.close();

        while (true) {
            int input = sc.nextInt();
            sc.nextLine();
            if (!action(input)) break;
        }
    }
}
