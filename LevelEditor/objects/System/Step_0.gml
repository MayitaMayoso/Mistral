
#region Camera stuff

	var zspd = 0.3;
	var alt = keyboard_check(vk_alt);
	if(mouse_wheel_down() && alt) uc_set_view_scale(Camera.view_scale * (1+zspd));
	if(mouse_wheel_up() && alt) uc_set_view_scale(Camera.view_scale * (1-zspd));
	
	var vx = Camera.view_x - 1;
	var vy = Camera.view_y - 1;
	var scl = Camera.view_scale;
	var vw = Camera.view_width * scl;
	var vh = Camera.view_height * scl;
	var fact = Camera.view_width / window_get_width();

#endregion

#region Input!

	var mx = vx + window_mouse_get_x() * fact * scl;
	var my = vy + window_mouse_get_y() * fact * scl;
	var smx = Snap(mx);
	var smy = Snap(my);
	var imx = smx / PPU;
	var imy = smy / PPU;
	var lhold = mouse_check_button(mb_left);
	var lpress = mouse_check_button_pressed(mb_left);
	var lrelease = mouse_check_button_released(mb_left);
	var rhold = mouse_check_button(mb_right);
	var rpress = mouse_check_button_pressed(mb_right);
	var rrelease = mouse_check_button_released(mb_right);
	var mhold = mouse_check_button(mb_middle);
	var mpress = mouse_check_button_pressed(mb_middle);
	var mrelease = mouse_check_button_released(mb_middle);
	var control = keyboard_check(vk_control);
	var shift = keyboard_check(vk_shift);
	z += ( mouse_wheel_up() - mouse_wheel_down() ) * !alt;
	ds_list_sort(numOfLayers, false);

#endregion

#region Level managing

	#region Place
	 
		if(lhold && alt) {
			var alreadyPlaced = false;
			selected = -1;
			for (var i = 0; i < ds_list_size(placed); ++i) {
				var e = placed[|i];
				if ( e.x == Snap(mx) && e.y == Snap(my) && e.z == z ) {
					alreadyPlaced = true;
					break;
				}
			}
			for (var i = 0; i < ds_list_size(level); ++i) {
				var e = level[|i];
				if ( e.x == Snap(mx) && e.y == Snap(my) && e.z == z && e.type == entities[|entityId] ) {
					alreadyPlaced = true;
					break;
				}
			}
			if(!alreadyPlaced) {
				var e = new Entity(Snap(mx), Snap(my), z, entities[|entityId]);
				ds_list_add(placed, e);
				if (copyId!=-1) {
					e.xscale = copyId.xscale;
					e.yscale = copyId.yscale;
				}
			}
		}
		if(lrelease) ds_list_clear(placed)
	
	#endregion

	#region Destroy
	
		if(rhold) {
			selected = -1;
			for (var i = 0; i < ds_list_size(level); ++i) {
				var e = level[|i];
				if ( Within(mx, e.x, e.x+PPU*e.xscale) && Within(my, e.y, e.y+PPU*e.yscale) && e.z == z) {
					ds_list_delete(level, i);
					break;
				}
			}
		}
	
	#endregion

	#region Select

		if(lpress && !alt) {
			selected = -1;
			for (var i = 0; i < ds_list_size(level); ++i) {
				var e = level[|i];
				if ( Within(mx, e.x, e.x+PPU*e.xscale) && Within(my, e.y, e.y+PPU*e.yscale)  && e.z == z ) selected = e;
			}	
		}

	#endregion

	#region Modify
	
		window_set_cursor(cr_arrow);
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
				selected.x = Snap(mx) - selected.clicX;
				selected.y = Snap(my) - selected.clicY;
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
	
			if ( lhold ) {
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
	
			if(lrelease) {
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
				if(lpress) {
					selected.rpick = inR;
					selected.lpick = inL;
					selected.bpick = inB;
					selected.tpick = inT;
					selected.cpick = inC;
					selected.clicX = Snap(mx - selected.x);
					selected.clicY = Snap(my - selected.y);
					selected.corX = selected.x + PPU*selected.xscale;
					selected.corY = selected.y + PPU*selected.yscale;
				}
			}
		}
		
	#endregion

	#region Copy
	
		if ( mpress ) {
			selected = -1;
			for (var i = 0; i < ds_list_size(level); ++i) {
				var e = level[|i];
				if ( Within(mx, e.x, e.x+PPU*e.xscale) && Within(my, e.y, e.y+PPU*e.yscale) ) {
					entityId = ds_list_find_index(entities, e.type);
					copyId = e;
				}
			}
		}
	
	#endregion

#endregion

#region File Management

	if ( keyboard_check_released(ord("S")) ) saved = false;
	if( keyboard_check(ord("S")) ) {
		if (control) {
			if ( shift || !permision ) {
				var filename = get_save_filename(".mistral", projectName + ".mistral");
				if (filename!="") SaveFile(filename);
			} else {
				if ( !saved )SaveFile(path);
				saved = true;
			}
		}
	}


	if( keyboard_check(ord("O")) ) {
		if (control) {		
			var filename;
			if ( memorypath == "" ) filename = get_open_filename(".mistral", projectName + ".mistral");
			else filename = get_open_filename_ext(".mistral", memoryprojectName, memorypath, "Open file ");
			if (filename!="") LoadFile(filename);
		}
	}

#endregion
