
// test_pelcoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test_pelco.h"
#include "test_pelcoDlg.h"
#include "afxdialogex.h"

#include "CameraDSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define DEVICE2   //Select software device 1 or 2
//#define PORTDEVICE



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctest_pelcoDlg dialog




Ctest_pelcoDlg::Ctest_pelcoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_pelcoDlg::IDD, pParent)
	, V_Address(0)
	, V_Para(0)
	, V_left(0)
	, UartIp(_T(""))
	, V_DeviceNum(_T(""))
	, m_limit_para(0)
	, m_iris_data(0)
	, m_initinfo(_T(""))
	, m_cameraip(_T(""))
	, m_zoomspeed(0)
	, m_focusspeed(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest_pelcoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SPEED, V_Address);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, V_Para);
	DDX_Text(pDX, IDC_EDIT_ADDRESS2, V_left);
	DDX_Text(pDX, IDC_EDIT1, UartIp);
	DDX_Text(pDX, IDC_EDIT4, V_DeviceNum);
	DDX_Text(pDX, IDC_EDIT2, m_limit_para);
	DDX_Text(pDX, IDC_EDIT3, m_iris_data);
	DDX_Text(pDX, IDC_EDIT6, m_initinfo);
	DDX_Text(pDX, IDC_EDIT5, m_cameraip);
	DDX_Text(pDX, IDC_EDIT7, m_zoomspeed);
	DDX_Text(pDX, IDC_EDIT8, m_focusspeed);
}

BEGIN_MESSAGE_MAP(Ctest_pelcoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Connect, &Ctest_pelcoDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_Left, &Ctest_pelcoDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_Right, &Ctest_pelcoDlg::OnBnClickedRight)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_Stop, &Ctest_pelcoDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_Up, &Ctest_pelcoDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_Down, &Ctest_pelcoDlg::OnBnClickedDown)
	ON_BN_CLICKED(IDC_ZoomIn, &Ctest_pelcoDlg::OnBnClickedZoomin)
	ON_BN_CLICKED(IDC_ZoomOut, &Ctest_pelcoDlg::OnBnClickedZoomout)
	ON_BN_CLICKED(IDC_SetZeroPan, &Ctest_pelcoDlg::OnBnClickedSetZeroPos)
	ON_BN_CLICKED(IDC_BUTTON1, &Ctest_pelcoDlg::OnBnClickedRecoder)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctest_pelcoDlg::OnBnClickedStopRecoder)
	ON_BN_CLICKED(IDC_BUTTONPRESETSAVE, &Ctest_pelcoDlg::OnBnClickedButtonPresetSave)
	ON_BN_CLICKED(IDC_BUTTONPRESETRECALL, &Ctest_pelcoDlg::OnBnClickedButtonPresetRecall)
	ON_BN_CLICKED(IDC_BUTTONPOWERON, &Ctest_pelcoDlg::OnBnClickedButtonpoweron)
	ON_BN_CLICKED(IDC_BUTTONPOWEROFF, &Ctest_pelcoDlg::OnBnClickedButtonpoweroff)
	ON_BN_CLICKED(IDC_BUTTON9, &Ctest_pelcoDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON14, &Ctest_pelcoDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &Ctest_pelcoDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_UP, &Ctest_pelcoDlg::OnBnClickedButtonUp)
	//ON_WM_LBUTTONDOWN(IDC_BUTTON_UP, &Ctest_pelcoDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &Ctest_pelcoDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &Ctest_pelcoDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_IRISRUN, &Ctest_pelcoDlg::OnBnClickedButtonIrisrun)
	ON_BN_CLICKED(IDC_BUTTON_IRISMODE, &Ctest_pelcoDlg::OnBnClickedButtonIrismode)
	ON_BN_CLICKED(IDC_BUTTON_ZOOMDOWN, &Ctest_pelcoDlg::OnBnClickedButtonZoomdown)
	ON_BN_CLICKED(IDC_BUTTON_ZOOMUP, &Ctest_pelcoDlg::OnBnClickedButtonZoomup)
	ON_BN_CLICKED(IDC_BUTTON_FOCUSEUP, &Ctest_pelcoDlg::OnBnClickedButtonFocuseup)
	ON_BN_CLICKED(IDC_BUTTON_FOCUSEDOWN, &Ctest_pelcoDlg::OnBnClickedButtonFocusedown)
	ON_BN_CLICKED(IDC_DELPRESER, &Ctest_pelcoDlg::OnBnClickedDelpreser)
