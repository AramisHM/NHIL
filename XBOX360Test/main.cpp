#include "CXBOXController.h"
#include <iostream>


int main(int argc, char* argv[])
{
	xcon_create();

	while(true)
	{
		xcon_update();

		if(xcon_is_key_pressed(xcon_dpad_up))
			printf("dpad\n");
		if(xcon_is_key_pressed(xcon_key_x))
			printf("teste tecla press\n");
		if(xcon_is_key_active(xcon_dpad_down))
			printf("dpada\n");
		if(xcon_is_key_released(xcon_key_y))
			printf("teste tecla pressa\n");

		printf("R Stick: X = %lf\t\t\t\t\t Y = %lf\n", xcon_RStickX(), xcon_RStickY());
	}

	xcon_destroy();

	return( 0 );
}