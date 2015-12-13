import java.io.*;
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

    protected static void saveStep(EntryList entries) throws IOException {
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream("out.txt"), "UTF-8"));
        entries.toStream(new DataOutputStream(new FileOutputStream("out.bin")));
        entries.toFile(out);
        System.out.print(entries);
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

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        printMenu();

        entries = new EntryList();
        BufferedReader in = new BufferedReader(new InputStreamReader(
            new FileInputStream("in.txt"), "UTF8"));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream("in.txt"), "UTF-8"));
        entries.generateDefaultData(out);
        entries.fromFile(in);
        entries.toStream(new DataOutputStream(new FileOutputStream("in.bin")));
        entries.fromStream(new DataInputStream(new FileInputStream("in.bin")));

        sc = new Scanner(System.in);

        while (true) {
            int input = sc.nextInt();
            sc.nextLine();
            if (!action(input)) break;
        }
    }
}