END_MESSAGE_MAP()


// Ctest_pelcoDlg message handlers
BOOL Ctest_pelcoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// init socket
	m_pSocket = NULL;
	m_pSocket1 = NULL;

	m_pSocketUdp = NULL;
	m_pSocketUdp1 = NULL;

	pFileRecall = NULL;

	m_nComAddr = 1;
	m_nSpeed = 20 * 0x3f / 100;  // 64 levels: 0-63
    
	m_panPos = 0;
	m_tiltPos = 0; 
	m_zoomPos = 1;
	m_zoomLimit = 30;
	
	V_Para = 80;
	V_left = 80;
	V_Address = 1;

	m_iris_data = 20;
	m_zoomspeed = 30;
	m_focusspeed = 30;

	UartIp = "192.168.1.200";
	UartIp1 = "192.168.1.2";
#if defined DEVICE1
	m_initinfo = "Please connect device 1 !!";
#elif defined DEVICE2
	m_initinfo = "Please connect device 2 !!";
#else
	m_initinfo = "Please connect device Port !!";
#endif
	
    CString strTemp;
	int i = 0;
	int iline = 0;
   ((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();//消除现有所有内容

    pFileRecall = fopen("rerecal.ini","rb+");
	if( !pFileRecall )
	{
		//dont find recal file
		MessageBox(_T("Must get rerecal.ini file !!"));
		exit(0);
	}
	else
	{   char pBuf[4];
		fread(pBuf, 1, 1, pFileRecall );
		i = atoi(pBuf) + 1;
	}
	fclose(pFileRecall);
	for(iline = 0 ; iline < i ;  iline ++ )
	{
		strTemp.Format(_T("%0.2d-Mode"),iline );
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(strTemp);
	}
	
   ((CComboBox*)GetDlgItem( IDC_COMBOIRIS ))->ResetContent();//消除现有所有内容

    strTemp.Format(_T("AUTO-Mode"),i);
    ((CComboBox*)GetDlgItem(IDC_COMBOIRIS))->AddString(strTemp);
    strTemp.Format(_T("HAND-Mode"),i);
    ((CComboBox*)GetDlgItem(IDC_COMBOIRIS))->AddString(strTemp);

	UpdateData( false );

	if (!AfxSocketInit())
	{
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ctest_pelcoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	char pBuf[4];
	int i,error;

	//save recall data to file
	pFileRecall = fopen("rerecal.ini","rb+");
	if(pFileRecall != NULL)
	{   
        i = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();//取得目前已经有的行数
		itoa( i-1 , pBuf , 10);
		error = fwrite( pBuf, sizeof(char) , 4  , pFileRecall );
	}
    fclose(pFileRecall);

	// TODO: Add your message handler code here
	if (m_pSocket!=NULL)
	{
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket = NULL;
	}
	if (m_pSocket1!=NULL)
	{
		m_pSocket1->Close();
		delete m_pSocket1;
		m_pSocket1 = NULL;
	}
	if (m_pSocketUdp1!=NULL)
	{
		m_pSocketUdp1->Close();
		delete m_pSocketUdp1;
		m_pSocketUdp1 = NULL;
	}
	if (m_pSocketUdp!=NULL)
	{
		m_pSocketUdp->Close();
		delete m_pSocketUdp;
		m_pSocketUdp = NULL;
	}

}


void Ctest_pelcoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ctest_pelcoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ctest_pelcoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ctest_pelcoDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	// = "192.168.1.200";
	UpdateData( true );

	CString str = UartIp.Right( UartIp.GetLength() - 1 - UartIp.ReverseFind('.') );
	CString Ddpip;

	int data = _ttoi( str );
	if( (data + 3) >= 254  )
	{
		MessageBox(_T("IP Address must less 254"));
		return ;
	}

	CString str1 = _T("");
	str1.Format( _T("%d") , ( _ttoi( str ) + 1 ) );
	UartIp1 =  UartIp.Left( UartIp.ReverseFind('.') + 1 ) +  str1;	
	Ddpip = UartIp1;

	if (m_pSocketUdp == NULL)
	{

#ifdef PORTDEVICE
	//unsigned char ZlDevID1[] ={ 0x5a , 0x4c , 0xcd ,0x0b ,0xae ,0x54 }; //4 口 的ID port 1
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4c , 0xcd ,0x06 ,0xae ,0x5b }; //4 口 的ID port 2
	unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x33 ,0x14 ,0x50 ,0x7c };
	unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x33 ,0x11 ,0x57 ,0x25 }; //4 口 的ID port 2

