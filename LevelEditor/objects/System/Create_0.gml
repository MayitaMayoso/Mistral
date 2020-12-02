#macro PPU 16
#macro FILENAME "CONFIGURATION.data"

#region Global Settings

	game_set_speed(60, gamespeed_fps);

	Camera.cam_mouse_drag_acceleration = 1;
	uc_set_target_position(Camera.view_width/2 - 64, -Camera.view_height/2 + 64);
	alarm[0] = 5;

#endregion

#region Logic of the level

	level = ds_list_create();
	placed = ds_list_create();

	selected = -1;
	copyId = -1;
	
	entityId = 0;
	
	entities = ds_list_create();
	var ent = tag_get_assets("Entities");
	for (var i = 0; i < array_length(ent); ++i)
		ds_list_add(entities, asset_get_index(ent[i]));

	function Entity(x, y, type) constructor {
		self.type = type;
		self.x =  x;
		self.y = y;
		static xdraw = function() { return self.x + sprite_get_xoffset(type); };
		static ydraw = function() { return self.y + sprite_get_yoffset(type); };
		self.xscale = 1;
		self.yscale = 1;
		self.bpick = false;
		self.tpick = false;
		self.lpick = false;
		self.rpick = false;
		self.cpick = false;
		self.clicX = 0;
		self.clicY = 0;
		self.corX = 0;
		self.corY = 0;
		ds_list_add(System.level, self);
	}
	
#endregion

#region GUI

	gui = {
		
		// Parameters
		unit : 1,
		scale : 4,
		itemsPerRow : 3,		
		col : {	base : Grey(45), shade : Grey(30), light : Grey(50), accent : make_color_rgb(255, 0, 0)	},
		
		// Attributes		
		width : 0,
		height : 0,
		
		// State
		resize : false,
		show : true,		
		
		// Calculate every variable necessary
		Init : function() {
			unit = PPU * scale;
			width = unit * itemsPerRow;
			height = Camera.port_height;
		},
		
		// Draw the whole gui			
		Draw : function() {
			
			// Management
			if ( keyboard_check_pressed(vk_space) ) show = !show;
			if ( !show ) exit;
			Init();
						
			// Background div
			var bw = 3;
			draw_rectangle_color(0, 0, width, height, col.base, col.base, col.base, col.base, false);
			draw_line_width_color(width+bw/2, 0, width+bw/2, height, bw, col.light, col.light);
			draw_line_width_color(width+3*bw/2, 0, width+3*bw/2, height, bw, col.shade, col.shade);
				
			// Entities drawing
			for (var i = 0; i < ds_list_size(System.entities); i++) {
				var xx = (i % itemsPerRow) * unit;
				var yy = (i div itemsPerRow) * unit;
				var spr = System.entities[|i];
				if ( i==System.entityId && System.copyId==-1) Rectangle(xx, yy, xx+unit, yy+unit, col.shade, false);
				Sprite(spr, 0, xx + sprite_get_xoffset(spr) * scale, yy + sprite_get_yoffset(spr) * scale, scale, scale, 1);
				if ( i==System.entityId && System.copyId==-1) Rectangle(xx, yy, xx+unit, yy+unit, col.accent, 1);
			}
			
			// Mouse interaction
			var mx = window_mouse_get_x();
			var my = window_mouse_get_y();
			var imx = mx div unit;
			var imy = my div unit;
			var smx = unit * imx;
			var smy = unit * imy;
			var lhold = mouse_check_button(mb_left);
			var lpress = mouse_check_button_pressed(mb_left);
			var lrelease = mouse_check_button_released(mb_left);
			var entId = imx + itemsPerRow * imy;
			
			// Resize the window
			if ( resize ) {
				if ( lrelease ) {
					resize = false;
					window_set_cursor(cr_arrow);
				} else {
					itemsPerRow = max(imx,1);
					window_set_cursor(cr_size_we);
				}
			} else {			
				if ( mx < width  ) {
					if ( entId < ds_list_size(System.entities) ) {
						window_set_cursor(cr_handpoint);
						Rectangle(smx, smy, smx+unit, smy+unit, c_white, true);
						if ( lpress ) {
							System.entityId = entId;
							System.copyId = -1;
						}
					}
				} else {
					if ( mx < width + bw*2 ) {
						window_set_cursor(cr_size_we);
						if ( lpress ) resize = true;
					}
				}		
			}
		}
	}

#endregion

#region File management
	projectName = "Untitled";
	path = "";
	window_set_caption("Mistral LevelEditor : " + projectName);
	
	
	memorypath = "";
	memoryprojectName = "";	
	
	if(file_exists(FILENAME)) {	
		var file = file_text_open_read(FILENAME);
					
		memorypath = file_text_read_string(file);
		var arr = Split(memorypath, ["\\", "/"]);
		memoryprojectName = arr[array_length(arr)-1];
		memorypath = string_copy(memorypath, 0, string_length(memorypath) - string_length(memoryprojectName));
	
		Print(memorypath, memoryprojectName);
						
		file_text_close(file);
	}

	saved = false;
	permision = false;

	function SaveFile(filename) {
		var file = file_text_open_write(filename);
		for (var i = 0; i < ds_list_size(level); ++i) {
			var e = level[|i];
			file_text_write_string(file, sprite_get_name(e.type) + "," + string(e.xdraw()/PPU) + "," + string(-e.ydraw()/PPU) + "," + string(e.xscale) + "," + string(e.yscale) + "\n");
		}
		var splits = Split(filename, ["/", "\\"]);
		path = filename;
		projectName = splits[array_length(splits)-1];
		projectName = string_copy(projectName, 0, string_length(projectName) - 8);
		window_set_caption("Mistral LevelEditor : " + projectName);
		file_text_close(file);
		Print(projectName + " saved!");
	
		var saveWork = file_text_open_write(FILENAME);
		file_text_write_string(saveWork, path);
		file_text_close(saveWork);
	
		permision = true;
		selected = -1;
	}

	function LoadFile(filename) {	
		for (var i = 0; i < ds_list_size(level); ++i) {
			var e = level[|i];
			delete e;
		}
	
		ds_list_clear(level);
	
		var file = file_text_open_read(filename);	
	
		while(!file_text_eof(file)) {
			var line = file_text_readln(file);
			var arr = Split(line, ",");
			var e = new Entity(real(arr[1])*PPU, -real(arr[2])*PPU, asset_get_index(arr[0]));
			e.xscale = real(arr[3]);
			e.yscale = real(arr[4]);
			e.x -= sprite_get_xoffset(e.type);
			e.y -= sprite_get_yoffset(e.type);
		}
		file_text_close(file);
	
		var splits = Split(filename, ["/", "\\"]);
		path = filename;
		projectName = splits[array_length(splits)-1];
		projectName = string_copy(projectName, 0, string_length(projectName) - 8);
		window_set_caption("Mistral LevelEditor : " + projectName);
		Print(projectName + " loaded!");
	
		selected = -1;
	}

#endregion