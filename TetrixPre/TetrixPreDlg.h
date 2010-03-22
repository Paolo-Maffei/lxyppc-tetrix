// TetrixPreDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Stream.h"


// CTetrixPreDlg �Ի���
class CTetrixPreDlg : public CDialog
{
// ����
public:
	CTetrixPreDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TETRIXPRE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedTest();
    CStatic m_pic;
    afx_msg void OnBnClickedLoad();
    afx_msg void OnBnClickedSave();
    CImage  m_image;
    afx_msg void OnTimer(UINT nIDEvent);
    int     m_keyCode;
    CStatic m_picDbg;
};

void    GenerateJpeg(const char* fileName);


