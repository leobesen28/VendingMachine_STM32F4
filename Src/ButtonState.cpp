#include "ButtonState.h"

ButtonState::ButtonState(void){
	m025 = 0;
	m050 = 0;
	m100 = 0; 
	dev = 0;
	meet = 0;
	etirps = 0;
	stock = 0;
	stock_acc = 0;
	add_m = 0;
	add_e = 0;
	s_inc = 0;
	s_dec = 0;
	s_stop = 0;
	s_cash = 0;
}
ButtonState::~ButtonState(void){}

/*
params
	button : 	BUTTON_M025 
				BUTTON_M050 	 
				BUTTON_M100 	
				BUTTON_DEV  	 
				BUTTON_MEET 	
				BUTTON_ETIRPS 
				BUTTON_STOCK
	
	state : 	true or false
*/


	
void ButtonState::setButtonState(char button, bool state){
	switch(button){
		case 0x01:
			this->m025 = state;
			break;
		case 0x02:
			this->m050 = state;
			break;
		case 0x03:
			this->m100 = state;
			break;
		case 0x04:
			this->dev = state;
			break;
		case 0x05:
			this->meet = state;
			break;
		case 0x06:
			this->etirps = state;
			break;
		case 0x07:
			this->stock = state;
			break;
		case 0x08:
			this->stock_acc = state;
			break;
		case 0x09:
			this->add_m = state;
			break;
		case 0x0A:
			this->add_e = state;
			break;
		case 0x0B:
			this->s_inc = state;
			break;
		case 0x0C:
			this->s_dec = state;
			break;
		case 0x0D:
			this->s_stop = state;
			break;
		case 0x0F:
			this->s_cash = state;
		default:
			//criar enum de status de operações STATUS_OK, STATUS_ERRO
			break;
	}	
}

/*
params
	button : 	BUTTON_M025 
				BUTTON_M050 	 
				BUTTON_M100 	
				BUTTON_DEV  	 
				BUTTON_MEET 	
				BUTTON_ETIRPS 
				BUTTON_STOCK
*/

bool ButtonState::getButtonState(char button){
	switch(button){
		case 0x01:
			return m025;
		case 0x02:
			return m050;
		case 0x03:
			return m100;
		case 0x04:
			return dev;
		case 0x05:
			return meet;
		case 0x06:
			return etirps;
		case 0x07:
			return stock;
		case 0x08:
			return stock_acc;
		case 0x09:
			return add_m;
		case 0x0A:
			return add_e;
		case 0x0B:
			return s_inc;
		case 0x0C:
			return s_dec;
		case 0x0D:
			return s_stop;
		case 0x0F:
			return s_cash;
		default:
			return 0;
	}
}
/*
To clear all the buttons state: allButtons = 1, buttonNumber = don't care
To clear just one button: allButtons = 0, button = 	BUTTON_M025 
																										BUTTON_M050 	 
																										BUTTON_M100 	
																										BUTTON_DEV  	 
																										BUTTON_MEET 	
																										BUTTON_ETIRPS 
																										BUTTON_STOCK
*/
void ButtonState::resetButtonState(char allButtons, char button){
	if(allButtons == 0x01){
		m025 = 0;
		m050 = 0;
		m100 = 0; 
		dev = 0;
		meet = 0;
		etirps = 0;
		stock = 0;
		stock_acc = 0;
		add_m = 0;
		add_e = 0;
		s_inc = 0;
		s_dec = 0;
		s_stop = 0;
		s_cash = 0;
	}else{
		switch(button){
			case 0x01:
				this->m025 = 0;
				break;
			case 0x02:
				this->m050 = 0;
				break;
			case 0x03:
				this->m100 = 0;
				break;
			case 0x04:
				this->dev = 0;
				break;
			case 0x05:
				this->meet = 0;
				break;
			case 0x06:
				this->etirps = 0;
				break;
			case 0x07:
				this->stock = 0;
				break;
			case 0x08:
				this->stock_acc = 0;
				break;
			case 0x09:
				this->add_m = 0;
				break;
			case 0x0A:
				this->add_e = 0;
				break;
			case 0x0B:
				this->s_inc = 0;
				break;
			case 0x0C:
				this->s_dec = 0;
				break;
			case 0x0D:
				this->s_stop = 0;
				break;
			case 0x0F:
				this->s_cash = 0;
			break;
			default:
				//criar enum de status de operações STATUS_OK, STATUS_ERRO
				break;
			}
	}
}
