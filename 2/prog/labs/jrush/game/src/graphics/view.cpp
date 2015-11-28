#include "view.h"
#undef min

View::View(HWND _hwnd, LPTSTR path, Position _position) : hwnd(_hwnd), position(_position)
{
    bitmap = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    BITMAP bm;
    ::GetObject(bitmap, sizeof(bm), &bm);
    bitmap_width = bm.bmWidth;
    bitmap_height = bm.bmHeight;
    hdc = GetDC(hwnd);
    hdc_mem = CreateCompatibleDC(hdc);

    resize();
}

View::~View()
{
    ReleaseDC(hwnd, hdc_mem);
    ReleaseDC(hwnd, hdc);
    DeleteDC(hdc_mem);
    DeleteDC(hdc);
}

void View::draw()
{
    move(player->getX(), player->getY());

    SelectClipRgn(hdc, region);
    SelectObject(hdc, ::pens::map["null"]);

    BitBlt(hdc, xd, yd, w, h, hdc_mem, xs, ys, SRCCOPY);

	SelectObject(hdc, ::fonts::town_text);
    Town* tmp_town;
    for (Towns::iterator it = towns.begin(); it != towns.end(); ++it) {
        tmp_town = (Town*)*it;

        if (tmp_town->getHoster())
            SelectObject(hdc, ::brushes::map[tmp_town->getHoster()->getColor()]);
        else
            SelectObject(hdc, ::brushes::map[::colors::default_color]);

        tmp_town->draw(hdc, xd - xs, yd - ys);
    }

    RECT rect;
    SetRect(&rect, xd, 0, xd + w, ::config::bar_height);
    FillRect(hdc, &rect, ::brushes::map[::colors::menu_background]);
    SelectObject(hdc, ::fonts::status_text);
    
    DrawText(hdc, player->getDescription().c_str(), -1, &rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER);

    if (player) {
        SelectObject(hdc, ::brushes::map[player->getColor()]);    
        player->draw(hdc, xd - xs, yd - ys);
    }


    HGDIOBJ old = SelectObject(hdc_mem, bitmap);
}

void View::move(int x, int y)
{
    int nxs = x - w / 2;
    int nys = y - h / 2;

    if (nxs >= max_xs) nxs = max_xs;
    if (nys >= max_ys) nys = max_ys;
    if (nxs < 0) nxs = 0;
    if (nys < 0) nys = 0;

    if (nxs != xs || nys != ys)
    {
        int rr = std::sqr(nxs - xs) + std::sqr(nys - ys);
        if (rr < std::sqr(::config::view_speed)) {
            xs = nxs;
            ys = nys;
        } else {
            xs += (int) ( (nxs - xs) / std::sqrt(rr) * ::config::view_speed );
            ys += (int) ( (nys - ys) / std::sqrt(rr) * ::config::view_speed );
        }
    }
}

void View::setPlayer(Player* _player)
{
    player = _player;
}

void View::setTowns(Towns _towns)
{   
    towns = _towns;
}

void View::resize()
{
    RECT r;
    GetClientRect(hwnd, &r);
    width = ( r.right - r.left ) / 2;
    height = r.bottom - r.top - ::config::bar_height;
    w = std::min(width, bitmap_width);
    h = std::min(height, bitmap_height);
    max_xs = bitmap_width - w;
    max_ys = bitmap_height - h;

	yd = ::config::bar_height + (bitmap_height < height ? (height - h) / 2 : 0);
	xd = (bitmap_width < width ? (width - w) / 2 : 0);

	xs = ys = 0;

    if (position == Position::left) {
        region = CreateRectRgn(0, 0, w, yd + h);
    } else {
        region = CreateRectRgn(w, 0, 2 * w, yd + h);
        xd += w;
    }
}