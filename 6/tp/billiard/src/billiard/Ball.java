package billiard;

import static java.lang.Math.*;


public class Ball {
    
    public int x, y, r = 9;
    public float energy, angle;
    private int speed = 2;
    
    
    public Ball(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    
    public void HitBall(float sp, float an)
    {
        energy = sp;
        angle = an;
        speed = 2 + (int)sp;
    }
    
    public void Refresh()
    {
        if (energy > 0)
        {
            energy -= 0.0125f;
            x += (int)(speed*cos(angle));
            y += (int)(speed*sin(angle));
        }
    }
    
    public void BounceWall(int x, int y, int w, int h)
    {
        for (double t = 0; t <2*PI+0.1; t+=0.1)
        {
            int _x = this.x + (int)(r*cos(t)), _y = this.y + (int)(r*sin(t));
            if (_x <= x || _x >= x+w)
            {
                angle = (float)PI - angle;
                this.x += _x <= x ? 1 : -1;
                break;
            }
            else if (_y <= y || _y >= y+h)
            {
                angle = (float)PI*2 - angle;
                this.y += _y <= y ? 1 : -1;
                break; 
            }
        }
    }
    
    public void BounceBall(Ball b)
    {
        int _x = b.x, _y = b.y;
        for (double t1 = 0; t1 <2*PI+0.1; t1+=0.1)
        {
            boolean isCollided = false;
            for (double t2 = 0; t2 <2*PI+0.1; t2+=0.1)
            {
                int x1 = this.x + (int)(r*cos(t2)), x2 = _x + (int)(r*cos(t1)),
                        y1 = this.y + (int)(r*sin(t2)), y2 = _y + (int)(r*sin(t1));
                if (x1 == x2 && y1 == y2)
                {
                    isCollided = true;
                    float _a = angle;
                    angle = (angle + (float)t2)/2;
                    b.angle = (float)(PI + t1);
                    if (_a >= angle-0.1f && _a <= angle+0.1f)
                    {
                        b.energy = energy / 7 * 8;
                        energy /= 8;
                    }
                    else 
                    {
                        energy /= 2;
                        b.energy = energy;
                    }
                    b.Refresh();
                    break;
                }
            }
            if (isCollided)
                break;
        }
    }
    
    public boolean HitInPocket(Pocket p)
    {
        int _x = p.x - x, _y = p.y - y, _r = p.r - r + 1;
        if (sqrt(_x*_x+_y*_y) <= _r)
        {
            x = 0;
            y = 0;
            r = 0;
            return true;   
        }
        return false;
    }
    
    public boolean IsNearTo(Ball b)
    {
        int _x = b.x, _y = b.y;
        if (sqrt((x-_x)*(x-_x)+(y-_y)+(y-_y)) <= 2*r)
            return true;
        return false;
    }
}
