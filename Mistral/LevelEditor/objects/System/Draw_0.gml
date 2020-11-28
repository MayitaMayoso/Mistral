switch(state) {
	case S.START:
		draw_set_halign(fa_middle);
		draw_set_valign(fa_center);
		draw_text_transformed(room_width/2, room_height/2, "MISTRAL ENGINE\nLevel Editor\n\nPress enter to start", 2, 2,0);
		break;
	case S.SELECT_WIDTH:
		draw_set_halign(fa_middle);
		draw_set_valign(fa_center);
		draw_text_transformed(room_width/2, room_height/2, "Select level width in blocks and press enter:\n" + keyboard_string, 1, 1, 0);
		break;
	case S.SELECT_HEIGHT:
		draw_set_halign(fa_middle);
		draw_set_valign(fa_center);
		draw_text_transformed(room_width/2, room_height/2, "Select level height in blocks and press enter:\n" + keyboard_string, 1, 1, 0);
		break;
	case S.DRAW:		
		var margin = 20;
		var xspace = (room_width-margin*2) / width;
		var yspace = (room_height-margin*2) / height;
		for(var i=0 ; i<=width ; i++ )
			draw_line(margin + xspace*i, margin, margin + xspace*i, room_height - margin);
		for(var i=0 ; i<=height ; i++ )
			draw_line(margin, margin + yspace*i, room_width - margin, margin + yspace*i);
		break;
	case S.EXPORT:
		break;
}