#elif defined DEVICE1
	//// DEVICE 1
	unsigned char ZlDevID1[] ={ 0x5a , 0x4c , 0xf3 ,0x6e ,0x97 ,0xb3 };   //2 口 的ID port 1  
	unsigned char ZlDevID2[] ={ 0x5a , 0x4c , 0xf3 ,0xa8 ,0x96 ,0x71 };   //2 口 的ID port 2
#elif defined DEVICE2
	//// DEVICE 2
	//unsigned char ZlDevID1[] ={ 0x5a , 0x4c , 0xf1 ,0x9a ,0x68 ,0xe8 };   //2 口 的ID port 1  
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4c , 0xf3 ,0x9a ,0x96 ,0xef };   //2 口 的ID port 2
#if 0
	//// For network device 1
	unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x41 ,0xa5 ,0x58 ,0x52 };   //2 口 的ID port 1  
	unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x41 ,0x9e ,0x58 ,0xc3 };   //2 口 的ID port 2

	//// For network device 2
	unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x41 ,0x9d ,0x58 ,0x1a };   //2 口 的ID port 1  
	unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x41 ,0x9c ,0x58 ,0xf5 };   //2 口 的ID port 2
#endif 
#if 0
	//// For network device 3
	unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x41 ,0xaa ,0x5f ,0x9f };   //2 口 的ID port 1  
	unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x41 ,0xa2 ,0x5f ,0x27 };   //2 口 的ID port 2

#endif 
	//// For network device 4
	//unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x41 ,0xa9 ,0x58 ,0x76 };   //2 口 的ID port 1  
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x41 ,0xa1 ,0x58 ,0x7e };   //2 口 的ID port 2


		//// For network device 5
	//unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x94 ,0x65 ,0xe1 ,0x6f };   //2 口 的ID port 1  
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x94 ,0x95 ,0xe7 ,0xff };   //2 口 的ID port 2

		//// For network device 6
//	unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x94 ,0xa3 ,0xe7 ,0x79 };   //2 口 的ID port 1  
//	unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x94 ,0x58 ,0xe1 ,0x06 };   //2 口 的ID port 2


		//// For network device 7
	unsigned char ZlDevID1[] ={ 0x5A, 0x4D, 0xBD, 0x4B, 0xFE, 0x11  };   //2 口 的ID port 1  
	unsigned char ZlDevID2[] ={ 0x5A, 0x4D, 0xBD, 0x5B, 0xFE, 0x01 };   //2 口 的ID port 2
#else
	//// DEVICE For testing
	//unsigned char ZlDevID1[] ={ 0x5a , 0x4c , 0xcd ,0x0b ,0xae ,0x54 };   //2 口 的ID port 1  
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x41 ,0xa9 ,0x58 ,0x76 };   //2 口 的ID port 2
	//unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x33 ,0x14 ,0x50 ,0x7c };
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x33 ,0x11 ,0x57 ,0x25 }; //4 口 的ID port 2

	//unsigned char ZlDevID1[] ={ 0x5a , 0x4d , 0x41 ,0xa9 ,0x58 ,0x76 };
	//unsigned char ZlDevID2[] ={ 0x5a , 0x4d , 0x41 ,0xa1 ,0x58 ,0x7e }; //4 口 的ID port 2
#endif

		unsigned char send[256] ={0x5a,0x4c,0x04};
		unsigned char buf[256];
		memset(buf , 0 , 256);
		m_pSocketUdp = new CSocket;
		m_pSocketUdp->Create( 0 , SOCK_DGRAM , NULL );

		m_pSocketUdp->SendTo( send , sizeof(buf), 1092 ,UartIp , 0 );
		Sleep(50);
		m_pSocketUdp->ReceiveFrom(buf, sizeof(buf) , NULL, NULL);
