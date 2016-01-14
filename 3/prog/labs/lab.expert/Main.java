import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import java.util.*;

public class Main extends JPanel
implements ListSelectionListener {
    private JList list;
    private DefaultListModel listModel;
    private JTable table;
    String[] columnNames = {"Name", "Surname"};
    private DefaultTableModel dtm = new DefaultTableModel(null,columnNames);

    private static final String hireString = "add";
    private static final String fireString = "delete";
    private static final String clearString = "reset";
    private static final String isEmptyString = "size";
    private JButton clearButton;
    private JButton isEmptyButton;
    private JButton fireButton;
    private JTextField name, surname;
    private IdentityHashMap<String,String> hashMap;
    private JFrame frame;

    public Main(JFrame frame) {
        super(new BorderLayout());
        this.frame = frame;

        hashMap = new IdentityHashMap<String,String>();
        table = new JTable(dtm);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        table.setFillsViewportHeight(true);
        JScrollPane tableScrollPane = new JScrollPane(table);

        JButton hireButton = new JButton(hireString);
        HireListener hireListener = new HireListener(hireButton, hashMap, table);
        hireButton.setActionCommand(hireString);
        hireButton.addActionListener(hireListener);
        hireButton.setEnabled(false);

        fireButton = new JButton(fireString);
        fireButton.setActionCommand(fireString);
        fireButton.addActionListener(new FireListener());

        clearButton = new JButton(clearString);
        clearButton.setActionCommand(clearString);
        clearButton.addActionListener(new ClearListener());

        isEmptyButton = new JButton(isEmptyString);
        isEmptyButton.setActionCommand(isEmptyString);
        isEmptyButton.addActionListener(new IsEmptyListener());

        name = new JTextField(10);
        name.addActionListener(hireListener);
        name.getDocument().addDocumentListener(hireListener);
        surname = new JTextField(10);
        surname.addActionListener(hireListener);
        surname.getDocument().addDocumentListener(hireListener);

        JPanel buttonPane = new JPanel();
        buttonPane.setLayout(new BoxLayout(buttonPane,
            BoxLayout.LINE_AXIS));
        buttonPane.add(fireButton);
        buttonPane.add(Box.createHorizontalStrut(5));
        buttonPane.add(new JSeparator(SwingConstants.VERTICAL));
        buttonPane.add(Box.createHorizontalStrut(5));
        buttonPane.add(name);
        buttonPane.add(surname);
        buttonPane.add(hireButton);
        buttonPane.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));

        JPanel button2Pane = new JPanel();
        button2Pane.setLayout(new BoxLayout(button2Pane,
            BoxLayout.LINE_AXIS));
        button2Pane.add(clearButton);
        button2Pane.add(isEmptyButton);
        buttonPane.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));

        JPanel commonPane = new JPanel();
        commonPane.setLayout(new BoxLayout(commonPane,
            BoxLayout.PAGE_AXIS));
        commonPane.add(buttonPane);
        commonPane.add(button2Pane);
        buttonPane.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));

        add(tableScrollPane, BorderLayout.CENTER);
        add(commonPane, BorderLayout.PAGE_END);
    }

    class FireListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            int index = table.getSelectedRow();
            if (index != -1) {
                String nameStr = (String)dtm.getValueAt(index, 0);
                String surnameStr = (String)dtm.getValueAt(index, 1);
                dtm.removeRow(index);
                hashMap.remove(nameStr);
            }
        }
    }

    class ClearListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            dtm.setRowCount(0);
            hashMap.clear();
        }
    }

    class IsEmptyListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            if (hashMap.isEmpty()) {
                JOptionPane.showMessageDialog(frame, "Hash table is empty");
            } else {
                JOptionPane.showMessageDialog(frame, "Hash table contains "
                    + hashMap.size() +" elements");
            }
        }
    }

    class HireListener implements ActionListener, DocumentListener {
        private boolean alreadyEnabled = false;
        private JButton button;
        private IdentityHashMap<String,String> hashMap;
        private JTable table;

        public HireListener(JButton button, IdentityHashMap<String,String> hashMap, JTable table) {
            this.button = button;
            this.hashMap = hashMap;
            this.table = table;
        }

        public void actionPerformed(ActionEvent e) {
            String nameStr = name.getText();
            String surnameStr = surname.getText();
            System.out.println(nameStr + " " + surnameStr);

            if (nameStr.equals("") || surnameStr.equals("")
                || hashMap.containsKey(nameStr)) {
                Toolkit.getDefaultToolkit().beep();
            name.requestFocusInWindow();
            name.selectAll();
            return;
        }

        hashMap.put(nameStr, surnameStr);

        surname.requestFocusInWindow();
        surname.setText("");
        name.requestFocusInWindow();
        name.setText("");
        System.out.println(nameStr + " " + surnameStr);
        String[] tmp = new String[2];
        tmp[0] = nameStr;
        tmp[1] = surnameStr;
        dtm.addRow(tmp);
    }

    public void insertUpdate(DocumentEvent e) {
        if (!surname.getText().isEmpty() && !name.getText().isEmpty()) {
            enableButton();
        }
    }

    public void removeUpdate(DocumentEvent e) {
        handleEmptyTextField(e);
    }

    public void changedUpdate(DocumentEvent e) {
        if (!handleEmptyTextField(e)) {
            enableButton();
        }
    }

    private void enableButton() {
        if (!alreadyEnabled) {
            button.setEnabled(true);
        }
    }

    private boolean handleEmptyTextField(DocumentEvent e) {
        if (e.getDocument().getLength() <= 0) {
            button.setEnabled(false);
            alreadyEnabled = false;
            return true;
        }
        return false;
    }
}

public void valueChanged(ListSelectionEvent e) {
    if (e.getValueIsAdjusting() == false) {

        if (list.getSelectedIndex() == -1) {
            fireButton.setEnabled(false);

        } else {
            fireButton.setEnabled(true);
        }
    }
}

private static void createAndShowGUI() {
    JFrame frame = new JFrame("Main");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    JComponent newContentPane = new Main(frame);
            newContentPane.setOpaque(true);
            frame.setContentPane(newContentPane);

            frame.pack();
            frame.setVisible(true);
        }

        public static void main(String[] args) {
            javax.swing.SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                    createAndShowGUI();
                }
            });
        }

    }
