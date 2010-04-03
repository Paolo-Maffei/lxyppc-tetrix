/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  GOL Layer
 *  DigitalMeter
 *****************************************************************************
 * FileName:        DigitalMeter.c
 * Dependencies:    None
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright � 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Arpan kumar		  06/11/09	  Version 1.0 release
*****************************************************************************/
#include "Graphics\Graphics.h"

#ifdef USE_DIGITALMETER
	   


/************************************************************************************
* Function: NumberToString(DWORD Value,XCHAR *pText, BYTE NoOfDigits, BYTE DotPos )
*
* Notes: convert the number to string
*
*************************************************************************************/
static void NumberToString(DWORD Value,XCHAR *pText, BYTE NoOfDigits, BYTE DotPos )
{
	 
	BYTE    i;
    BYTE    bIndex;

    for(bIndex = 0; bIndex < NoOfDigits; bIndex++)
	{
	 pText[NoOfDigits - bIndex - 1] = '0' + (Value % 10);
	 Value /= 10;
	}
	if(DotPos != 0 && DotPos<=NoOfDigits)
	{
	    for(i=0; i<DotPos; i++)
		{
		 pText[NoOfDigits-i] = pText[NoOfDigits - 1-i];
		}
	 pText[NoOfDigits - DotPos] = '.';
	 pText[NoOfDigits + 1] = '\0';
	}
    //If dot position is 0 or greater than number of digits, then don't put dot in the display
	else		
	{
	 pText[NoOfDigits] = '\0';
	}

}

/*********************************************************************************************************
* Function: DIGITALMETER  *DmCreate(WORD ID, SHORT left, SHORT top, SHORT right, SHORT bottom, WORD state,
*                               DWORD Value, BYTE NoOfDigits, BYTE DotPos, GOL_SCHEME *pScheme)
*
* Notes: Creates a DIGITALMETER object and adds it to the current active list.
*        If the creation is successful, the pointer to the created Object
*        is returned. If not successful, NULL is returned.
*
**********************************************************************************************************/
DIGITALMETER *DmCreate(WORD ID, SHORT left, SHORT top, SHORT right, SHORT bottom, WORD state,
                   DWORD Value, BYTE NoOfDigits, BYTE DotPos, GOL_SCHEME *pScheme)
{
    DIGITALMETER *pDm=NULL;
 	pDm = malloc(sizeof(DIGITALMETER));
	if (pDm == NULL)
		return pDm;
		
 
	pDm->hdr.ID      	= ID;                   // unique id assigned for referencing
	pDm->hdr.pNxtObj 	= NULL;                 // initialize pointer to NULL
	pDm->hdr.type    	= OBJ_DIGITALMETER;         // set object type
	pDm->hdr.left    	= left;                 // left,top corner
	pDm->hdr.top     	= top;
	pDm->hdr.right   	= right;                // right buttom corner
	pDm->hdr.bottom  	= bottom;
	pDm->Cvalue   		= Value;                // initial value to be displayed
	pDm->hdr.state   	= state;
	pDm->NoOfDigits   	= NoOfDigits;           // number of digits to be displayed
	pDm->DotPos   	    = DotPos;               // position of decimal point

	// Set the color scheme to be used
	if (pScheme == NULL)
		pDm->hdr.pGolScheme = _pDefaultGolScheme;
	else
		pDm->hdr.pGolScheme = (GOL_SCHEME *)pScheme;

	pDm->textHeight 	= 0;
	if (pDm->Cvalue  != 0) 
     {
		// Set the text height
		pDm->textHeight 	= GetTextHeight(pDm->hdr.pGolScheme->pFont);
	 }

    GOLAddObject((OBJ_HEADER*) pDm);

	return pDm;
}

/*********************************************************************
* Function: DmSetValue(DIGITALMETER *pDm, DWORD Value)
*
* Notes: Sets the value to be displayed.
*
********************************************************************/
void DmSetValue(DIGITALMETER *pDm, DWORD Value)
{
    // store the previous and current value to be displayed
    pDm->Pvalue   		= pDm->Cvalue; 
   	pDm->Cvalue   		= Value;  
   	              
	pDm->textHeight     = GetTextHeight(pDm->hdr.pGolScheme->pFont);
}

/*********************************************************************
* Function: WORD DmTranslateMsg(DIGITALMETER *pDm, GOL_MSG *pMsg)
*
* Notes: Evaluates the message if the object will be affected by the
*		 message or not.
*
**********************************************************************/
WORD DmTranslateMsg(DIGITALMETER *pDm, GOL_MSG *pMsg)
{
    // Evaluate if the message is for the static text
    // Check if disabled first
	if (GetState(pDm, DM_DISABLED))
        return OBJ_MSG_INVALID;

#ifdef  USE_TOUCHSCREEN
    if(pMsg->type == TYPE_TOUCHSCREEN) {
        // Check if it falls in static text control borders
		if( (pDm->hdr.left     < pMsg->param1) &&
	  	    (pDm->hdr.right    > pMsg->param1) &&
	   	    (pDm->hdr.top      < pMsg->param2) &&
	   	    (pDm->hdr.bottom   > pMsg->param2) ) {

    		return DM_MSG_SELECTED;
        }
	}
#endif

	return OBJ_MSG_INVALID;
}

