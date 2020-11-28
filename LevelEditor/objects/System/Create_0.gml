#macro PPU 16

game_set_speed(60, gamespeed_fps);

Camera.cam_mouse_drag_acceleration = 1;
uc_set_target_position(Camera.view_width/2 - 64, -Camera.view_height/2 + 64);
alarm[0] = 5;

// Logic of the level
level = ds_list_create();
placed = ds_list_create();

if(file_exists("options.data")) {
	var saveWork = file_text_open_read("options.data");
	path = file_text_read_string(saveWork);
	Print("----",path)
	projectName = "oju";
	file_text_close(saveWork);
} else {
	projectName = "Untitled";
	path = "";
}
saved = false;
window_set_caption("Mistral LevelEditor : " + projectName);

enum TYPE {
	GROUND,
	CHARACTER,
	ENEMY,
	_ENUMSIZE
}

SPRITE[TYPE.GROUND] = spr_ground;
SPRITE[TYPE.CHARACTER] = spr_character;
NAME[TYPE.GROUND] = "GROUND";
NAME[TYPE.CHARACTER] = "CHARACTER";

selected = -1;

function Entity(x, y, type) constructor {
	self.x = x;
	self.y = y;
	self.xscale = 1;
	self.yscale = 1;
	self.type = type;
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

function SaveFile(filename) {
	if(saved) exit;
	var file = file_text_open_write(filename);
	for (var i = 0; i < ds_list_size(level); ++i) {
		var e = level[|i];
		file_text_write_string(file, NAME[e.type] + "," + string(e.x) + "," + string(e.y) + "," + string(e.xscale) + "," + string(e.yscale) + "\n");
	}
	var splits = Split(filename, ["/", "\\"]);
	path = filename;
	projectName = splits[array_length(splits)-1];
	window_set_caption("Mistral LevelEditor : " + projectName);
	file_text_close(file);
	saved = true;
	Print(projectName + " saved!");
	var saveWork = file_text_open_write("options.data");
	file_text_write_string(saveWork, path);
	file_text_close(saveWork);
}