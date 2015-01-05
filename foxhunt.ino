
// These values are in miliseconds
const int WPM = 20;
const int DIT = 1200 / WPM;
const int DAH = DIT * 3;
const int LETTER_SPACE = DIT * 3;
const int WORD_SPACE = DIT * 7;

// ========= Pin assignments ==========
// The pin to blink morse, as sending.
const int LED_PIN = 13;

// The pin to send rf out of.
const int TX_PIN = 12;


//Fox
const unsigned int FREQ=35000;
const long foxCount = 1;
const long foxIndex = 1;

const long intervalsBefore = foxIndex-1;
const long intervalsAfter = foxCount-foxIndex;

long previousMillis = 0;
long messageLength = 0;
long callsignMessageLength = 0;
const long interval = 60000;//1 min
const long intervalBefore = interval * intervalsBefore;
const long intervalAfter = interval * intervalsAfter;


//Messages
const String CALLSIGN_MESSAGE="DE YO2MKE/P";

/**
 * Iterate through a given string and perform blink() on each character.
 * @return String Morse message that needs to be sent.
 */
String message(){
 switch (foxIndex) {
    case 1: return "ME";
    case 2: return "MI";
    case 3: return "MS";
    case 4: return "MH";
    case 5: return "M5";
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED_PIN, OUTPUT);
  messageLength=blink_time(message());
  callsignMessageLength=blink_time(CALLSIGN_MESSAGE);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  
  unsigned long currentMillis = millis();
  
char buf[500];
sprintf(buf, "currentMillis %lu previousMillis %lu messageLength %lu callsignMessageLength %lu c-p %lu intervalBefore %lu interval %lu intervalAfter %lu ib+i %lu ib+i+ia %lu", currentMillis, previousMillis, messageLength, callsignMessageLength, currentMillis - previousMillis, intervalBefore, interval, intervalAfter, intervalBefore + interval, intervalBefore + interval + intervalAfter); 
Serial.println( buf );



  if(currentMillis - previousMillis > intervalBefore && currentMillis - previousMillis < intervalBefore + interval) {
    //TX interval
    if(currentMillis - previousMillis + messageLength + callsignMessageLength< intervalBefore + interval){
      //I have time to send both message and callsign so send message
      perform_blink(message());
    }else{
      if(currentMillis - previousMillis + callsignMessageLength< intervalBefore + interval){
        //I still have time to send callsign so send callsign
        perform_blink(CALLSIGN_MESSAGE);
      }else{
        if(currentMillis - previousMillis + messageLength< intervalBefore + interval){
          //I can only squeze a message so send it
          perform_blink(message());
        }
      }
    }
  }
  
  if(currentMillis - previousMillis > intervalBefore + interval + intervalAfter) {
    // start a new cycle
    previousMillis = currentMillis;   
  }
  
}

/**
 * Iterate through a given string and perform blink() on each character.
 *
 * @param String text The string of letters to encode to morse.
 */
void perform_blink(String text){
   text.toLowerCase();
  for (int i = 0; i < text.length(); i++) {
    
    // Handle special cases here.
    if (text.charAt(i) == ' ') {
      delay(WORD_SPACE);
      continue;
    }
    
    // Convert the letter to morse, ...
    String morseified = convert_morse(text.charAt(i));
    
    // For each char of the morse string, ...
    for (int j = 0; j <= morseified.length(); j++) {
      
      if (morseified.charAt(j) == '.') {
        blink('.');
      } else if (morseified.charAt(j) == '-') {
        blink('-');
      }
    }
    delay(LETTER_SPACE);
  }
}
/**
 * Iterate through a given string and reutrn the milliseconds needed to send the message.
 *
 * @param String text The string of letters to encode to morse.
 * @return int millisenconds nedded to send the message.
 */
int blink_time(String text) {
  int duration=0;
  text.toLowerCase();
  for (int i = 0; i < text.length(); i++) {
    
    // Handle special cases here.
    if (text.charAt(i) == ' ') {
      duration+=WORD_SPACE;
      continue;
    }
    
    // Convert the letter to morse, ...
    String morseified = convert_morse(text.charAt(i));
    
    // For each char of the morse string, ...
    for (int j = 0; j <= morseified.length(); j++) {
      
      if (morseified.charAt(j) == '.') {
        duration+=DIT;
      } else if (morseified.charAt(j) == '-') {
        duration+=DAH;
      }
      duration+=DIT;
    }
    duration+=LETTER_SPACE;
  }
  return duration;
}

/**
 * Blink the LED and sound the tone for one "dit" or "dah"
 *
 * @param char type_delay A char representing a dit or dah ('.' or '-') which
                          determines how long the action happens.
*/
void blink(char type_delay) {

  digitalWrite(LED_PIN, HIGH);
  tone(TX_PIN, FREQ);
  if (type_delay == '.') {
    delay(DIT);
  } else if (type_delay == '-') {
    delay(DAH);
  }

  digitalWrite(LED_PIN, LOW);
  noTone(TX_PIN);
  delay(DIT);
}

/**
 * Convert a char/letter to appropriate dots and dashes.
 * @param char letter The letter to encode
 * @return String Morse code representation (ASCII "." and "-") of the given
                  char.
*/
String convert_morse(char letter) {
  switch (letter) {
    case 'a': return ".-";
    case 'b': return "-...";
    case 'c': return "-.-.";
    case 'd': return "-..";
    case 'e': return ".";
    case 'f': return "..-.";
    case 'g': return "--.";
    case 'h': return "....";
    case 'i': return "..";
    case 'j': return ".---";
    case 'k': return "-.-";
    case 'l': return ".-..";
    case 'm': return "--";
    case 'n': return "-.";
    case 'o': return "---";
    case 'p': return ".--.";
    case 'q': return "--.-";
    case 'r': return ".-.";
    case 's': return "...";
    case 't': return "-";
    case 'u': return "..-";
    case 'v': return "...-";
    case 'w': return ".--";
    case 'x': return "-..-";
    case 'y': return "-.--";
    case 'z': return "--..";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '0': return "-----";
    case '?': return "..--..";
    case '.': return ".-.-.-";
    case ',': return "--..--";
    case '-': return "-....-";
    case '/': return "-..-.";
    default: return "";
  }
}
