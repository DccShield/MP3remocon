#include <IRremote.h>
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include "IrCmd_List.h"

int RECV_PIN = 11;
int volume = 10;
unsigned long PreviosTime = 0;  // PreviosTime 前時間


IRrecv irrecv(RECV_PIN);
SoftwareSerial mySoftwareSerial(A4, A5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

decode_results results;

void setup()
{
  Serial.begin(115200);
  // ソフトウエアシリアル通信レートセット:
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  Serial.println(F("DFPlayer Mini online."));
 
  irrecv.enableIRIn();          // Start the receiver
  myDFPlayer.volume(volume);    // Set volume value. From 0 to 30
  PreviosTime = millis();       // setup()終了時の時刻をPreviosTimeに格納

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    state(results.value);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

void state(long val){
  switch(val){
      case IRCMD_NEC_FUNC1:
      case IRCMD_SONYTV_FUNC1:
      case IRCMD_SONYMD_FUNC1:
                              track(1);
                              break;
      case IRCMD_NEC_FUNC2:
      case IRCMD_SONYTV_FUNC2:
      case IRCMD_SONYMD_FUNC2:
                              track(2);
                              break;
      case IRCMD_NEC_FUNC3:
      case IRCMD_SONYTV_FUNC3:
      case IRCMD_SONYMD_FUNC3:
                              track(3);
                              break;  
      case IRCMD_NEC_FUNC4:
      case IRCMD_SONYTV_FUNC4:
      case IRCMD_SONYMD_FUNC4:
                              track(4);
                              break;  
      case IRCMD_NEC_FUNC5:
      case IRCMD_SONYTV_FUNC5:
      case IRCMD_SONYMD_FUNC5:
                              track(5);
                              break;
      case IRCMD_NEC_FUNC6:
      case IRCMD_SONYTV_FUNC6:
      case IRCMD_SONYMD_FUNC6:
                              track(6);
                              break;
      case IRCMD_NEC_FUNC7:
      case IRCMD_SONYTV_FUNC7:
      case IRCMD_SONYMD_FUNC7:
                              track(7);
                              break;
      case IRCMD_NEC_FUNC8:
      case IRCMD_SONYTV_FUNC8:
      case IRCMD_SONYMD_FUNC8:
                              track(8);
                              break;
      case IRCMD_NEC_FUNC9:
      case IRCMD_SONYTV_FUNC9:
      case IRCMD_SONYMD_FUNC9:
                              track(9);
                              break;
      case IRCMD_NEC_PLAY:
      case IRCMD_SONYTV_PLAY:
      case IRCMD_SONYMD_PLAY:      
                              //myDFPlayer.start();
                              //Serial.println("PLAY");
                              break;  
      case IRCMD_NEC_STOP:
      case IRCMD_SONYTV_STOP:
      case IRCMD_SONYMD_STOP:      
                              myDFPlayer.stop();
                              Serial.println("STOP");
                              break;  
      case IRCMD_NEC_SPEEDUP:
//    case IRCMD_SONYTV_SPEEDUP:  //  error: previously used here
      case IRCMD_SONYMD_SPEEDUP:
                               volume ++;
                               if(volume >=20)
                                volume = 20;
                               myDFPlayer.volume(volume);
                               break;
      case IRCMD_NEC_SPEEDDOWN:
//    case IRCMD_SONYTV_SPEEDDOWN:  // error: previously used here
      case IRCMD_SONYMD_SPEEDDOWN:
                               volume --;
                               if(volume < 0)
                                volume = 0;
                               myDFPlayer.volume(volume);
                               break;
                              
      default:
                break;
  }
}

void track( int ch ){
   Serial.print("TRACK:");  
   Serial.println(ch);  
   myDFPlayer.play(ch);
}
