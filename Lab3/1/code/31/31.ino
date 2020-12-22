#include <LiquidCrystal.h>

const int rs = 13 , en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(16, 2);
}
int counter = 0 ;
int i = 0 ;
void loop() {
  lcd.clear() ;
  i = 0 ;
  lcd.setCursor(0 , 0 ) ;
  lcd.print("Seyyed Mahdi") ;

  
  for ( i = 0 ; i < 4 ; i ++ ) {
    lcd.scrollDisplayRight() ;
    delay(500) ;
  }

  
  lcd.clear() ;
  lcd.noDisplay();
  lcd.setCursor(0 , 1 ) ;
  lcd.print("Seyyed Mahdi") ;

  
  for ( i = 0 ; i < 12 ; i++ ) {
    lcd.scrollDisplayLeft() ;
  }

  
  lcd.setCursor(16, 0) ;
  lcd.print("Seyyed Mahdi") ;
  lcd.display();

  
  for ( i = 0 ; i < 15 ; i ++ ) {
    lcd.scrollDisplayRight() ;
    delay(500) ;
  }


  lcd.clear() ;
  lcd.noDisplay();
  lcd.setCursor(0 , 0 ) ;
  lcd.print("Seyyed Mahdi") ;



  for ( i = 0 ; i < 12 ; i++ ) {
    lcd.scrollDisplayLeft() ;
  }


  lcd.setCursor(16, 1) ;
  lcd.print("Seyyed Mahdi") ;
  lcd.display();

  for ( i = 0 ; i < 12 ; i ++ ) {
    lcd.scrollDisplayRight() ;
    delay(500) ;
  }
}
