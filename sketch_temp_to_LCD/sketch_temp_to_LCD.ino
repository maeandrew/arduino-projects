#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // инициализируем LCD, указывая контакты данных
// задаем переменные
int Count = 0;                  // счетчик обновлений
int tempPin = 0;                // пин куда подключен датчик
float tempc = 0;                // переменная для температуры
float maxi = 0, mini = 30;      // max/min значения температуры

void setup() {
  // красивая "загрузка" программы при старте :)
  lcd.begin(16, 2);
  lcd.print("Loading");
  delay(500);                // ждем 0.5 секунды
  lcd.print(".");
  delay(500);                // ждем 0.5 секунды
  lcd.print(".");
  delay(500);                // ждем 0.5 секунды
  lcd.print(".");
  delay(1000);               // ждем 1 секунду
  lcd.clear();               //очистка экрана
}

void loop() {
  lcd.clear();               //очистка экрана
  // считываем и вычисляем температуру
  tempc = 0.48828125 * analogRead(tempPin) ;
  if(tempc > maxi) {
    maxi = tempc;
  } // max температура?

  if(tempc < mini) {
    mini = tempc;
  } // min температура?

  lcd.setCursor(0, 0);     // устанавливаем курсор в 0-ом
  // столбце, 1 строке (начинается с 0)
  lcd.print("t=");
  lcd.print(tempc);        // выводим текущую температуру
  lcd.setCursor(0, 1);     // устанавливаем курсор в 0-ом столбце, 2 строке
  lcd.print("t");        // обозначение минимальной температры
  lcd.print(mini);         // выводим min температуру
  lcd.print(" T");         // обозначение максимальной температуры
  lcd.print(maxi);         // выводим max температуру 
  delay(5*500);   // задержка перед повторением измерений
  Count++;         // инкремент счетчика измерений
}
