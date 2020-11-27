width = 1;
height = 1;
level = ds_grid_create(width, height);

enum S {
	START,
	SELECT_WIDTH,
	SELECT_HEIGHT,
	DRAW,
	EXPORT,
	_ENUMSIZE
}

state = S.START;