/*********************************************************************
* Function: WORD DmDraw(DIGITALMETER *pDm)
*
* Notes: This is the state machine to display the changing numbers.
*
**********************************************************************/
WORD DmDraw(DIGITALMETER *pDigMeter)
{
typedef enum 
{
	DM_STATE_IDLE,
	DM_STATE_INIT,
	DM_STATE_SETALIGN,
	DM_STATE_DRAWTEXT
} DM_DRAW_STATES;

static DIGITALMETER *pDm = NULL;
static DM_DRAW_STATES state = DM_STATE_IDLE;
static SHORT charCtr = 0, lineCtr = 0;
static XCHAR CurValue[DM_WIDTH] , PreValue[DM_WIDTH];
       SHORT   textWidth=0;
       XCHAR   ch=0,pch=0;

pDm = pDigMeter;

    if(IsDeviceBusy())
        return 0;

    switch(state)
    {

        case DM_STATE_IDLE:

            SetClip(CLIP_DISABLE);

           	if (GetState(pDm, DM_HIDE)) 
            {
   	   	        SetColor(pDm->hdr.pGolScheme->CommonBkColor);
    	        if(Bar(pDm->hdr.left,pDm->hdr.top,pDm->hdr.right,pDm->hdr.bottom) == 0) return 0;
    	        // State is still IDLE STATE so no need to set
    	        return 1;
    	    }

	       	if (GetState(pDm, DM_FRAME)) 
    	     {
		       	// show frame if specified to be shown
   	   	        SetLineType(SOLID_LINE);
   	   	        SetLineThickness(NORMAL_LINE);
	             if(!GetState(pDm,DM_DISABLED))
    	         {
		            // show enabled color
    	   	        SetColor(pDm->hdr.pGolScheme->Color1);
	    	        if(Rectangle(pDm->hdr.left,pDm->hdr.top,pDm->hdr.right,pDm->hdr.bottom) == 0) return 0;
                 }
	             else 
    	         {
       	        	// show disabled color
    	   	        SetColor(pDm->hdr.pGolScheme->ColorDisabled);
		            if(Rectangle(pDm->hdr.left,pDm->hdr.top,pDm->hdr.right,pDm->hdr.bottom) == 0) return 0;
    	         }
    	     }
    	    // set clipping area, text will only appear inside the static text area.
            SetClip(CLIP_ENABLE);
            SetClipRgn(pDm->hdr.left+DM_INDENT, pDm->hdr.top,   		\
                       pDm->hdr.right-DM_INDENT, pDm->hdr.bottom);
            state = DM_STATE_INIT;



        case DM_STATE_INIT:

            if(IsDeviceBusy())
                return 0;
                
            // set the text color
	        if(!GetState(pDm,DM_DISABLED))
    	    {
	   	        SetColor(pDm->hdr.pGolScheme->TextColor0);
	        }
	        else 
    	    {
	   	        SetColor(pDm->hdr.pGolScheme->TextColorDisabled);
	        }
                     
           // convert the values to be displayed in string format
            NumberToString( pDm->Pvalue, PreValue, pDm->NoOfDigits, pDm->DotPos);
            NumberToString( pDm->Cvalue, CurValue, pDm->NoOfDigits, pDm->DotPos);
        
           // use the font specified in the object
	        SetFont(pDm->hdr.pGolScheme->pFont);
	                     
			state = DM_STATE_SETALIGN;                  // go to drawing of text
			
			

        case DM_STATE_SETALIGN:

            	if (!charCtr) {
                // set position of the next character (based on alignment and next character)
			    textWidth = GetTextWidth(CurValue, pDm->hdr.pGolScheme->pFont);

                // Display text with center alignment
				if (GetState(pDm, (DM_CENTER_ALIGN))) {
					MoveTo((pDm->hdr.left+pDm->hdr.right-textWidth) >> 1,	\
					       pDm->hdr.top+(lineCtr * pDm->textHeight));
				}
                // Display text with right alignment
				else if (GetState(pDm, (DM_RIGHT_ALIGN))) {
					MoveTo((pDm->hdr.right-textWidth-DM_INDENT), 		\
					        pDm->hdr.top+(lineCtr * pDm->textHeight));
				}
                // Display text with left alignment
				else {
					MoveTo(pDm->hdr.left+DM_INDENT, 					\
					       pDm->hdr.top+(lineCtr * pDm->textHeight));
				}
			}
			state = DM_STATE_DRAWTEXT;
			
        case DM_STATE_DRAWTEXT:

            pch = *(PreValue + charCtr);
			ch = *(CurValue + charCtr);

            // output one character at time until a newline character or a NULL character is sampled
		    while((0x0000 != ch) ) 
    		{
		        if(IsDeviceBusy()) 
    		    {
			        return 0;                           // device is busy return
			    } 

                if(pch!=ch)
                {
                    SetColor(pDm->hdr.pGolScheme->CommonBkColor);
                    if(Bar(GetX(),pDm->hdr.top + 1,GetX()+textWidth,pDm->hdr.bottom-1) == 0) return 0;
                }
                SetColor(pDm->hdr.pGolScheme->TextColor0);

 			 // render the character
                while(!OutChar(ch));
		        charCtr++;                                  // update to next character
				ch = *(CurValue + charCtr);
				pch = *(PreValue + charCtr);

		    }

			// end of text string is reached no more lines to display

				lineCtr = 0;
				charCtr = 0;
	            SetClip(CLIP_DISABLE);                      // remove clipping
				state = DM_STATE_IDLE;                      // go back to IDLE state

				return 1;
	}
    return 1;
}

#endif      // USE_DIGITALMETER
