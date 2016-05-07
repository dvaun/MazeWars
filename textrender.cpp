#ifndef TEXT_RENDER
#define TEXT_RENDER

void drawBlackNum(float x, float y, float offsetx, float offsety, float printvalue)
{
	Rect r;
	std::string s;
	char const *c;
	r.center = 0;
	r.bot = x + offsety;
	r.left = y + offsetx;
	s = std::to_string(printvalue);
	c = s.c_str();
	ggprint8b(&r, 0, 0, "%s", c);
}
void drawWhiteNum(float x, float y, float offsetx, float offsety, float printvalue)
{
	Rect r;
	std::string s;
	char const *c;
	r.center = 0;
	r.bot = x + offsety;
	r.left = y + offsetx;
	s = std::to_string(printvalue);
	c = s.c_str();
	ggprint8b(&r, 0x00ffffff, 0, "%s", c);
}
#endif