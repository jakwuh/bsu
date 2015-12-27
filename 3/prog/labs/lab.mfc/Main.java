// 12. Реализовать программу для загрузки текстового файла в главное окно 
// приложения, его редактирование и сохранение. Управление выполнением 
// операций реализовать посредством клавиатуры.

import util.Window;
import util.Settings;

import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.regex.*;
import java.util.*;
import java.io.*;
import java.util.stream.Collectors;
import javax.swing.*;

public class Main {
	
	private static Window window = null;
	private static HashMap components = new HashMap();
	private static File file = null;

	public static void main(String[] args) {
		try {
			build();
		} catch (Exception e) {
			Window.message(e.getMessage());
		}
	}

	public static void build() throws NullPointerException {
		components.clear();
		
		// Main window
		window = new Window(new Settings()
			.setHeight(430)
			.setWidth(600)
			.setName("TextEditor")
			.setMenuName("Menu")
			.setGridWidth(1)
			.setGridHeight(1));
		components.put("window", window);
		
		// About menu item
		window.addMenuItem(new Settings()
			.setName("About")
			.setListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					about();
				}
			}));

		// File menu item
		window.addMenuItem(new Settings()
			.setName("Open file")
			.setListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					try {
						open();
					} catch (Exception ex) {
						String message = null;
						if (ex.getMessage() != null && !ex.getMessage().isEmpty()) {
							message = ex.getMessage();
						} else {
							message = "Cannot parse the file";
						}
						Window.message(message);
					}
				}
			}));

		// File menu item
		window.addMenuItem(new Settings()
			.setName("Save file")
			.setListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					try {
						save();
					} catch (Exception ex) {
						String message = null;
						if (ex.getMessage() != null && !ex.getMessage().isEmpty()) {
							message = ex.getMessage();
						} else {
							message = "Cannot save the file";
						}
						Window.message(message);
					}
				}
			}));

		// Text area
		JPanel textPanel = new JPanel();
		JTextArea textArea = new JTextArea();
		textArea.addKeyListener(new KeyListener() {
			@Override
			public void keyTyped(KeyEvent e) {}

			@Override
			public void keyReleased(KeyEvent e) {}

			@Override
			public void keyPressed(KeyEvent e) {
				System.out.println(e.getKeyChar());
				if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_O) {
					try {
						open();
					} catch (Exception ex) {
						String message = null;
						if (ex.getMessage() != null && !ex.getMessage().isEmpty()) {
							message = ex.getMessage();
						} else {
							message = "Cannot parse the file";
						}
						Window.message(message);
					}
				}
				if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_S) {
					try {
						save();
					} catch (Exception ex) {
						String message = null;
						if (ex.getMessage() != null && !ex.getMessage().isEmpty()) {
							message = ex.getMessage();
						} else {
							message = "Cannot save the file";
						}
						Window.message(message);
					}
				}
			}
		});
		textArea.setEditable(true);
		textArea.setBackground(Color.decode("#EEEEEE"));
		textArea.setLineWrap (true);
		textArea.setWrapStyleWord (false);
		textPanel.setLayout(new BorderLayout());
		textPanel.add(new TextArea(), BorderLayout.CENTER);
		textPanel.add(textArea);
		textPanel.setBackground(Color.white);
		window.add(textPanel);
		components.put("textArea", textArea);

	}

	public static void about(){
		Settings settings = new Settings();
		settings
		.setHeight(200)
		.setWidth(200)
		.setName("About")
		.setGridWidth(1)
		.setGridHeight(1);
		Window about = new Window(settings);

		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);
		textArea.append("James Akwuh, 3 group, 2 course");
		about.add(textArea);
	}

	public static void open() throws IOException {
		JFileChooser fileopen = new JFileChooser();             
		int ret = fileopen.showDialog(null, "Open file");
		if (ret == JFileChooser.APPROVE_OPTION) {
			file = fileopen.getSelectedFile();
			Scanner in = new Scanner(file);
			JTextArea textArea = (JTextArea)components.get("textArea");
			textArea.setText("");
			while (in.hasNextLine()) {
				textArea.append(in.nextLine() + "\n");
			}
		}
	}

	public static void save() throws Exception {
		FileWriter fw = new FileWriter(file.getAbsoluteFile(), false);
		JTextArea textArea = (JTextArea)components.get("textArea");
		textArea.write(fw);
	}

}