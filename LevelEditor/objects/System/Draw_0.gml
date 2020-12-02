#region Camera stuff

	var vx = Camera.view_x - 1;
	var vy = Camera.view_y - 1;
	var scl = Camera.view_scale;
	var vw = Camera.view_width * scl;
	var vh = Camera.view_height * scl;
	var fact = vw / window_get_width();

#endregion

#region Input

	var mx = vx + window_mouse_get_x() * fact;
	var my = vy + window_mouse_get_y() * fact;
	var smx = Snap(mx);
	var smy = Snap(my);
	//var imx = smx / PPU;
	//var imy = smy / PPU;
	var alt = keyboard_check(vk_alt);

#endregion

#region GRID

	// Vertical lines of the grid
	var vlines = floor(vw/ PPU) + 2;
	var start = Snap(vx);
	var yy1 = vy;
	var yy2 = yy1 + vh;
	var col = Grey(100);
	for (var i = 0; i < vlines; ++i) {
		var xx = start + i * PPU;
	    draw_line_width_color(xx, yy1, xx, yy2, .5 * scl, col, col);
	}

	// Horizontal lines of the grid
	var hlines = floor(vh/ PPU) + 2;
	var start = Snap(vy);
	var xx1 = vx;
	var xx2 = xx1 + vw;
	var col = Grey(100);
	for (var i = 0; i < hlines; ++i) {
		var yy = start + i * PPU;
	    draw_line_width_color(xx1, yy, xx2, yy, .4 * scl, col, col);
	}

	// X and Y axis
	draw_line_width_color(vx, 0, vx + vw, 0, .5*scl, make_color_rgb(0, 153, 255), make_color_rgb(0, 153, 255));
	draw_line_width_color(0, vy, 0, vy + vh, .5*scl, c_red, c_red);
	
#endregion

#region Level drawing
	// Drawing of every entity
	for (var i = 0; i < ds_list_size(level); ++i) {
		var e = level[|i];
	    Sprite(e.type, 0, e.xdraw(), e.ydraw(), e.xscale, e.yscale, 1);
	}
	
	if (copyId!=-1) {		
		Rectangle(copyId.x, copyId.y, copyId.x+PPU*copyId.xscale, copyId.y+PPU*copyId.yscale, c_blue, 1);
	}

	// Drawing of the entity you are about to place
	if ( alt ) {
		var spr = entities[|entityId];
		Sprite(spr, 0, smx + sprite_get_xoffset(spr), smy + sprite_get_yoffset(spr), (copyId!=-1)?copyId.xscale:1, (copyId!=-1)?copyId.yscale:1, 0.7);
	}

	// Drawing of the selected rectangle
	if (selected != -1) {
		var x1 = selected.x;
		var y1 = selected.y;
		var x2 = x1 + PPU * selected.xscale;
		var y2 = y1 + PPU * selected.yscale;
		var col = make_color_rgb(200, 0, 0);
		
		Rectangle(x1, y1, x2, y2, col, .4);		
		
		var margin = 3;
		var xmar = margin*sign(selected.xscale);
		var ymar = margin*sign(selected.yscale);
	
		Rectangle(x1, y1, x1 + xmar, y1 + ymar,	col,	false);
		Rectangle(x2, y1, x2 - xmar, y1 + ymar,	col,	false);
		Rectangle(x1, y2, x1 + xmar, y2 - ymar,	col,	false);
		Rectangle(x2, y2, x2 - xmar, y2 - ymar,	col,	false);
	}

#endregion

//Print(vx, vy, mx, my);