// This file is used by BuildBindings.py to generate LUA bindings

void flip();
void clip(int x, int y, int w, int h);
void color(int value);
void colorcount(int value);
void colortable(int index, int r, int g, int b);
void cls();
void camera(int x, int y);
void rect(int x, int y, int w, int h);
void rectfill(int x, int y, int w, int h);
void memsize(int size);
void memload(int offset, const void* src, int size);
void bmpload(int offset, int stride, int bits, int shift, const void* src, int sizex, int sizey);
void sprsheet(int offset, int bits, int shift, int sizex, int sizey, int countx, int county);
void spr(int n, int x, int y, int w, int h, bool flip_x = false, bool flip_y = false);
