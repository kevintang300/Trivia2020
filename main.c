	/*
	 * proj1.c
	 *
	 * Created: 4/13/2020 3:11:32 PM
	 * Author : Kevin Tang
	 */ 

	#include "avr.h"
	#include "lcd.h"
	#include <stdio.h>
	#include <math.h>
	#include <time.h>
	#include <stdlib.h>




struct Note {
	
	int frequency;
	int duration;
	
	
};

struct Stats {
	
	int current;
	int min;
	int max;
	long sum;
	int count;
	
};



int get_key(void);

int is_pressed(int r, int c);

void display_startup();

void display_menu();

void display_sport();

void pop_culture();
void sports();

void ready_set_go();


void play_note(int frequency, int duration);

void play_song(const struct Note SONG[], int songLength);


int get_sample();

void update_stats(int s);





//Sound
#define A 0
#define As 1
#define B 2
#define C 3
#define Csharp 4
#define D 5
#define Dsharp 6
#define E 7
#define F 8
#define Fsharp 9
#define G 10
#define Gsharp 11

//Duration
#define W 1
#define H 2
#define Q 4
int freq[12] = {222, 232, 250, 263, 277, 294, 312, 333, 344, 370, 393, 416};
struct Note winning_song[] = { {C,Q}, {E,Q}, {G,Q} };
struct Note losing_song[] = { {G,H}, {E,H}, {C,H} };
struct Note start_song[] = { {G,Q}, {G,Q}, {G,Q} };


struct Stats stats;








static int currentTopic = 0;
static int p_question = 0;
static int s_question = 0;






	
int main(void){
		
			
		
		lcd_init();
		
		/* Display Game Title */
		display_startup();
		avr_wait(90300);
		lcd_clr();
		
		char sport_title[17]; sprintf(sport_title, "Sports!!");
		char pop_title[17]; sprintf(pop_title, "Pop Culture!");
		char true_false[17]; sprintf(true_false, "True or False!");

	
			SET_BIT(DDRB,3);
			int keyPress;
			while(1) {
					
			
				/* Menu Options */
				display_menu();
				keyPress = get_key();
				int s = get_sample() % 2;
				update_stats(s);
			
				
				if(keyPress == 14) {

					
					lcd_clr();
				
					
					switch(s) {

						case 0:
						{
							
							lcd_pos(0,4);
							lcd_puts(sport_title);
							avr_wait(100400);
							lcd_clr();

							sports();
							currentTopic = 1;
							break;
						}
						
			
						case 1:
						{
							
							lcd_pos(0,2);
							lcd_puts(pop_title);
							avr_wait(100400);
							lcd_clr();
							
							
							pop_culture();
							currentTopic = 0;
							break;
						}
						
					

                        default:
						{
							break;
						}
						
						

					}
			}
	}
}


int get_key(void) {
		int r, c;
	
		for(r = 0; r < 4; ++r) {
			for(c=0; c<4; ++c) {
			
				if(is_pressed(r,c)) {
					return (r * 4 + c) + 1;
				}
			
			}
		}
		return 0;
}

int is_pressed(int r, int c) {
	
		DDRC = 0;
		PORTC = 0;
	
	
		SET_BIT(DDRC, r);
		SET_BIT(PORTC, c + 4);
	
		avr_wait(1);
	
		if(GET_BIT(PINC, c + 4)) {
			return 0;
		}
	
		return 1;
	
}



void display_startup() {


	  char line_one[17];
	  char screen_title[17] = "Trivia Game!";
	  sprintf(line_one, "%s", screen_title);
	  lcd_pos(0,2);
	  lcd_puts(line_one);
	  
	  
	  
		char line_two[17];
	    char year[17] = "2020";
	    sprintf(line_two, "%s", year);
	    lcd_pos(1,6);
	    lcd_puts(line_two);

}


void display_menu() {


	  char line_one[17];
	  char line_two[17];
	  char directions[17] = "Start";
	  char press_command[17] = "Press 0 to";


	  sprintf(line_one, "%s", press_command);
	  sprintf(line_two, "%s", directions);

	  lcd_pos(0,3);
	  lcd_puts(line_one);

	  lcd_pos(1,6);
	  lcd_puts(line_two);

  

}


