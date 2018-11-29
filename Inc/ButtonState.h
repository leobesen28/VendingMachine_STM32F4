#ifndef BUTTONSTATE_H
	#define BUTTONSTATE_H
/*
 ------BUTUONS DEFINES-------
*/	
#define	 BUTTON_M025 	0x01
#define	 BUTTON_M050 	0x02 
#define	 BUTTON_M100 	0x03
#define	 BUTTON_DEV  	0x04 
#define	 BUTTON_MEET 	0x05
#define	 BUTTON_ETIRPS 	0x06
#define	 BUTTON_STOCK  0x07
#define  BUTTON_STOCK_ACCESS 0x08
#define  BUTTON_ADD_MEET 0x09
#define  BUTTON_ADD_ETIRPS 0x0A
#define  BUTTON_STOCK_INC 0x0B
#define  BUTTON_STOCK_DEC 0x0C
#define  BUTTON_STOCK_STOP 0x0D
#define  BUTTON_CASH			0x0F

/*
 ----------------------------
*/

class ButtonState{
		bool m025, m050, m100; //moedas
		bool dev, meet, etirps, stock;
		bool stock_acc, add_m, add_e, s_inc, s_dec, s_stop, s_cash; 
	public:
		ButtonState(void);
		~ButtonState(void);
		void setButtonState(char, bool);
		bool getButtonState(char);
		void resetButtonState(char,char);
};
#endif
