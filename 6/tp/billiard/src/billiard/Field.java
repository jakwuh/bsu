package billiard;

public class Field {
    
    public int x, y, w, h;      //положение, длина и высота
    public Ball[] balls;        //шары на поле
    public Pocket[] pockets;    //лузы
    private Frame frame;        //форма для отображения
    
    public Field()
    {
        x = 60;
        y = 80;
        w = 300;
        h = 200;
        AddPockets();
        AddBalls();
        frame = new Frame(this);
    }
    
    private void AddPockets()
    {
        pockets = new Pocket[6];
        for (int i = 0; i < 6; i++)
        {
            int _x = (i / 2)*(w/2) + x, _y = i % 2 == 0 ? y : y + h;
            pockets[i] = new Pocket(_x, _y);
        }
    }
    
    private void AddBalls()
    {
        balls = new Ball[16];
        balls[0] = new Ball(x + w/2 + 50, y + h/2);
        int r = balls[0].r, count = 1;
        for (int i = 0; i < 5; i++)
        {
            int st_h = y + h/2 - i*r, _w = x + w/2 - 2*r*i;
            for (int j = 0; j <= i; j++)
            {
                balls[count] = new Ball(_w, st_h+j*2*r);
                count++;
            }
        }
    }
}
