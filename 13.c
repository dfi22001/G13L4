#include <13.h>
#include <nrfx.h>
#include <nrfx_uarte.h>
#include <nrf_gpio.h>
#include <stdlib.h>
#define CLEAR_screen "\033c"




void uarte_handler(nrfx_uarte_event_t const *p_event, void *p_context)
{
    nrfx_uarte_t * p_inst = p_context;
    if (p_event->type == NRFX_UARTE_EVT_RX_DONE)
    {
    //gör något

    }
}


void uarte_write(uint8_t* data, uint8_t length)
{
  nrfx_uarte_tx(&instance, data, length, 0);
  while(nrfx_uarte_tx_in_progress(&instance));
}


void readstring(uint8_t str[])
{
  int i = 0;
  do
  {
    nrfx_uarte_rx(&instance, &uarte_buffer, sizeof(uarte_buffer));
    str[i] = uarte_buffer;
    i += 1;
  } while (str[i - 1] != '\r'&& i <99);
  str[i - 1] = '\0';
}

int strtoint(uint32_t inputstr[])
{
  return atoi(inputstr);
}

void start_game_13(){

  char arr[] = "\r\n";
	char grid[10][10];
	char clear[] = CLEAR_screen;
	int y= 0, x =0, y_apple, x_apple;
	int score = 0;
	int run = 1;
	y_apple = rand()%10; 
	x_apple = rand()%10;
	char state[] = " You won!";
	while(run){
		uarte_write(clear, sizeof(clear));
		nrfx_uarte_rx(&instance, &uarte_buffer, sizeof(uarte_buffer));
		/*if(uarte_buffer == 'a'){
			uarte_write(arr, sizeof(arr));
			uarte_buffer = 0;
		}*/
		switch(uarte_buffer)
		{
			case 'i':
			if(y > 0){
			y --;
			}
			uarte_buffer = '0';
			break;

			case 'k':
			if(y < 9 )
			{
			y = y+1;
			}
			uarte_buffer = '0';
			break; 

			case 'j':
			if(x > 0)
			{
			x = x-1;
			}
			uarte_buffer = '0';
			break;

			case 'l':
			if(x < 9){
			x++;
			}
			uarte_buffer = '0';
			break; 
			case 'q':
			run = 0;
			break;
			
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				grid[i][j] = '_';
				
			}
		}
		grid[y][x] = 'o';
		grid[y_apple][x_apple] = 'm';
		if(y == y_apple && x == x_apple)
		{
			y_apple = rand()%10; 
			x_apple = rand()%10;
			score +=1;
		}
    
		for(int z = 0; z < 10; z++){
		uarte_write(grid[z], sizeof(grid[z]));
		uarte_write(arr, sizeof(arr)); 
		}
		nrfx_systick_delay_ms(100);
		if(score == 10){
      uarte_write(state, sizeof(state));
      break;
		}
	}
}