void display_sport() {


	  char line_one[17];
	  char sport[17] = "Sports";
  

	  sprintf(line_one, "%s", sport);

		/* Display Category for a certain amount of time */
	  for(int i = 0; i < 1000; ++i) {
		lcd_pos(0,0);
		lcd_puts(line_one);
    
	  }
  
		lcd_clr();
  
		
		
  

}


void pop_culture() {
	
	
	ready_set_go();
	int i = 0;
	
	
	p_question = get_sample() % 24;


	

	int pop_score = 0;
	while (i < 10){
		
		if(p_question > 24) {
			p_question = get_sample() % 12;
			
			if(p_question < 9) {
				p_question = 0;
			} else {
				p_question--;
			}
		}
		
		if(p_question == 0) {
		  
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Dave Chappelle");
			sprintf(line_two, "is a _______");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();
			
			
			
			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Singer");
				sprintf(option_two, "B. Comedian");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);
				
				if(keyPress == 4) {
					lcd_clr();
					break;
					
				}
				
				if(keyPress == 8){
					++pop_score;
					lcd_clr(); 
					break;
				}
				
					
			}
			
			
		}
		
		else if(p_question == 1) {
			
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Adam Sandler");
			sprintf(line_two, "Movie");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();
			
			
			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Uncut Gems");
				sprintf(option_two, "B. Inception");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);
				
				if(keyPress == 4) {
					++pop_score;
					lcd_clr();
					break;
				}
				
				if(keyPress == 8){
					lcd_clr();
					break;
				}
				
					
			}
			
		}
		
		
		else if(p_question == 2) {
			
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Tom Cruise's");
			sprintf(line_two, "Religion");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();
			
			
			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Buddhism");
				sprintf(option_two, "B. Scientology");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);
				
				if(keyPress == 4){
					lcd_clr();
					break;
				}
				
				if(keyPress == 8){
                    ++pop_score;
					lcd_clr();
					break;
				}
					
			}
			
			
		}

        else if(p_question == 3) {
             
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Jennifer Anistons");
            sprintf(line_two, "Exhusband");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Brad Pitt");
                sprintf(option_two, "B. Tom Hardy");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

           
        }

        else if(p_question == 4) {
       
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Award show for");
            sprintf(line_two, "movies");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Oscars");
                sprintf(option_two, "B. Emmys");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

            
        }


        else if(p_question == 5) {
          
            /* Display Question */
            char line_one[17];
            sprintf(line_one, "Beyonce's Song");
            lcd_pos(0,0);
            lcd_puts(line_one);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Single Ladies");
                sprintf(option_two, "B. Can't Take It");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

         
        }


        else if(p_question == 6) {
           
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Steve Carrell's");
            sprintf(line_two, "TV show");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Lost");
                sprintf(option_two, "B. The Office");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

           
        }
        else if(p_question == 7) {
           
              /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Kylie's Last");
            sprintf(line_two, "Name");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Kardashian");
                sprintf(option_two, "B. Jenner");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
				
            }

           
        }

        else if(p_question == 8) {
       
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Jeremey Zucker's");
            sprintf(line_two, "Song");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. come thru");
                sprintf(option_two, "B. coffee");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
					++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    
                    lcd_clr();
                    break;
                }
					
            }
        }


        else if(p_question == 9) {
      
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Friends TV show");
            sprintf(line_two, "aired on");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. 1994");
                sprintf(option_two, "B. 1998");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

          
        }

        else if(p_question == 10) {
     
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Stranger Things");
            sprintf(line_two, "Plays On");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Hulu");
                sprintf(option_two, "B. Netflix");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

          
        }


        else if(p_question == 11) {
      
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Justin Bieber's");
            sprintf(line_two, "2020 Song");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Intentions");
                sprintf(option_two, "B. Sorry");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
            }

            
        }

        else if(p_question == 12) {
            
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Travis Scott");
            sprintf(line_two, "is a ______");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Rapper");
                sprintf(option_two, "B. Dancer");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					avr_wait(5000);
            }

      
        }

        else if(p_question == 13) {
             
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Hannah");
            sprintf(line_two, "Montanna is");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Miley Cyrus");
                sprintf(option_two, "B. Courtney Cox");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					avr_wait(5000);
            }

           
        }


        else if(p_question == 14) {
             
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Suite Life of");
            sprintf(line_two, "________");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Zack/Cody");
                sprintf(option_two, "B. David/Jordan");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
					++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    
                    lcd_clr();
                    break;
                }
					
            }

            
        }


        else if(p_question == 15) {
           
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Who is Iron");
            sprintf(line_two, "Man?");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Chris Evans");
                sprintf(option_two, "B. Robert Downey");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

          
        }

        else if(p_question == 16) {
	       
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Who is Captain");
            sprintf(line_two, "America?");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Chris Evans");
                sprintf(option_two, "B. Leonardo D.");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

            
        }

        else if(p_question == 17) {
       
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Double Double");
            sprintf(line_two, "Grilled Onions");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. In and Out");
                sprintf(option_two, "B. Mcdonalds");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
			}
        }

        else if(p_question == 18) {
           
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Kylie's Last");
            sprintf(line_two, "Name");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Kardashian");
                sprintf(option_two, "B. Jenner");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

            
        }

        else if(p_question == 19) {
 
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Mario and ____");
            lcd_pos(0,0);
            lcd_puts(line_one);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Bowser");
                sprintf(option_two, "B. Luigi");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

        }

        else if(p_question == 20) {
   
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Coachella's");
            sprintf(line_two, "Festival Month");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. June");
                sprintf(option_two, "B. April");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

            
        }


        else if(p_question == 21) {
           
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Drake's Real");
            sprintf(line_two, "Name");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Calvin");
                sprintf(option_two, "B. Aubrey");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {

                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    ++pop_score;
                    lcd_clr();
                    break;
                }
					
            }

           
        }


        else if(p_question == 22) {
        
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Monica Geller");
            sprintf(line_two, "is named _____");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Courtney Cox");
                sprintf(option_two, "B. Monique Bel");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
			}

        }


        else if(p_question == 23) {
    
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "David Dobrik");
            sprintf(line_two, "is a ______");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. Vlogger");
                sprintf(option_two, "B. Athlete");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

           
        }

        else if(p_question == 24) {
  
            /* Display Question */
            char line_one[17];
            char line_two[17];
            sprintf(line_one, "Jimmy Fallon's");
            sprintf(line_two, "Location");
            lcd_pos(0,0);
            lcd_puts(line_one);
            lcd_pos(1,0);
            lcd_puts(line_two);
            avr_wait(90500);
            lcd_clr();


            /* Change Score */
            int keyPress = 0;
            while(keyPress == 0) {
                keyPress = get_key();
                /* Display Options */
                char option_one[17];
                char option_two[17];
                sprintf(option_one, "A. New York");
                sprintf(option_two, "B. Los Angeles");
                lcd_pos(0,0);
                lcd_puts(option_one);
                lcd_pos(1,0);
                lcd_puts(option_two);

                if(keyPress == 4) {
                    ++pop_score;
                    lcd_clr();
                    break;
                }

                if(keyPress == 8){
                    lcd_clr();
                    break;
                }
					
            }

           
        }
		
		++p_question;
		++i;
    }
	
		char your_score[17];
		sprintf(your_score, "Your Score");

		char str_score[17];
		sprintf(str_score, "%d/10", pop_score);

		lcd_pos(0,3);
		lcd_puts(your_score);

		lcd_pos(1,5);
		lcd_puts(str_score);
		
		
		if(pop_score >= 7) {
			
			while(1) {
				
				int n = sizeof(winning_song) / sizeof(winning_song[0]);
				play_song(winning_song, n);
				
				break;
				
				
			}
		}
		
		else {
			while(1) {
				
				int n = sizeof(losing_song) / sizeof(losing_song[0]);
				play_song(losing_song, n);
				
				
				break;
			}
			
			
		}
		
		
		avr_wait(90500);
		lcd_clr();
	
	
	
	
}

