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
  [STR_ABOUT_0]         = "Super Joystick 1.0",
  [STR_ABOUT_1]         = "lxyppc@163.com",
  [STR_ABOUT_2]         = "All rights reserved",
  [STR_MOUSE_0]         = "R1 - Scorll Up",
  [STR_MOUSE_1]         = "R2 - Scroll Down",
  [STR_MOUSE_2]         = "Buttons:",
  [STR_MOUSE_3]         = "4-Left 3-Mid 2-Right",
  [STR_SETTING]         = "Setting",
  [STR_LANG_CHS]        = /*"��������"*/"\xB3\x86\x82\xA0",
  [STR_LANG_ENG]        = "English",
  [STR_ABOUT]           = "About",
  [STR_AIR_MOUSE_0]     = "Press 1, then",
  [STR_AIR_MOUSE_1]     = "rotate, make",
  [STR_AIR_MOUSE_2]     = "ball out of",
  [STR_AIR_MOUSE_3]     = "the inner box",
};

const LPCSTR StringTable_CHS[STR_LAST] ={	
  [STR_CAMERA_ON]       = /*"����ͷ��"*/"\x9F\x89\x93\x98",
  [STR_CAMERA_OFF]      = /*"����ͷ��"*/"\x9F\x89\x93\x8B",
  [STR_JOYSTICK]        = /*"��Ϸ�ֱ�"*/"\xAD\x9A\x9C\xA8",
  [STR_MOUSE]           = /*"���"*/"\xC2\xA9",
  [STR_AIR_MOUSE]       = /*"��Ӧ���"*/"\x99\x97\xC2\xA9",
  [STR_KEYBOARD]        = /*"����"*/"\xC0\xB1",
  [STR_KB_NORMAL]       = /*"����"*/"\xAB\x95",
  [STR_KB_SEQ]          = /*"˳��"*/"\xC1\x96",
  [STR_TETRIS]          = /*"����˹����"*/"\x87\xB6\xA1\xA2\x92",
  [STR_TETRIS_PAUSE]    = /*"��Ϸ��ͣ    "*/"\xAD\x9A\xA4\x88    ",
  [STR_TETRIS_OVER]     = /*"��Ϸ����    "*/"\xAD\x9A\xB5\xA7    ",
  [STR_TETRIS_PLAY]     = /*"��Ϸ������.."*/"\xAD\x9A\xBF\xB8\x82..",
  [STR_TETRIS_SWITCH]   = /*"������ͣ��Ϸ!"*/"\xBB\x8A\xA4\x88\xAD\x9A!",
  [STR_ABOUT_0]         = /*"�����ֱ� 1.0"*/"\xBC\xB4\x9C\xA8 1.0",
  [STR_ABOUT_1]         = "lxyppc@163.com",
  [STR_ABOUT_2]         = /*"��Ȩ����"*/"\xAF\xA6\x9B\xA5",
  [STR_MOUSE_0]         = /*"R1 - ��������"*/"R1 - \xAE\xBE\x91\x80",
  [STR_MOUSE_1]         = /*"R2 - ��������"*/"R2 - \xAE\xBE\x91\x81",
  [STR_MOUSE_2]         = /*"����:"*/"\x9D\xC0:",
  [STR_MOUSE_3]         = /*"4��  3��  2��"*/"4\x94  3\x82  2\x8F",
  [STR_SETTING]         = /*"����"*/"\xBA\xB7",
  [STR_LANG_CHS]        = /*"��������"*/"\xB3\x86\x82\xA0",
  [STR_LANG_ENG]        = "English",
  [STR_ABOUT]           = /*"����"*/"\x8B\x83",
  [STR_AIR_MOUSE_0]     = /*"��ס1������ת"*/"\x9D\x85\x31\xC0\x90\xA3\xBD",
  [STR_AIR_MOUSE_1]     = /*"�ֱ�,�����Ƴ�"*/"\x9C\xA8,\xB9\xB0\xB2\x8D",
  [STR_AIR_MOUSE_2]     = /*"�ڿ�,�Դ˿���"*/"\x8C\xAA,\x84\xAC\x9E\x8E",
  [STR_AIR_MOUSE_3]     = /*"���"*/"\xC2\xA9",
};

/** Replaced strings:
      ����������ס���ͣ���ȹ��ڳ����Һ����ͷ����Ӧ����Ϸ���ְ�������˹��������Ȩ������������ι��������Ƽ򼶽������������볬ת�ֽ���˳��

String Lookup Table:
     Char: �� �� �� �� �� ס �� �� ͣ �� �� �� �� �� �� �� 
    Value: 80 81 82 83 84 85 86 87 88 89 8A 8B 8C 8D 8E 8F 
     Char: �� �� �� ͷ �� �� �� Ӧ �� �� Ϸ �� �� �� �� �� 
    Value: 90 91 92 93 94 95 96 97 98 99 9A 9B 9C 9D 9E 9F 
     Char: �� ˹ �� �� �� �� Ȩ �� �� �� �� �� �� �� �� �� 
    Value: A0 A1 A2 A3 A4 A5 A6 A7 A8 A9 AA AB AC AD AE AF 
     Char: �� �� �� �� �� �� �� �� �� �� �� �� �� ת �� �� 
    Value: B0 B1 B2 B3 B4 B5 B6 B7 B8 B9 BA BB BC BD BE BF 
     Char: �� ˳ �� 
    Value: C0 C1 C2 
*/
