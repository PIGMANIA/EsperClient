
// EsperClientDlg.cpp : 구현 파일
//
#include "afxdialogex.h"
#include "stdafx.h"
#include "EsperClient.h"
#include "EsperClientDlg.h"

#include "WrapDlg.h"
#include "SettingDlg.h"
#include "strsafe.h"
#include "Communication.h"
#include <fstream>
#include <cstring>
#include "AccessDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDH_TRAYICON 0x01
#define YM_FROMTRAY WM_USER+1



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32775();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::On32775()
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_32775, &CAboutDlg::On32775)
END_MESSAGE_MAP()


// CEsperClientDlg 대화 상자

void CEsperClientDlg::SetId(std::string param_id)
{
	m_userid = param_id;
}

CEsperClientDlg::CEsperClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ESPERCLIENT_DIALOG, pParent), m_strEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_oldpos.x = m_oldpos.y = 0;
	m_isOpen = true;
}

void CEsperClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//DDX_Control(pDX, IDC_EDIT1, m_ebMsg);
	//DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	DDX_Control(pDX, IDC_WRAPBUTTON, m_wrapButton);
	DDX_Control(pDX, IDC_REFRESHBUTTON, m_refreshButton);
}

BEGIN_MESSAGE_MAP(CEsperClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(YM_FROMTRAY, OnMsgFromTray)
//	ON_EN_CHANGE(IDC_EDIT1, &CEsperClientDlg::OnEnChangeEdit1)
//ON_LBN_SELCHANGE(IDC_LIST1, &CEsperClientDlg::OnLbnSelchangeList1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CEsperClientDlg::OnTvnSelchangedTree1)
	ON_COMMAND(ID_MENU_WRAPPING, &CEsperClientDlg::OnMenuWrapping)
	ON_COMMAND(ID_SETTING, &CEsperClientDlg::OnSetting)
	ON_COMMAND(ID_TRAY_OPEN, &CEsperClientDlg::OnTrayOpen)
	ON_COMMAND(ID_TRAY_SETTINGS, &CEsperClientDlg::OnTraySettings)
	ON_COMMAND(ID_TRAY_INFO, &CEsperClientDlg::OnTrayInfo)
	ON_COMMAND(ID_TRAY_LOGOUT, &CEsperClientDlg::OnTrayLogout)
	ON_COMMAND(ID_TRAY_EXIT, &CEsperClientDlg::OnTrayExit)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()

	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CEsperClientDlg::OnNMRClickTree1)
	ON_COMMAND(ID_TREESELECT_ACCESS, &CEsperClientDlg::OnTreeselectAccess)
	ON_COMMAND(ID_TREESELECT_DELETE, &CEsperClientDlg::OnTreeselectDelete)
	ON_BN_CLICKED(IDC_WRAPBUTTON, &CEsperClientDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_REFRESHBUTTON, &CEsperClientDlg::OnBnClickedRefreshbutton)
END_MESSAGE_MAP()




// CEsperClientDlg 메시지 처리기

