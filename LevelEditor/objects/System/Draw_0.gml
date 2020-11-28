#region GRID
var scl = Camera.view_scale;
var vlines = floor(Camera.view_width * scl / PPU) + 2;
var hlines = floor(Camera.view_height * scl / PPU) + 2;

var start = snap(Camera.view_x);
var yy1 = Camera.view_y - 1;
var yy2 = yy1 + Camera.view_height * scl;
var col = Grey(100);
for (var i = 0; i < vlines; ++i) {
	var xx = start + i * PPU - 1;
    draw_line_width_color(xx, yy1, xx, yy2, .5 * scl, col, col);
}

var start = snap(Camera.view_y);
var xx1 = Camera.view_x - 1;
var xx2 = xx1 + Camera.view_width * scl;
var col = Grey(100);
for (var i = 0; i < hlines; ++i) {
	var yy = start + i * PPU -1;
    draw_line_width_color(xx1, yy, xx2, yy, .4 * scl, col, col);
}

draw_line_width_color(Camera.view_x - 1, -1, Camera.view_x + Camera.view_width * scl - 1, -1, .5*scl, make_color_rgb(0, 153, 255), make_color_rgb(0, 153, 255));
draw_line_width_color(-1, Camera.view_y - 1, -1, Camera.view_y + Camera.view_height * scl - 1, .5*scl, c_red, c_red);
#endregion

var fact = Camera.view_width / window_get_width();
var mx = Camera.view_x + window_mouse_get_x() * fact * scl;
var my = Camera.view_y + window_mouse_get_y() * fact * scl;

for (var i = 0; i < ds_list_size(level); ++i) {
	var e = level[|i];
    draw_sprite_ext(SPRITE[e.type], 0, e.x, e.y, e.xscale, e.yscale, 0, c_white, 1);
}

if ( keyboard_check(vk_alt) ) {
	draw_sprite_ext(spr_ground, 0, snap(mx), snap(my), 1, 1,0,Grey(150), 1);
}

if (selected != -1) {
	var x1 = selected.x - 1;
	var y1 = selected.y - 1;
	var x2 = x1 + PPU * selected.xscale;
	var y2 = y1 + PPU * selected.yscale;
	var col = make_color_rgb(151, 0, 51);
	draw_line_width_color(x1, y1, x1, y2, .5*scl, col, col);
	draw_line_width_color(x2, y1, x2, y2, .5*scl, col, col);
	draw_line_width_color(x1, y1, x2, y1, .5*scl, col, col);
	draw_line_width_color(x1, y2, x2, y2, .5*scl, col, col);
	draw_circle_color(x1, y1, .1, col, col, false);
	draw_circle_color(x1, y2, .1, col, col, false);
	draw_circle_color(x2, y1, .1, col, col, false);
	draw_circle_color(x2, y2, .1, col, col, false);
	x1 ++;	y1 ++;	x2 ++;	y2 ++;
	
	var col2 = make_color_rgb(255, 0, 102);
	var margin = 3;
	var xmar = margin*sign(selected.xscale);
	var ymar = margin*sign(selected.yscale);
	draw_rectangle_color(x1, y1, x1 + xmar - 1,	y1 + ymar - 1,	col2, col2, col2, col2, false);
	draw_rectangle_color(x1, y1, x1 + xmar - 1,	y1 + ymar - 1,	col, col, col, col, true);
	draw_rectangle_color(x2, y1, x2 - xmar - 1,	y1 + ymar - 1,	col2, col2, col2, col2, false);
	draw_rectangle_color(x2, y1, x2 - xmar - 1,	y1 + ymar - 1,	col, col, col, col, true);
	draw_rectangle_color(x2, y2, x2 - xmar - 1,	y2 - ymar - 1,	col2, col2, col2, col2, false);
	draw_rectangle_color(x2, y2, x2 - xmar - 1,	y2 - ymar - 1,	col, col, col, col, true);
	draw_rectangle_color(x1, y2, x1 + xmar - 1,	y2 - ymar - 1,	col2, col2, col2, col2, false);
	draw_rectangle_color(x1, y2, x1 + xmar - 1,	y2 - ymar - 1,	col, col, col, col, true);
}