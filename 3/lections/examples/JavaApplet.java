import java.applet.Applet;
import java.awt.Graphics;

public class JavaApplet extends Applet
{
	public JavaApplet()
	{
		// конструктор
	}

	public void init()
	{
		// инициализация
	}

	public void start()
	{
		// начало или продолжение выполнения
	}

	public void paint(Graphics theGraphics)
	{
		theGraphics.drawString("Hello world", 0, 50);
	}

	public void stop()
	{

	}

	public void destroy()
	{

	}
}