#if 1
		//buf[ 0x22 + 6] = '\0';
		if(  (*( buf + 0x22) != ZlDevID1[0]) || (*( buf + 0x22 +1) != ZlDevID1[1]) 
			|| (*( buf + 0x22 +2) != ZlDevID1[2]) || (*( buf + 0x22 + 3) != ZlDevID1[3]) 
			|| (*( buf + 0x22 +4) != ZlDevID1[4]) || (*( buf + 0x22 + 5) != ZlDevID1[5]) )
		{
		   CString strinfo;
		   strinfo.Format(  _T("Device is not authorization !! Error Code1: %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x "),  *( buf + 0x22) , *( buf + 0x23) , *( buf + 0x24) ,*( buf + 0x25), *( buf + 0x26) , *( buf + 0x27)  ); 
		   MessageBox( strinfo );	
		   exit(0);
		}
#endif

#if 1
		/////////////////////////////////////////////////////////////////////////////////////////device 2
		m_pSocketUdp1 = new CSocket;
		unsigned char buf1[256];
		memset(buf1 ,  0 , 256);
		m_pSocketUdp1->Create( 0 , SOCK_DGRAM , NULL );
		m_pSocketUdp1->SendTo( send , sizeof(buf), 1092 , UartIp1 , 0 );
		Sleep(50);
		m_pSocketUdp1->ReceiveFrom(buf1, sizeof(buf1) , NULL , NULL  );
		if(  (*( buf1 + 0x22) != ZlDevID2[0]) || (*( buf1 + 0x22 +1) != ZlDevID2[1]) 
			|| (*( buf1 + 0x22 +2) != ZlDevID2[2]) || (*( buf1 + 0x22 +3) != ZlDevID2[3]) 
			|| (*( buf1 + 0x22 +4) != ZlDevID2[4]) || (*( buf1 + 0x22 +5) != ZlDevID2[5]) )
		{
		   CString strinfo;
		   strinfo.Format(  _T("Device is not authorization !! Error Code2: %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x "),  *( buf1 + 0x22) , *( buf1 + 0x23) , *( buf1 + 0x24) ,*( buf1 + 0x25), *( buf1 + 0x26) , *( buf1 + 0x27) ); 
		   MessageBox( strinfo );
		   exit(0);
		}
		//////////////////////////////////////////////////////////////////////////////////////////
#endif 

	}

	if (m_pSocket==NULL)
	{
		m_pSocket = new CSocket;
		m_pSocket->Create(0);
		if (m_pSocket->Connect( ( UartIp ), 4196)==0)                     // 云台 1
		{
			MessageBox(_T("Connect failed Device 1"));
		}
	}

#if 1
	if (m_pSocket1==NULL)
	{
		m_pSocket1 = new CSocket;
		m_pSocket1->Create(0);
		if (m_pSocket1->Connect( ( UartIp1 ), 4196)==0)                    //摄像机 1
		{
			MessageBox(_T("Connect failed Device 2"));
		}
	}
#endif 

	V_DeviceNum = UartIp;
	m_cameraip = UartIp1;
	m_initinfo = "Connect device is ok !!";
	UpdateData( false );
}

void Ctest_pelcoDlg::OnBnClickedLeft()
{
	// TODO: Add your control notification handler code here
	Ctest_pelcoDlg::OnBnClickedStop();


}


void Ctest_pelcoDlg::OnBnClickedRight()
{
	// TODO: Add your control notification handler code here
	 Ctest_pelcoDlg::OnBnClickedStop();

}


void Ctest_pelcoDlg::OnBnClickedUp()
{
	// TODO: Add your control notification handler code here
	Ctest_pelcoDlg::OnBnClickedStop();

}


void Ctest_pelcoDlg::OnBnClickedDown()
{
	// TODO: Add your control notification handler code here
	Ctest_pelcoDlg::OnBnClickedStop();

}

void Ctest_pelcoDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);
	 
	CamerSet.TiltRun( SendData , V_Address , 50 );
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

	CamerSet.PanRun( SendData , V_Address , 50 );  
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

}




void Ctest_pelcoDlg::OnBnClickedZoomin()
{
	// TODO: Add your control notification handler code here
	if (m_pSocket1==NULL) return;
	//Sleep( 20 );
	CamerSet.CameraSet( SendData , 0x25 );
	// send the message
	m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );

}

