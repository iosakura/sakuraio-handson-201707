#include <SakuraIO.h>

/*
  Standardサンプルから送信以外のいらない部分を消してみた
 */

//SakuraIO_SPI sakuraio(10);
SakuraIO_I2C sakuraio;

void setup() {
  Serial.begin(9600);
  // オンラインになるまでまつ
  Serial.print("Waiting to come online");
  for(;;){
    if( (sakuraio.getConnectionStatus() & 0x80) == 0x80 ) break;
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

uint8_t counter = 0;

void loop() {
  counter++;

  Serial.println("");
  Serial.println(counter);

  // 接続状態を取得して表示する
  uint8_t connectionStatus = sakuraio.getConnectionStatus();
  Serial.print("Status ");
  Serial.println(connectionStatus);

  // 送信データをキューに追加する
  uint8_t ret;
  ret = sakuraio.enqueueTx(0, (int32_t)counter);
  Serial.print("Enqueue ");
  Serial.println(ret);

  // キューの中身を送信する
  ret = sakuraio.send();
  Serial.print("Send ");
  Serial.println(ret);

  delay(5000);
}
