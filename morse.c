#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wiringPi.h>

#define LED 0	//GPIO Pin used is  0

#define shortDelay 200
#define longDelay 500
#define spaceDelay 1000

const char* morse_alphabet_table[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-","-.--","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
const char* morse_number_table[] = {"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};

void signal(int);

int main(int argc, char* argv[]){
	if(wiringPiSetup() == -1){
		(void)fprintf(stderr, "Unable to execute method 'wiringPi'. \nAre you executing this program with root privileges?");
		return -1;
	}

	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);

	if(argc < 1){
		(void)fprintf(stderr, "morse: morse <arg1> [arg2 ...]");
		(void)fprintf(stderr, "\tTranslate Input into Morse Code with LED-Output");
		return -1;
	}

	for(int i = 1; i < argc; ++i){
		char* input = argv[i];
		int string_length = strlen(input);
		
		for(int a = 0; a < string_length; ++a){
			char character = tolower(input[a]);
			int encoding;
			const char* morse_code;

			if(character >= '0' && character <= '9' ){
				encoding = character - '0';
				morse_code = morse_number_table[encoding];
			} else if(character >= 'a' && character <= 'z'){
				encoding = character - 'a';
				morse_code = morse_alphabet_table[encoding];
			}else{
				(void)fprintf(stderr, "'%c' is not supported", character);
				continue;
			}

			 
			int morse_code_length = strlen(morse_code);

			for(int b = 0; b < morse_code_length; ++b){
				(void)fprintf(stdout, "%c", morse_code[b]);

				switch(morse_code[b]){
					case '.':
						signal(shortDelay);
						break;
					case '-':
						signal(longDelay);
						break;
				}

			}

			(void)fprintf(stdout, "  ");
			digitalWrite(LED, LOW);
			delay(spaceDelay);
		}
		(void)fprintf(stdout, "\n");
	}
	return 0;
}

void signal(int delayTime){
	digitalWrite(LED, HIGH);
	delay(delayTime);
	digitalWrite(LED, LOW);
	delay(delayTime);
}