void Ctest_pelcoDlg::OnBnClickedZoomout()
{
	// TODO: Add your control notification handler code here
	if (m_pSocket1==NULL) return;
	CamerSet.CameraSet( SendData , 0x25 );
	m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );
}

void Ctest_pelcoDlg::OnBnClickedSetZeroPos()
{
	// TODO: Add your control notification handler code here
	BYTE* Message;

	if (m_pSocket1==NULL) return;

	UpdateData(true);	 
	CamerSet.CameraSet( SendData , 0x25  );
	// send the message
	m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );

}


void Ctest_pelcoDlg::OnBnClickedRecoder()
{
	// TODO: Add your control notification handler code here
	BYTE* Message;

	if (m_pSocket1==NULL) return;

	UpdateData(true);	 
	CamerSet.CameraRecod( SendData , 1  );
	// send the message
	m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );

}


void Ctest_pelcoDlg::OnBnClickedStopRecoder()
{
	// TODO: Add your control notification handler code here
	BYTE* Message;

	if (m_pSocket1==NULL) return;

	UpdateData(true);	 
	CamerSet.CameraRecod( SendData , 0  );
	// send the message
	m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );
}


void Ctest_pelcoDlg::OnBnClickedButtonPresetSave()
{
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);	
	CString strTemp;
	//int iCount=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
    int iCount=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();//取得目前已经有的行数
    if( iCount < 100 )//防止重复多次添加
    {
          strTemp.Format(_T("%0.2d-Mode"), iCount );
          ((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(strTemp);
    }
	else
	{	
			MessageBox(_T("PreSet Number must is 0 -- 99 ! failed"));
	}

	CamerSet.PresetSave( SendData , V_Address  , iCount );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

}


void Ctest_pelcoDlg::OnBnClickedButtonPresetRecall()
{
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);	 

	int iCount=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	CamerSet.PresetRecall( SendData , V_Address , iCount  );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

}

void Ctest_pelcoDlg::OnBnClickedDelpreser()
{
	// TODO: Add your control notification handler code here
	int index;
	if (m_pSocket==NULL) return;

	UpdateData(true);	 
	index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->DeleteString(index - 1) ;
	UpdateData(false);
}


void Ctest_pelcoDlg::OnBnClickedButtonpoweron()
{
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);	 
	CamerSet.PowerSet( SendData , V_Address , 1  );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

}


void Ctest_pelcoDlg::OnBnClickedButtonpoweroff()
{
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);	 
	CamerSet.PowerSet( SendData , V_Address , 0  );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );
}


void Ctest_pelcoDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//if ( V_DeviceNum == 1 )


	UpdateData(false);
}


void Ctest_pelcoDlg::OnBnClickedButton14()
{
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);	 
	CamerSet.LimitSet( SendData , V_Address , m_limit_para  );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );


}


void Ctest_pelcoDlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSocket==NULL) return;
	UpdateData(true);
	m_limit_para = 3;
	UpdateData(false);
}


void Ctest_pelcoDlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSocket==NULL) return;
	UpdateData(true);
	m_limit_para = 1;
	UpdateData(false);
}


void Ctest_pelcoDlg::OnBnClickedButtonRight()
{
	if (m_pSocket==NULL) return;
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_limit_para = 4;
	UpdateData(false);
}


void Ctest_pelcoDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSocket==NULL) return;
	UpdateData(true);
	m_limit_para = 2;
	UpdateData(false);
}


void Ctest_pelcoDlg::OnBnClickedButtonIrisrun()
{
	// TODO: 在此添加控件通知处理程序代码	
	BYTE* Message;

	if (m_pSocket==NULL) return;

	UpdateData(true);	 
	if(( m_iris_data > 99)||(m_iris_data < 1) )
	{
		MessageBox(_T("IrisRun Number must is 0 -- 99 ! failed"));
		return;
	}    
	CamerSet.IrisRun( SendData , V_Address , m_iris_data  );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

}


