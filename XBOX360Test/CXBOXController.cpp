#include "CXBOXController.h"
#include <stdio.h>
// By Aramis Hornung Moraes   2015

CXBOXController::CXBOXController(int playerNumber)
{
	// Set the Controller Number
	_controllerNum = playerNumber - 1;
}

XINPUT_STATE CXBOXController::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool CXBOXController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if(Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CXBOXController::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}
//============-=-=-=-=-=-=-=-=-=-================-=-=-=-=-=-=-=-=-=-=-================
//============-=-=-=-=-=-=-=-=-=-================-=-=-=-=-=-=-=-=-=-=-================
//============-=-=-=-=-=-=-=-=-=-================-=-=-=-=-=-=-=-=-=-=-================
// By Aramis Hornung Moraes 24/01/214  2015
//============-=-=-=-=-=-=-=-=-=-================-=-=-=-=-=-=-=-=-=-=-================
//============-=-=-=-=-=-=-=-=-=-================-=-=-=-=-=-=-=-=-=-=-================
//variaveis do singletone do joystick
#define n_keys 8
int past_state_keys[n_keys];
int keys[n_keys];
// range raw do joystick eh de -32000 a 32000 ou simplesmente SHORT, conversao pode ser feito para int usando cast (int)
int inner_dead_j = 5000;
int outter_dead_j = 31000;


CXBOXController* Player1;

// default is 31000 and 5000, in a range of 0 to 32000
// By Aramis Hornung Moraes 24/01/214  2015
void xcon_set_jitter(int inner_jitter, int outter_jitter)
{
	inner_dead_j = inner_jitter;
	outter_dead_j = outter_jitter;
}

void xcon_create()
{
	for(int i = 0; i < n_keys; i++)
	{
		keys[i] = 0;
	}
	for(int i = 0; i < n_keys; i++)
	{
		past_state_keys[i] = 0;
	}
	Player1 = new CXBOXController(1);

	Player1->LeftThumbStick.Xpos = Player1->RightThumbStick.Xpos = (double)0;
	Player1->LeftThumbStick.Ypos = Player1->RightThumbStick.Ypos = (double)0;
	Player1->RightTrigger = Player1->LeftTrigger = (double)0;
}
void xcon_update()
{
	for(int i = 0; i < n_keys; i++)
	{
		past_state_keys[i] = keys[i];
		keys[i] = 0;
	}


	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		keys[xcon_key_a] = 1;
	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		keys[xcon_key_b] = 1;
	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
		keys[xcon_key_x] = 1;
	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		keys[xcon_key_y] = 1;

	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		keys[xcon_dpad_up] = 1;
	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		keys[xcon_dpad_down] = 1;
	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		keys[xcon_dpad_left] = 1;
	if(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		keys[xcon_dpad_right] = 1;


	// JOYSTICKS !!!!!!!!!!!!!!!!!!!!!!!!!!!
	Player1->RightThumbStick.Xpos = (double)Player1->GetState().Gamepad.sThumbRX;
	Player1->RightThumbStick.Ypos = (double)Player1->GetState().Gamepad.sThumbRY;

	Player1->LeftThumbStick.Xpos = (double)Player1->GetState().Gamepad.sThumbLX;
	Player1->LeftThumbStick.Ypos = (double)Player1->GetState().Gamepad.sThumbLY;

	Player1->RightTrigger = (double)Player1->GetState().Gamepad.bRightTrigger;
	Player1->LeftTrigger = (double)Player1->GetState().Gamepad.bLeftTrigger;
	

	// TRATAR O JITTER
	// R ThumbSti
	if(Player1->RightThumbStick.Xpos > 0)//X
	{
		if(Player1->RightThumbStick.Xpos < inner_dead_j)
			Player1->RightThumbStick.Xpos = 0;
		if(Player1->RightThumbStick.Xpos > outter_dead_j)
			Player1->RightThumbStick.Xpos = 32000;
	}
	else
	{
		if(Player1->RightThumbStick.Xpos > -inner_dead_j)
			Player1->RightThumbStick.Xpos = 0;
		if(Player1->RightThumbStick.Xpos < -outter_dead_j)
			Player1->RightThumbStick.Xpos = -32000;
	}
	if(Player1->RightThumbStick.Ypos > 0)//Y
	{
		if(Player1->RightThumbStick.Ypos < inner_dead_j)
			Player1->RightThumbStick.Ypos = 0;
		if(Player1->RightThumbStick.Ypos > outter_dead_j)
			Player1->RightThumbStick.Ypos = 32000;
	}
	else // inverte o valor
	{
		if(Player1->RightThumbStick.Ypos > -inner_dead_j)
			Player1->RightThumbStick.Ypos = 0;
		if(Player1->RightThumbStick.Ypos < -outter_dead_j)
			Player1->RightThumbStick.Ypos = -32000;
	}

	// L ThumbSti
	if(Player1->LeftThumbStick.Xpos > 0)//X
	{
		if(Player1->LeftThumbStick.Xpos < inner_dead_j)
			Player1->LeftThumbStick.Xpos = 0;
		if(Player1->LeftThumbStick.Xpos > outter_dead_j)
			Player1->LeftThumbStick.Xpos = 32000;
	}
	else
	{
		if(Player1->LeftThumbStick.Xpos > -inner_dead_j)
			Player1->LeftThumbStick.Xpos = 0;
		if(Player1->LeftThumbStick.Xpos < -outter_dead_j)
			Player1->LeftThumbStick.Xpos = -32000;
	}

	if(Player1->LeftThumbStick.Ypos > 0)//Y
	{
		if(Player1->LeftThumbStick.Ypos < inner_dead_j)
			Player1->LeftThumbStick.Ypos = 0;
		if(Player1->LeftThumbStick.Ypos > outter_dead_j)
			Player1->LeftThumbStick.Ypos = 32000;
	}
	else // inverte o valor
	{
		if(Player1->LeftThumbStick.Ypos > -inner_dead_j)
			Player1->LeftThumbStick.Ypos = 0;
		if(Player1->LeftThumbStick.Ypos < -outter_dead_j)
			Player1->LeftThumbStick.Ypos = -32000;
	}
		


	// Normaliza os valores de short (0-3200) pra normais (0-1)
	Player1->RightThumbStick.Xpos/=32000;
	Player1->RightThumbStick.Ypos/=32000;
	Player1->LeftThumbStick.Xpos/=32000;
	Player1->LeftThumbStick.Ypos/=32000;
	Player1->RightTrigger/=32000;
	Player1->LeftTrigger/=32000;


}

// Getters dos valores do controle xbox
double xcon_RStickX()
{
	return Player1->RightThumbStick.Xpos;
}
double xcon_RStickY()
{
	return Player1->RightThumbStick.Ypos;
}
double xcon_LStickX()
{
	return Player1->LeftThumbStick.Xpos;
}
double xcon_LStickY()
{
	return Player1->LeftThumbStick.Ypos;
}

double xcon_RTrigger()
{
	return Player1->RightTrigger;
}
double xcon_LTrigger()
{
	return Player1->LeftTrigger;
}


void xcon_destroy()
{
	delete(Player1);
}

int xcon_is_key_pressed(controller_keys key)
{
	if(past_state_keys[key] == 0 && keys[key] == 1)
		return 1;
	else
		return 0;
}

int xcon_is_key_released(controller_keys key)
{
	if(past_state_keys[key] == 1 && keys[key] == 0)
		return 1;
	else
		return 0;
}

int xcon_is_key_active(controller_keys key)
{
	return keys[key];
}