BOOL CEsperClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);
	/*
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
	}*/

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.

	//Tree control 아이콘 설정
	
	
	
	
	
	

	



	m_hIcon = NULL;
	//SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	//SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	NOTIFYICONDATA st_taskbaricon = { 0, };
	st_taskbaricon.cbSize = sizeof(NOTIFYICONDATA);
	st_taskbaricon.hWnd = this->GetSafeHwnd();
	st_taskbaricon.uID = IDH_TRAYICON;
	st_taskbaricon.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_MESSAGE;
	st_taskbaricon.hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	st_taskbaricon.uCallbackMessage = YM_FROMTRAY;

	strcpy(st_taskbaricon.szTip,"ESPER Client - developing version");
	strcpy(st_taskbaricon.szInfoTitle, "ESPER");
	strcpy(st_taskbaricon.szInfo, "ESPER Client - developing version");

	st_taskbaricon.uVersion = NOTIFYICON_VERSION;
	st_taskbaricon.dwInfoFlags = NIIF_USER;

	::Shell_NotifyIcon(NIM_ADD, &st_taskbaricon);

	CFont m_font;

	m_font.CreateFont(40, // nHeight 
		30, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		30, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		"굴림"); // lpszFacename 
	//GetDlgItem(IDC_STATIC)->SetFont(&m_font);
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/*
	//버튼 이미지 불러오기
	CImage WrapImage;
	HRESULT res = WrapImage.Load(_T(".\\res\\Arrow0a.ico"));
	if (res != S_OK)
	{
		
	}

	HBITMAP bit;
	bit = WrapImage.Detach();

	m_wrapButton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_wrapButton.m_bTransparent = FALSE;
	m_wrapButton.m_bDrawFocus = FALSE;
	m_wrapButton.SetImage(bit, TRUE, NULL);
	m_wrapButton.SetMouseCursorHand();
	*/

	//통신
	
	SOCKET s = socketCreate();
	if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);
	/*
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4500);
	addr.sin_addr.s_addr = inet_addr("165.132.144.106");
	//if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
	//	AfxMessageBox(_T("connection(dir) error!"), MB_OK);
	//}*/

	//char c_userid[20] = { 0, }, c_sessionkey[20] = { 0, };
	ifstream fin;
	fin.open("C:\\Program Files (x86)\\Esper\\idsk.txt");
	fin >> m_userid >> m_sessionkey;

	Items item;
	item.UserId = m_userid;	
	item.SessionKey = m_sessionkey;
	

	string str,str2;
	if (sockSetting(s) == -1)
		AfxMessageBox(_T("connection error!"), MB_OK);
	else {
		
		socket_send(s, "fileListReq", item);
		string result[20];

		//if()
		
		socket_recv(s, &str);
		
		/*
		AfxMessageBox((LPCTSTR)str.c_str(), MB_OK);
		AfxMessageBox(finfo[0].fileId.c_str());
		AfxMessageBox(finfo[0].del.c_str());
		AfxMessageBox(finfo[0].fileName.c_str());
		AfxMessageBox(finfo[0].userId[0].c_str());
		*/
		//AfxMessageBox(str.c_str(), MB_OK);
		//AfxMessageBox(resultpacketbuffer1.c_str(), MB_OK);
		//AfxMessageBox(resultpacketbuffer2.c_str(), MB_OK);
		//AfxMessageBox(m_userid.c_str(), MB_OK);
		//AfxMessageBox(m_sessionkey.c_str(), MB_OK);
		
		
		str2 = "file1 : ";
		for (unsigned int i = 0; i < finfo[0].userId.size();i++)
			str2.append(finfo[0].userId[i]);
		str2.append(", ");
		str2.append(finfo[0].fileId);
		str2.append(", ");
		str2.append(finfo[0].del);
		

		//AfxMessageBox((LPCTSTR)str2.c_str(), MB_OK);
		

		
		//TREE 만들기
		
		//m_hRoot = new HTREEITEM[2];
		//m_hKind = new HTREEITEM[5];
		m_hRoot = new HTREEITEM[10];
		m_hKind = new HTREEITEM[10];

		m_ImageList1.Create(16, 16, ILC_MASK, 2, 2);
		m_bitmap1.LoadBitmapA(IDB_FILE);
		m_bitmap2.LoadBitmapA(IDB_USER);
		m_ImageList1.Add(&m_bitmap1, RGB(255, 0, 255));
		m_ImageList1.Add(&m_bitmap2, RGB(255, 0, 255));
		/*
		m_Tree.SetImageList(&m_ImageList1, 0);
		
		m_hRoot[0] = m_Tree.InsertItem(_T("test.hwp"), 0, 0);
		m_hRoot[1] = m_Tree.InsertItem(_T("test2.hwp"), 0, 0);
		//m_Tree.SetFont(&m_font,1);

		
		
		
		m_Tree.SetImageList(&m_ImageList1, 1);
		m_hKind[0] = m_Tree.InsertItem(_T("idophio"), 1, 1, m_hRoot[0], TVI_LAST);
		m_hKind[1] = m_Tree.InsertItem(_T("sangwoo"), 1, 1, m_hRoot[0], TVI_LAST);
		m_hKind[2] = m_Tree.InsertItem(_T("jwyang"), 1, 1, m_hRoot[0], TVI_LAST);
		//m_hKind[3] = m_Tree.InsertItem(_T("사람4"), 2, 2, m_hRoot[0], TVI_LAST);

		m_hKind[0] = m_Tree.InsertItem(_T("idophio"), 1, 1, m_hRoot[1], TVI_LAST);
		m_hKind[1] = m_Tree.InsertItem(_T("khkim"), 1, 1, m_hRoot[1], TVI_LAST);
		m_hKind[2] = m_Tree.InsertItem(_T("jmhan"), 1, 1, m_hRoot[1], TVI_LAST);
		//m_hKind[3] = m_Tree.InsertItem(_T("사람8"), 2, 2, m_hRoot[1], TVI_LAST);
		
		//m_Tree.Expand(m_hRoot[0], TVE_EXPAND);
		//m_Tree.Expand(m_hRoot[1], TVE_EXPAND);
		*/

		int length = flength;		
		//AfxMessageBox(std::to_string(length).c_str());

		

		//AfxMessageBox(finfo[3].userId[0].c_str());
		//AfxMessageBox(finfo[3].fileId.c_str());
		for (unsigned int i = 0; i < length;i++)
		{
			//AfxMessageBox(_T("Round"));
			m_Tree.SetImageList(&m_ImageList1, 0);
			
			m_hRoot[i] = m_Tree.InsertItem(finfo[i].fileName.c_str(),0,0);
			
			//m_hRoot[i] = m_Tree.InsertItem(_T("abc"), 0, 1);
			/*
			TVINSERTSTRUCT tvInsert;
			tvInsert.hParent = NULL;
			tvInsert.hInsertAfter = TVI_LAST;
			tvInsert.item.mask = TVIF_TEXT;
			tvInsert.item.state = 0;
			tvInsert.item.stateMask = 0;
			tvInsert.item.cchTextMax = 60;
			tvInsert.item.lParam = i;
			tvInsert.item.cChildren = 0;
			LPSTR s = const_cast<char *>(finfo[i].fileName.c_str());
			tvInsert.item.pszText = s;

			m_hRoot[i] = m_Tree.InsertItem(&tvInsert);*/

			//AfxMessageBox(finfo[i].fileName.c_str());
			//m_hKind = new HTREEITEM[finfo[i].userId.size()];
			//AfxMessageBox(std::to_string(finfo[i].userId.size()).c_str());

			string strUserid;
			for (unsigned int j = 0; j < finfo[i].userId.size(); j++)			
			{			
				//m_Tree.SetImageList(&m_ImageList1, 1);
				
				strUserid = finfo[i].userId[j].substr(1, finfo[i].userId[j].length() - 3);
				m_hKind[j] = m_Tree.InsertItem(strUserid.c_str(), 1, 1, m_hRoot[i], TVI_LAST);
				
								
			}
				
			//AfxMessageBox(_T("Clear"));
		}		

		closesocket(s);
		WSACleanup();

		return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
	}
}

void CEsperClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEsperClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CEsperClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CEsperClientDlg::OnMsgFromTray(WPARAM wParam, LPARAM lParam)
{
	/* CString str;
	str.Format(_T("YM_FROMTRAY	%04x	%04x\r\n"), wParam, lParam);
	UpdateData(TRUE);
	m_strEdit += str;
	UpdateData(FALSE);
	m_ebMsg.LineScroll(m_ebMsg.GetLineCount());*/

	if (wParam == IDH_TRAYICON)
		if (lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN)
		{
			POINT pos;
			CMenu m_menu2;
			m_menu2.LoadMenu(IDR_TRAY);
			::GetCursorPos(&pos);
			::SetForegroundWindow(this->GetSafeHwnd());
			m_menu2.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);
			
			::SetForegroundWindow(this->GetSafeHwnd ());

		}
		else if (lParam == WM_LBUTTONDBLCLK)
		{
			ShowWindow(SW_SHOW);
			//SetFocus();
		}

	if (m_isOpen) {
		ShowWindow(SW_SHOW);
	}
	else
		ShowWindow(SW_HIDE);

	return 0;
}

void CEsperClientDlg::OnEnChangeEdit1()
{
	
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CEsperClientDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CEsperClientDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

}


void CEsperClientDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CEsperClientDlg::OnMenuWrapping()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 랩핑 메뉴

	CFileDialog dialog((BOOL)TRUE, _T("hwp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("한글파일(*.hwp)|*.hwp|모든파일(*.*)|*.*||"));


	dialog.m_ofn.lpstrTitle = _T("파일 랩핑하기");
	dialog.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12;
	
	
	if (IDOK == dialog.DoModal()) {
		CWrapDlg wDialog(dialog.GetFileName(),dialog.GetPathName());
		wDialog.SetId(m_userid);
		wDialog.DoModal();
	}

}



void CEsperClientDlg::OnSetting()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 환경설정
	CSettingDlg dialog1;
	dialog1.SetId(m_userid);
	dialog1.DoModal();
}


void CEsperClientDlg::OnTrayOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isOpen)
		m_isOpen = false;
	else
		m_isOpen = true;
}


void CEsperClientDlg::OnTraySettings()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSettingDlg dialog1;
	dialog1.SetId(m_userid);
	dialog1.DoModal();
}


void CEsperClientDlg::OnTrayInfo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CEsperClientDlg::OnTrayLogout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CEsperClientDlg::OnTrayExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	DestroyWindow();
	CDialog::OnClose();
	

}


void CEsperClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_oldpos = point;
	SetCapture();
	CDialog::OnLButtonDown(nFlags, point);
}

void CEsperClientDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default	
	if (nFlags == MK_LBUTTON)
	{
		RECT rect;
		POINT offset;

		this->GetWindowRect(&rect);
		offset.x = point.x - m_oldpos.x;
		offset.y = point.y - m_oldpos.y;

		rect.left += offset.x; rect.right += offset.x;
		rect.top += offset.y; rect.bottom += offset.y;

		MoveWindow(&rect, 1);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CEsperClientDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}


void CEsperClientDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selId;
	HTREEITEM hItem;
	TV_HITTESTINFO hit_info;

	// 화면상에서 마우스의 위치를 얻는다.
	::GetCursorPos(&hit_info.pt);

	// 얻은 마우스 좌표를 트리컨트롤 기준의 좌표로 변경한다.
	::ScreenToClient(m_Tree.m_hWnd, &hit_info.pt);

	// 현재 마우스 좌표가 위치한 항목 정보를 얻는다.
	HTREEITEM current_item = m_Tree.HitTest(&hit_info);
	if (current_item != NULL) {
		// 마우스가 위치한 항목을 찾았다면 해당 항목을 선택한다.
		m_Tree.Select(current_item, TVGN_CARET);
		selId = m_Tree.GetItemText(current_item);
		hItem = m_Tree.GetSelectedItem();

		//if (hItem == m_hRoot[0] or hItem == m_hRoot[1])
		{
			CPoint p;
			GetCursorPos(&p);
			CMenu menu;
			menu.LoadMenu(IDR_TREESELECT_MENU);
			CMenu* Dmenu = menu.GetSubMenu(0); //맨 앞에 메뉴를 가져옴
			Dmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
		}

	}

	

	*pResult = 0;
}


void CEsperClientDlg::OnTreeselectAccess()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAccessDlg dlg;
	HTREEITEM selitem = m_Tree.GetSelectedItem();

	
	TVITEM tvItem = { 0 };
	tvItem.mask = TVIF_PARAM;
	tvItem.hItem = selitem;
	m_Tree.GetItem(&tvItem);

	int index = (int)tvItem.lParam;
	CString cs;
	cs.Format(_T("%d"), index);
	//AfxMessageBox(cs);
	
	std::string filename((string)m_Tree.GetItemText(selitem));
	std::string fileid;
	cs.Format(_T("%d"), flength);
	//AfxMessageBox(cs);
	for (int i = 0; i < flength; i++)
	{
		if (finfo[i].fileName.compare(filename) == 0)
		{
			fileid = finfo[i].fileId;
			//AfxMessageBox(_T("hit!"));
			break;
		}
			

	}
 

	dlg.setFilename(filename);
	dlg.setFileid(fileid);
	//AfxMessageBox(fileid.c_str());
	dlg.DoModal();
	
}


void CEsperClientDlg::OnTreeselectDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	HTREEITEM selitem = m_Tree.GetSelectedItem();
	
	std::string filename((string)m_Tree.GetItemText(selitem));
	std::string fileid;
	//cs.Format(_T("%d"), flength);
	//AfxMessageBox(cs);
	for (int i = 0; i < flength; i++)
	{
		if (finfo[i].fileName.compare(filename) == 0)
		{
			fileid = finfo[i].fileId;
			//AfxMessageBox(_T("hit!"));
			break;
		}

	}

	//AfxMessageBox(fileid.c_str());

	std::string m_message = filename;
	m_message.append("을 모든 유저로부터 삭제하시겠습니까?");
	if (AfxMessageBox(m_message.c_str(), MB_YESNO) == IDYES)
	{
		SOCKET s = socketCreate();
		if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);
		
		ifstream fin;
		fin.open("C:\\Program Files (x86)\\Esper\\idsk.txt");
		fin >> m_userid >> m_sessionkey;

		Items item;
		item.UserId = m_userid;
		fileid = fileid.substr(0, fileid.length() - 1);
		item.FileId = fileid;
		item.SessionKey = m_sessionkey;
		//finfo[].

		/*
		//  fileId 찾기
		for (int i = 0; i < flength; i++)
		{
			if (finfo[i].fileName == filename)
				item.FileId = finfo[i].fileId;
		}
		*/
		
		string str;
		if (sockSetting(s) == -1)
			AfxMessageBox(_T("connection error!"), MB_OK);
		else {
			socket_send(s, "remoteDel", item);
			string result[20];
			
			//if()

			socket_recv(s, &str);
			//AfxMessageBox(str.c_str());
			

			if (resultpacketbuffer1 == "succ")
			{
				AfxMessageBox(_T("원격 삭제가 완료되었습니다."));
			}
			else
			{
				AfxMessageBox(_T("원격 삭제에 실패했습니다."));
			}
		}
	}
		
}


void CEsperClientDlg::OnBnClickedMfcbutton1() // = OnBnClickedWrapbutton
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->OnMenuWrapping();

}


void CEsperClientDlg::OnBnClickedRefreshbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	
	CEsperClientDlg dlg;
	dlg.SetId(m_userid);
	ShowWindow(SW_HIDE);
	dlg.DoModal();

	
	
}
