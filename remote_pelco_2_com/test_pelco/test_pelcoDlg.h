
// test_pelcoDlg.h : header file
//
#include <afxsock.h>
#include "Pelco_D.h"
#include "CameraDSet.h"

#pragma once


// Ctest_pelcoDlg dialog
class Ctest_pelcoDlg : public CDialogEx
{
// Construction
public:
	Ctest_pelcoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_PELCO_DIALOG };

	CSocket *m_pSocket;
	CSocket *m_pSocket1;

	CSocket *m_pSocketUdp;
	CSocket *m_pSocketUdp1;

	Pelco_D_Protocol::CPelco_D	m_Pelco_D;

	CameraDSet CamerSet;
	unsigned char SendData[8];
	unsigned int address;
	unsigned int para;

	int m_nComAddr, m_nSpeed;
	int m_panPos, m_tiltPos, m_zoomPos, m_zoomLimit;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedZoomin();
	afx_msg void OnBnClickedZoomout();
	afx_msg void OnBnClickedSetZeroPos();
	int V_Address;
	int V_Para;
	afx_msg void OnBnClickedRecoder();
	afx_msg void OnBnClickedStopRecoder();
	afx_msg void OnBnClickedButtonPresetSave();
	afx_msg void OnBnClickedButtonPresetRecall();

	afx_msg void OnBnClickedButtonpoweron();
	afx_msg void OnBnClickedButtonpoweroff();
	int V_left;

	CString UartIp;
	CString UartIp1;

	CString V_DeviceNum;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton14();
	int m_limit_para;
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonDown();
	int m_iris_data;
	afx_msg void OnBnClickedButtonIrisrun();
	afx_msg void OnBnClickedButtonIrismode();
	CString m_initinfo;
	CString m_cameraip;
	int m_zoomspeed;
	int m_focusspeed;
	afx_msg void OnBnClickedButtonZoomdown();
	afx_msg void OnBnClickedButtonZoomup();
	afx_msg void OnBnClickedButtonFocuseup();
	afx_msg void OnBnClickedButtonFocusedown();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	FILE *pFileRecall ;
	afx_msg void OnBnClickedDelpreser();
};
