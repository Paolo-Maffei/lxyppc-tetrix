/*******************************************************************************
* File Name          : StringResource.c
* Author             : lxyppc
* Version            : V1.0
* Date               : 10-01-21
* Description        : String resouce file
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "StringResource.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

const LPCSTR StringTable_ENG[STR_LAST] ={	
  [STR_CAMERA_ON]       = "Camera On ",
  [STR_CAMERA_OFF]      = "Camera Off",
  [STR_JOYSTICK]        = "Joystick",
  [STR_MOUSE]           = "Mouse",
  [STR_AIR_MOUSE]       = "Air Mouse",
  [STR_KEYBOARD]        = "Keyboard",
  [STR_KB_NORMAL]       = "Normal",
  [STR_KB_SEQ]          = "Senquence",
  [STR_TETRIS]          = "Play Tetris",
  [STR_TETRIS_PAUSE]    = "Game Pause  ",
  [STR_TETRIS_OVER]     = "Game Over   ",
  [STR_TETRIS_PLAY]     = "Game Running",
  [STR_TETRIS_SWITCH]   = "Pause game first!",
  [STR_ABOUT_0]         = "Super Joystick",
  [STR_ABOUT_1]         = "lxyppc@163.com",
  [STR_ABOUT_2]         = "All rights reserved",
  [STR_MOUSE_0]         = "R1 - Scorll Up",
  [STR_MOUSE_1]         = "R2 - Scroll Down",
  [STR_MOUSE_2]         = "Buttons:",
  [STR_MOUSE_3]         = "4-Left 3-Mid 2-Right",
  [STR_SETTING]         = "Setting",
  [STR_LANG_CHS]        = /*"��������"*/"\xA7\x84\x82\x99",
  [STR_LANG_ENG]        = "English",
  [STR_ABOUT]           = "About"
};

const LPCSTR StringTable_CHS[STR_LAST] ={	
  [STR_CAMERA_ON]       = /*"����ͷ��"*/"\x98\x87\x8D\x92",
  [STR_CAMERA_OFF]      = /*"����ͷ��"*/"\x98\x87\x8D\x89",
  [STR_JOYSTICK]        = /*"��Ϸ�ֱ�"*/"\xA3\x94\x96\xA0",
  [STR_MOUSE]           = /*"���"*/"\xB4\xA1",
  [STR_AIR_MOUSE]       = /*"��Ӧ���"*/"\x93\x91\xB4\xA1",
  [STR_KEYBOARD]        = /*"����"*/"\xB2\xA6",
  [STR_KB_NORMAL]       = /*"����"*/"\xA2\x8F",
  [STR_KB_SEQ]          = /*"˳��"*/"\xB3\x90",
  [STR_TETRIS]          = /*"����˹����"*/"\x85\xAA\x9A\x9B\x8C",
  [STR_TETRIS_PAUSE]    = /*"��Ϸ��ͣ    "*/"\xA3\x94\x9C\x86    ",
  [STR_TETRIS_OVER]     = /*"��Ϸ����    "*/"\xA3\x94\xA9\x9F    ",
  [STR_TETRIS_PLAY]     = /*"��Ϸ������.."*/"\xA3\x94\xB1\xAC\x82..",
  [STR_TETRIS_SWITCH]   = /*"������ͣ��Ϸ!"*/"\xAE\x88\x9C\x86\xA3\x94!",
  [STR_ABOUT_0]         = /*"�����ֱ�"*/"\xAF\xA8\x96\xA0",
  [STR_ABOUT_1]         = "lxyppc@163.com",
  [STR_ABOUT_2]         = /*"��Ȩ����"*/"\xA5\x9E\x95\x9D",
  [STR_MOUSE_0]         = /*"R1 - ��������"*/"R1 - \xA4\xB0\x8B\x80",
  [STR_MOUSE_1]         = /*"R2 - ��������"*/"R2 - \xA4\xB0\x8B\x81",
  [STR_MOUSE_2]         = /*"����:"*/"\x97\xB2:",
  [STR_MOUSE_3]         = /*"4��  3��  2��"*/"4\x8E  3\x82  2\x8A",
  [STR_SETTING]         = /*"����"*/"\xAD\xAB",
  [STR_LANG_CHS]        = /*"��������"*/"\xA7\x84\x82\x99",
  [STR_LANG_ENG]        = "English",
  [STR_ABOUT]           = /*"����"*/"\x89\x83"
};

/** Replaced strings:
      �����������ͣ���ȹ������ͷ����Ӧ����Ϸ���ְ�����˹������Ȩ���������ι����̼򼶽����������볬�ֽ���˳��

String Lookup Table:
     Char: �� �� �� �� �� �� ͣ �� �� �� �� �� �� ͷ �� �� 
    Value: 80 81 82 83 84 85 86 87 88 89 8A 8B 8C 8D 8E 8F 
     Char: �� Ӧ �� �� Ϸ �� �� �� �� �� ˹ �� �� �� Ȩ �� 
    Value: 90 91 92 93 94 95 96 97 98 99 9A 9B 9C 9D 9E 9F 
     Char: �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� 
    Value: A0 A1 A2 A3 A4 A5 A6 A7 A8 A9 AA AB AC AD AE AF 
     Char: �� �� �� ˳ �� 
    Value: B0 B1 B2 B3 B4 
*/