void sports() {

	ready_set_go();
	s_question = get_sample() % 14;
	
	int i = 0;

	int sports_score = 0;
	while (i < 10){

		if(s_question > 14) {
			s_question = get_sample() % 7;
			
			if(s_question < 3) {
				s_question = 0;
				} else {
				s_question--;
			}
			
		}


		if(s_question == 0) {
			
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Lebrons Jersey");
			sprintf(line_two, "Number");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. 23");
				sprintf(option_two, "B. 21");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

			
		}

		else if(s_question == 1) {
		
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "49ers Jersey");
			sprintf(line_two, "Color");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Red/White");
				sprintf(option_two, "B. Teal/Purple");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}


		}


		else if(s_question == 2) {

			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Kobe's Middle");
			sprintf(line_two, "Name");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Derek");
				sprintf(option_two, "B. Bean");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4){
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					++sports_score;
					lcd_clr();
					break;
				}
			}


		}

		else if(s_question == 3) {

			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Tom Brady's");
			sprintf(line_two, "Sport");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Football");
				sprintf(option_two, "B. Baseball");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

		}

		else if(s_question == 4) {

			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Michael Jordan");
			sprintf(line_two, "2nd sport");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Baseball");
				sprintf(option_two, "B. Football");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

		}


		else if(s_question == 5) {
			
			/* Display Question */
			char line_one[17];
			sprintf(line_one, "NHL Team");
			lcd_pos(0,0);
			lcd_puts(line_one);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Sharks");
				sprintf(option_two, "B. Mets");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

			
		}


		else if(s_question == 6) {
		
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Irish MMA");
			sprintf(line_two, "Fighter");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. James Jones");
				sprintf(option_two, "B. Conor M.");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					++sports_score;
					lcd_clr();
					break;
				}
			}

			
		}
		else if(s_question == 7) {
			
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Golden State");
			sprintf(line_two, "______");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Terriers");
				sprintf(option_two, "B. Warriors");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {

					lcd_clr();
					break;
				}

				if(keyPress == 8){
					++sports_score;
					lcd_clr();
					break;
				}
			}

			
		}

		else if(s_question == 8) {
		
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Who are the");
			sprintf(line_two, "Splash Bros");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Steph/Klay");
				sprintf(option_two, "B. Kobe/Lebron");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

			
		}


		else if(s_question == 9) {
		
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Stanley Cup");
			sprintf(line_two, "Trophy");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. NHL");
				sprintf(option_two, "B. MLB");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

		}

		else if(s_question == 10) {

			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Zion's NBA");
			sprintf(line_two, "Team");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. Lakers");
				sprintf(option_two, "B. Pelicans");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {

					lcd_clr();
					break;
				}

				if(keyPress == 8){
					++sports_score;
					lcd_clr();
					break;
				}
			}

			
		}


		else if(s_question == 11) {
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Lombordi Trophy");
			lcd_pos(0,0);
			lcd_puts(line_one);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. NFL");
				sprintf(option_two, "B. NHL");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}

			
		}

		else if(s_question == 12) {
			/* Display Question */
			char line_one[17];
			char line_two[17];
			sprintf(line_one, "Larry O'Brien");
			sprintf(line_two, "Trophy");
			lcd_pos(0,0);
			lcd_puts(line_one);
			lcd_pos(1,0);
			lcd_puts(line_two);
			avr_wait(90500);
			lcd_clr();


			/* Change Score */
			int keyPress = 0;
			while(keyPress == 0) {
				keyPress = get_key();
				/* Display Options */
				char option_one[17];
				char option_two[17];
				sprintf(option_one, "A. NBA");
				sprintf(option_two, "B. NFL");
				lcd_pos(0,0);
				lcd_puts(option_one);
				lcd_pos(1,0);
				lcd_puts(option_two);

				if(keyPress == 4) {
					++sports_score;
					lcd_clr();
					break;
				}

				if(keyPress == 8){
					lcd_clr();
					break;
				}
			}
		
			
		}
		
		    else if(s_question == 13) {
			  
			    /* Display Question */
			    char line_one[17];
			    char line_two[17];
			    sprintf(line_one, "Most NBA");
			    sprintf(line_two, "Championships");
			    lcd_pos(0,0);
			    lcd_puts(line_one);
			    lcd_pos(1,0);
			    lcd_puts(line_two);
			    avr_wait(90500);
			    lcd_clr();


			    /* Change Score */
			    int keyPress = 0;
			    while(keyPress == 0) {
				    keyPress = get_key();
				    /* Display Options */
				    char option_one[17];
				    char option_two[17];
				    sprintf(option_one, "A. Celtics");
				    sprintf(option_two, "B. Lakers");
				    lcd_pos(0,0);
				    lcd_puts(option_one);
				    lcd_pos(1,0);
				    lcd_puts(option_two);

				    if(keyPress == 4) {
					    ++sports_score;
					    lcd_clr();
					    break;
				    }

				    if(keyPress == 8){
					    lcd_clr();
					    break;
				    }
			    }
			    
		    }

			++s_question;
			++i;

	}
			char your_score[17];
			sprintf(your_score, "Your Score");

			char str_score[17];
			sprintf(str_score, "%d/10", sports_score);

			lcd_pos(0,3);
			lcd_puts(your_score);

			lcd_pos(1,5);
			lcd_puts(str_score);
			
			
		if(sports_score >= 7) {
			
			while(1) {
				
				int n = sizeof(winning_song) / sizeof(winning_song[0]);
				play_song(winning_song, n);
				
				break;
				
				
			}
		} 
		
		else {
				while(1) {
					
					int n = sizeof(losing_song) / sizeof(losing_song[0]);
					play_song(losing_song, n);
					
					
					break;
				}
					
			
		}
		
		
			avr_wait(90500);
			lcd_clr();
		

}



