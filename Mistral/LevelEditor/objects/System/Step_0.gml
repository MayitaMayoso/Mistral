switch(state) {
	case S.START:
		if (keyboard_check_pressed(vk_enter)) state = S.SELECT_WIDTH;
		keyboard_string = "";
		break;
	case S.SELECT_WIDTH:
		if (keyboard_check_pressed(vk_enter)) {
			if ( is_real(real(keyboard_string)) )	{
				width = real(keyboard_string);
				keyboard_string = "";
				state = S.SELECT_HEIGHT;
			} else {
				keyboard_string = "";	
			}
		}
		break;
	case S.SELECT_HEIGHT:
		if (keyboard_check_pressed(vk_enter)) {
			if ( is_real(real(keyboard_string)) )	{
				height = real(keyboard_string);
				keyboard_string = "";
				ds_grid_resize(level, width, height);
				state = S.DRAW;
			} else {
				keyboard_string = "";	
			}
		}
		break;
	case S.DRAW:
		break;
	case S.EXPORT:
		break;
}