#include <LiquidCrystal_I2C.h>

const int buttonDotPin = 2;
const int buttonDashPin = 3;
const int buttonEnterPin = 4;
const int buttonSpacePin = 5;
const int deleteButtonPin = 6;
const int resetButtonPin = 7;

const int displayAddress = 0x27;

LiquidCrystal_I2C lcd(displayAddress, 16, 2);

// Define the variable to store the current Morse code character
String currentMorseCodeChar = "";

// Define the variable to store the current Morse code word
String currentMorseCodeWord = "";

// Define a boolean variable to indicate whether the current Morse code character is complete
bool isCurrentMorseCodeCharComplete = false;

// Define a boolean variable to indicate whether the blank button has been pressed
bool isSpaceButtonPressed = false;

// Define a boolean variable to indicate whether the delete button has been pressed
bool isDeleteButtonPressed = false;

void setup() {
  // Set the button pins as inputs with pull-up resistors
  pinMode(buttonDotPin, INPUT_PULLUP);
  pinMode(buttonDashPin, INPUT_PULLUP);
  pinMode(buttonEnterPin, INPUT_PULLUP);
  pinMode(buttonSpacePin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(deleteButtonPin, INPUT_PULLUP);


 // Initialize the display
  lcd.init();
  lcd.backlight();

  // Clear the display
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("Morse Code");

   lcd.setCursor(3, 1);
   lcd.print("Translator");


}

void loop() {
  // Check the state of the reset button
  int resetButtonState = digitalRead(resetButtonPin);

  // If the reset button is pressed, clear the display and reset the variables
  if (resetButtonState == LOW) {
    lcd.clear();
    currentMorseCodeChar = "";
    currentMorseCodeWord = "";
    isCurrentMorseCodeCharComplete = false;
  }







// Check the state of the delete button
  int deleteButtonState = digitalRead(deleteButtonPin);

  // If the delete button is pressed, set the `isDeleteButtonPressed` flag to `true`
  if (deleteButtonState == LOW) {
    isDeleteButtonPressed = true;
  }

  // If the `isDeleteButtonPressed` flag is `true`, delete the last character from the current Morse code word
  if (isDeleteButtonPressed) {
    currentMorseCodeWord = currentMorseCodeWord.substring(0, currentMorseCodeWord.length() - 1);

    // Reset the `isDeleteButtonPressed` flag
    isDeleteButtonPressed = false;
  }

  // Check the state of the space button
  int spaceButtonState = digitalRead(buttonSpacePin);

  // If the space button is pressed, set the `isspaceButtonPressed` flag to `true`
  if (spaceButtonState == LOW) {
    isSpaceButtonPressed = true;
  }

  // If the `isSpaceButtonPressed` flag is `true`, add a space character to the current Morse code word
  if (isSpaceButtonPressed) {
    currentMorseCodeWord += " ";

    // Reset the `isSpaceButtonPressed` flag
    isSpaceButtonPressed = false;
  }



  // Read the state of the buttons
  int buttonDotState = digitalRead(buttonDotPin);
  int buttonDashState = digitalRead(buttonDashPin);
  int buttonEnterState = digitalRead(buttonEnterPin);

  // If the dot button is pressed, add a dot to the current Morse code character
  if (buttonDotState == LOW) {
    currentMorseCodeChar += ".";
  }

  // If the dash button is pressed, add a dash to the current Morse code character
  if (buttonDashState == LOW) {
    currentMorseCodeChar += "-";
  }

  // If the Enter button is pressed, mark the current Morse code character as complete
  if (buttonEnterState == LOW) {
    isCurrentMorseCodeCharComplete = true;
  }

  // If the current Morse code character is complete, decode it and display it on the display
  if (isCurrentMorseCodeCharComplete) {
    // Decode the Morse code character
    char decodedChar = decodeMorseCodeChar(currentMorseCodeChar);

    // If the decoded character is a valid character, add it to the current Morse code word
    if (decodedChar != '\0') {
      currentMorseCodeWord += decodedChar;
    }

    // Clear the current Morse code character
    currentMorseCodeChar = "";

    // Reset the isCurrentMorseCodeCharComplete flag
    isCurrentMorseCodeCharComplete = false;

    // Display the current Morse code word on the display
    lcd.clear();
    lcd.print(currentMorseCodeWord);

  }

  // Delay for 100 milliseconds
  delay(100);
}

// Decode a Morse code character
char decodeMorseCodeChar(String morseCodeChar) {
  // Define a lookup table for the Morse code characters
  const char* morseCodeLookupTable[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
  };

  // Decode the Morse code character and return the decoded character
  for (int i = 0; i < 26; i++) {
    if (morseCodeChar == morseCodeLookupTable[i]) {
      return 'a' + i;
    }
  }


// Define a lookup table for the Morse code numbers
const char* morseCodeNumberLookupTable[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

// Decode the Morse code number
for (int i = 0; i < 10; i++) {
  if (morseCodeChar == morseCodeNumberLookupTable[i]) {
    return '0' + i;
  }
}


  // If the Morse code character is a Space character, return the Space character
  if (morseCodeChar == " ") {
    return ' ';
  }

  // If the Morse code character is not valid, return the null character
  return '\0';
}
