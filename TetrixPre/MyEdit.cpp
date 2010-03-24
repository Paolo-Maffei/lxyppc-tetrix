// MyEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TetrixPre.h"
#include "MyEdit.h"
#include ".\myedit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)
CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
    ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CMyEdit ��Ϣ�������


void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    switch(nChar){
        case 'w'://Up
        case 'W':
            GetParent()->PostMessage(WM_PLAYACTION,3,0);
            return;
        case 'a'://Left
        case 'A':
            GetParent()->PostMessage(WM_PLAYACTION,1,0);
            return;
        case 's'://Down
        case 'S':
            GetParent()->PostMessage(WM_PLAYACTION,4,0);
            return;
        case 'd':
        case 'D'://Right
            GetParent()->PostMessage(WM_PLAYACTION,2,0);
            return;
        case 'p':
        case 'P':
            GetParent()->PostMessage(WM_PLAYACTION,5,0);
            return;
        default:
            break;
    }
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
