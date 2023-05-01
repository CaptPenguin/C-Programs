void int2bitstr(int I, char *str) {
	str[32] = '\0';

	for(int i = 31; i >= 0; i--){
		unsigned int bit = I & 1;
		if(bit == 0){
			str[i] = '0';
		} else {
			str[i] = '1';
		}
		I >>= 1;
	}
}

int get_exp_value(float f) {
	unsigned f2u(float f);
	unsigned int ui = f2u(f);
	
	ui = ui << 1;
	ui = ui >> 24;
	if(ui == 0){
		return ui-126;
	}
	else if(ui == 255){
		return ui-256;
	}
	else{
		return ui-127;
	}
}
