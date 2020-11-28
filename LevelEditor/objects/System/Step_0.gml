var zspd = 0.3;
if(mouse_wheel_down()) uc_set_view_scale(Camera.view_scale * (1+zspd));
if(mouse_wheel_up()) uc_set_view_scale(Camera.view_scale * (1-zspd));

var scl = Camera.view_scale;
var fact = Camera.view_width / window_get_width();
var mx = Camera.view_x + window_mouse_get_x() * fact * scl;
var my = Camera.view_y + window_mouse_get_y() * fact * scl;


// Select
if(mouse_check_button(mb_left) && keyboard_check(vk_alt)) {
	var alreadyPlaced = false;
	selected = -1;
	for (var i = 0; i < ds_list_size(placed); ++i) {
		var e = placed[|i];
		if ( e.x == snap(mx) && e.y == snap(my) ) {
			alreadyPlaced = true;
		}
	}
	if(!alreadyPlaced) ds_list_add(placed, new Entity(snap(mx), snap(my), TYPE.GROUND));
}

if(mouse_check_button_pressed(mb_left) && !keyboard_check(vk_alt)) {
	selected = -1;
	for (var i = 0; i < ds_list_size(level); ++i) {
		var e = level[|i];
		if ( Within(mx, e.x, e.x+PPU*e.xscale) && Within(my, e.y, e.y+PPU*e.yscale) ) selected = e;
	}	
}

if(mouse_check_button_released(mb_left)) ds_list_clear(placed)

// Destroy
if(mouse_check_button(mb_right)) {
	selected = -1;
	for (var i = 0; i < ds_list_size(level); ++i) {
		var e = level[|i];
		if ( Within(mx, e.x, e.x+PPU*e.xscale) && Within(my, e.y, e.y+PPU*e.yscale) ) {
			ds_list_delete(level, i);
			break;
		}
	}
}


// Modify
if(selected != -1) {
	if ( selected.rpick ) selected.xscale = round((mx - selected.x)/PPU);
	if ( selected.bpick ) selected.yscale = round((my - selected.y)/PPU);
	if ( selected.lpick ) {
		selected.xscale = round(-(mx - selected.corX)/PPU);
		selected.x = selected.corX - PPU*selected.xscale;
	}
	if ( selected.tpick ) {
		selected.yscale = round(-(my - selected.corY)/PPU);
		selected.y = selected.corY - PPU*selected.yscale;
	}
	if ( selected.cpick ) {
		selected.x = snap(mx) - selected.clicX;
		selected.y = snap(my) - selected.clicY;
	}

	var x1 = selected.x;
	var y1 = selected.y;
	var x2 = x1 + PPU * selected.xscale;
	var y2 = y1 + PPU * selected.yscale;
	
	var margin = 3;
	var xmar = margin*sign(selected.xscale);
	var ymar = margin*sign(selected.yscale);
	var inR = Within(mx, x2-xmar, x2) && Within(my, y1, y2);
	var inL = Within(mx, x1, x1+xmar) && Within(my, y1, y2);
	var inB = Within(my, y2-ymar, y2) && Within(mx, x1, x2);
	var inT = Within(my, y1, y1+ymar) && Within(mx, x1, x2);
	var inC = Within(mx, x1 + xmar, x2 - xmar) && Within(my, y1 + ymar, y2 - ymar);
	
	window_set_cursor(cr_arrow);
	if ( mouse_check_button(mb_left) ) {
		if ( selected.bpick || selected.tpick ) window_set_cursor(cr_size_ns);
		if ( selected.rpick || selected.lpick ) window_set_cursor(cr_size_we);
		if ( (selected.bpick&&selected.rpick) || (selected.tpick&&selected.lpick) ) window_set_cursor(cr_size_nwse);
		if ( (selected.tpick&&selected.rpick) || (selected.bpick&&selected.lpick) ) window_set_cursor(cr_size_nesw);
		if ( selected.cpick ) window_set_cursor(cr_size_all);
	} else {
		if ( inB || inT ) window_set_cursor(cr_size_ns);
		if ( inR || inL ) window_set_cursor(cr_size_we);
		if ( (inB&&inR) || (inT&&inL) ) window_set_cursor(cr_size_nwse);
		if ( (inT&&inR) || (inB&&inL) ) window_set_cursor(cr_size_nesw);
		if ( inC ) window_set_cursor(cr_size_all);
	}
	
	if(mouse_check_button_released(mb_left)) {
		selected.bpick = false;
		selected.tpick = false;
		selected.lpick = false;
		selected.rpick = false;
		selected.cpick = false;
		if (selected.xscale == 0 || selected.yscale == 0) {
			ds_list_delete(level, ds_list_find_index(level, selected));
			selected = -1;		
		}
	} else {
		if(mouse_check_button_pressed(mb_left)) {
			selected.rpick = inR;
			selected.lpick = inL;
			selected.bpick = inB;
			selected.tpick = inT;
			selected.cpick = inC;
			selected.clicX = snap(mx - selected.x);
			selected.clicY = snap(my - selected.y);
			selected.corX = selected.x + PPU*selected.xscale;
			selected.corY = selected.y + PPU*selected.yscale;
		}
	}
}

if( keyboard_check(ord("S")) ) {
	if (keyboard_check(vk_control)) {
		if ( keyboard_check(vk_shift) || projectName=="Untitled" ) {
			var filename = get_save_filename("", (projectName=="Untitled")?"Untitled.mistral":projectName);
			if (filename!="") SaveFile(filename);	
		} else {
			if ( projectName != "Untitled" ) SaveFile(path);	
		}
	}
}

if (keyboard_check_released(ord("S")) || keyboard_check_released(vk_shift) || keyboard_check_released(vk_control)) saved = false;