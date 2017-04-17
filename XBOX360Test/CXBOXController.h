#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_
// By Aramis Hornung Moraes 
// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")

// By Aramis Hornung Moraes 
typedef struct analog_hardware{
	double Xpos;
	double Ypos;
};
// XBOX Controller Class Definition
class CXBOXController
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;

	
public:
	CXBOXController(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
	analog_hardware RightThumbStick, LeftThumbStick; // ideal seria fazer um getter e um setter para as variaveis ao invez de deixalas em publics
	double RightTrigger, LeftTrigger;
};
// By Aramis Hornung Moraes 
enum controller_keys
{
	xcon_key_a = 0,
	xcon_key_b = 1,
	xcon_key_x = 2,
	xcon_key_y = 3,
	xcon_dpad_down = 4,
	xcon_dpad_up = 5,
	xcon_dpad_left = 6,
	xcon_dpad_right = 7
};

double xcon_RStickX();
double xcon_RStickY();
double xcon_LStickX();
double xcon_LStickY();
double xcon_RTrigger();
double xcon_LTrigger();
void xcon_create();
void xcon_update();
void xcon_destroy();
int xcon_is_key_pressed(controller_keys key);
int xcon_is_key_released(controller_keys key);
int xcon_is_key_active(controller_keys key);


#endif