void ready_set_go() {
	
	
		char ready[17];
		sprintf(ready, "READY...");
		lcd_pos(0,4);
		lcd_puts(ready);
		avr_wait(50700);
		lcd_clr();
		
		
		char set[17];
		sprintf(set, "SET...");
		lcd_pos(0,6);
		lcd_puts(set);
		avr_wait(50700);
		lcd_clr();
		
		char go[17];
		sprintf(go, "GO!!!!");
		lcd_pos(0,5);
		lcd_puts(go);
			while(1) {
				
				int n = sizeof(start_song) / sizeof(start_song[0]);
				play_song(start_song, n);
				
				break;
				
				
			}
		avr_wait(50700);
		lcd_clr();
		
}


void play_note(int frequency, int duration) {


	int hz = freq[frequency];
	int period = 23495 / hz;
	int TH = period / 2;
	int TL = TH;
	
	
	
	
	unsigned int plays = 1000 / duration;
	unsigned int i;
	for(i = 0; i < plays; ++i) {
		SET_BIT(PORTB,3);
		avr_wait(TH);
		CLR_BIT(PORTB,3);
		avr_wait(TL);
	}
	
	
	
	
	
	
}


void play_song(const struct Note SONG[], int songLength) {
	
	
	int i;
	for(i = 0; i < songLength; ++i) {
		play_note(SONG[i].frequency, SONG[i].duration);
		
		
		
		
		int keyPress = get_key();
		if(keyPress == 4) { break;}
		
		
	}
	
}

int get_sample() {
	
	
	SET_BIT(ADMUX, 6);
	CLR_BIT(ADMUX, 7);
	SET_BIT(ADCSRA, 7);
	SET_BIT(ADCSRA, 6);
	avr_wait(10);

	
	while(GET_BIT(ADCSRA, 6)) {
		
	}
	
	return (ADC + 7);
	
}

void update_stats(int s) {
	
	
	stats.current = s;
	
	
	if(stats.min > s) {
		stats.min = s;
	}
	
	if(stats.max < s) {
		stats.max = s;
	}
	
	stats.sum += s;
	++stats.count;

}