void Ctest_pelcoDlg::OnBnClickedButtonIrismode()
{
	// TODO: 在此添加控件通知处理程序代码	
	BYTE* Message;
	int irismode = 0;

	if (m_pSocket==NULL) return;
	UpdateData(true);

	int iCount=((CComboBox*)GetDlgItem(IDC_COMBOIRIS))->GetCurSel();//取得目前已经有的行数
    if( iCount == 0 )//防止重复多次添加
	{
		irismode = 31;
	}
	else if (  iCount == 1 )
	{	
		irismode = 30;
	}
	else 
	{
		MessageBox(_T("Please Select Iris Mode! HAND or AUTO "));
		return;		
	}
 
	CamerSet.IrisRun( SendData , V_Address ,  irismode );
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );
}


void Ctest_pelcoDlg::OnBnClickedButtonZoomdown()
{
	memset( SendData , 0 , sizeof(SendData) );

	if (m_pSocket==NULL) return;
	// create the message
	UpdateData(true);

	CamerSet.ZoomRun( SendData , V_Address , 50 + m_zoomspeed/2 );  
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );
}


void Ctest_pelcoDlg::OnBnClickedButtonZoomup()
{
	memset( SendData , 0 , sizeof(SendData) );

	if (m_pSocket==NULL) return;
	// create the message
	UpdateData(true);

	CamerSet.ZoomRun( SendData , V_Address , 50 + m_zoomspeed/2 );  
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );
}


void Ctest_pelcoDlg::OnBnClickedButtonFocuseup()
{
	memset( SendData , 0 , sizeof(SendData) );

	if (m_pSocket==NULL) return;
	// create the message
	UpdateData(true);

	CamerSet.FocusRun( SendData , V_Address , 50 + m_focusspeed/2 );  
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );
}


void Ctest_pelcoDlg::OnBnClickedButtonFocusedown()
{
	memset( SendData , 0 , sizeof(SendData) );

	if (m_pSocket==NULL) return;
	// create the message
	UpdateData(true);
 
	CamerSet.FocusRun( SendData , V_Address , 50 + m_focusspeed/2 );  
	// send the message
	m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );
}


BOOL Ctest_pelcoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	 if(pMsg->message==WM_LBUTTONDOWN)  
	 {

		 if(pMsg->hwnd == GetDlgItem( IDC_Up)->m_hWnd)
		 {
			if (m_pSocket==NULL) return FALSE;
			BYTE* Message;
			UpdateData(true);	 
			CamerSet.TiltRun( SendData , V_Address , 50 + V_Para /2  );
			m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );		 

		 }
		 if(pMsg->hwnd == GetDlgItem( IDC_Down)->m_hWnd)
		 {
			if (m_pSocket==NULL) return FALSE;
			BYTE* Message;
			UpdateData(true);	 
			CamerSet.TiltRun( SendData , V_Address , 50 - V_Para/2 );
			m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );		

		 }
		 if(pMsg->hwnd == GetDlgItem( IDC_Left)->m_hWnd)
		 {
			if (m_pSocket==NULL) return FALSE;
			memset( SendData , 0 , sizeof(SendData) );
			UpdateData(true);
			CamerSet.PanRun( SendData , V_Address , 50 - V_left/2 );  
			m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

		 }
		 if(pMsg->hwnd == GetDlgItem( IDC_Right)->m_hWnd)
		 {
			if (m_pSocket==NULL) return FALSE;
			BYTE* Message;
			UpdateData(true);	 
			CamerSet.PanRun( SendData , V_Address , 50 + V_left/2 );
			m_pSocket->Send( (BYTE *)SendData , sizeof(SendData) );

		 }


		 if(pMsg->hwnd == GetDlgItem( IDC_ZoomIn)->m_hWnd)
		 {
			if (m_pSocket1==NULL) return FALSE;
			BYTE* Message;
			UpdateData(true);	 
			CamerSet.CameraSet( SendData , 0x55 );
			m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );

		 }
		 if(pMsg->hwnd == GetDlgItem( IDC_ZoomOut)->m_hWnd)
		 {
    		if (m_pSocket1==NULL) return FALSE;
			BYTE* Message;
			UpdateData(true);	 
			CamerSet.CameraSet( SendData , 0x5  );
			m_pSocket1->Send( (BYTE *)SendData , sizeof(SendData) );		 
		 }
	 
	 }

	return FALSE;
	//return CDialogEx::PreTranslateMessage(pMsg);
}


