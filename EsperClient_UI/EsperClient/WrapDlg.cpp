// WrapDlg.cpp : 구현 파일입니다.
//
#include "afxdialogex.h"
#include "stdafx.h"
#include "EsperClient.h"
#include "WrapDlg.h"
#include <time.h>

#include "FileLayer.h"
#include "Communication.h"

// CWrapDlg 대화 상자입니다.
Items item;
IMPLEMENT_DYNAMIC(CWrapDlg, CDialog)

CWrapDlg::CWrapDlg(CString filename, CString filepath, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WrapDlg, pParent), Filename(filename), Filepath(filepath)
{

}

CWrapDlg::~CWrapDlg()
{
}

void CWrapDlg::SetId(std::string param)
{
	m_userid = param;
}

void CWrapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_authlistctrl);
}


BEGIN_MESSAGE_MAP(CWrapDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CWrapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CWrapDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_WRAP_FILENAME, &CWrapDlg::OnStnClickedWrapFilename)
END_MESSAGE_MAP()


// CWrapDlg 메시지 처리기입니다.


BOOL CWrapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText(_T("Wrap"));
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_WRAP_FILENAME, Filename);
	SetDlgItemText(IDC_WRAP_FILEPATH, Filepath);
	CString  m_userid2(m_userid.c_str());
	SetDlgItemText(IDC_WRAP_USER, m_userid2);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void CWrapDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	CT2CA temp(str);
	string tempstr(temp);
	ifstream fin;
	fin.open("C:\\Program Files (x86)\\Esper\\idsk.txt");
	fin >> m_userid >> m_sessionkey;
	item.AccessorID = tempstr;
	item.setId(m_userid);
	item.SessionKey = m_sessionkey;
	
	//통신 목표 설정
	SOCKET s = socketCreate();
	if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4500);
	addr.sin_addr.s_addr = inet_addr("165.132.144.106");
	//if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
	//	AfxMessageBox(_T("connection(dir) error!"), MB_OK);
	//}

	if (sockSetting(s) == -1)
		AfxMessageBox(_T("connection error!"), MB_OK);
	else {
		socket_send(s, "accessorCheck", item);
		//closesocket(s);
		//ShowWindow(SW_HIDE);
	}
	std::string strtemp;
	socket_recv(s, &strtemp);

	if (resultpacketbuffer1 == "succ")
	{
		m_authlistctrl.AddString(str);
		UpdateData(TRUE);
		item.Accessor.push_back(tempstr);
	}
	else if (resultpacketbuffer1 == "fail")
	{
		AfxMessageBox(_T("잘못된 아이디입니다."));
	}
	else
	{
		AfxMessageBox(_T("서버와 통신이 실패했습니다."));
		::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}

	//closesocket(s);
}


void CWrapDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();

	CString SubFilename = Filename.Mid(0, (Filename.GetLength() - 4));
	CFileDialog dialog((BOOL)FALSE, _T("esp"), SubFilename + _T(".esp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("에스퍼(*.esp)|*.esp|모든파일(*.*)|*.*||"));
	AfxMessageBox(SubFilename, MB_OK);
	AfxMessageBox(Filename, MB_OK);

	dialog.m_ofn.lpstrTitle = _T("파일 랩핑하기");
	dialog.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12;
	dialog.DoModal();


	//Items item;
	item.setId(m_userid);

	item.SessionKey = m_sessionkey;


	//시간 측정
	int begin[200], begin2[200], end[200], end2[200], start, finish;

	//통신 목표 설정
	SOCKET s = socketCreate();
	if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4500);
	addr.sin_addr.s_addr = inet_addr("165.132.120.126");
	//if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
	//	AfxMessageBox(_T("connection(dir) error!"), MB_OK);
	//}

	if (sockSetting(s) == -1)
		AfxMessageBox(_T("connection error!"), MB_OK);
	else {
		socket_send(s, "wrappingReq", item);
		//closesocket(s);
		//ShowWindow(SW_HIDE);
	}

	string strtemp;
	socket_recv(s, &strtemp);

	if (resultpacketbuffer2 == "succ")
	{
		
		ST_FILE_LAYER_HEADER stFileLayerHeader;
		stFileLayerHeader.dwServerId = atoi(resultpacketbuffer1.c_str());
		AfxMessageBox(resultpacketbuffer1.c_str());
		stFileLayerHeader.dwUserId = atoi(m_userid.c_str());
		
		CString outPath = dialog.GetFolderPath();
		CT2CA pszConvertedAnsiString(Filepath), pszConvertedAnsiString2(outPath);
		
		std::string strInputFile(pszConvertedAnsiString);
		//std::string strInputFile("C:\\Users\\wooPC\\Desktop\\hello.hwp");
		std::string strOutputFile(pszConvertedAnsiString2);
		AfxMessageBox(strOutputFile.c_str());
		//std::string strOutputFile("C:\\Users\\wooPC\\Desktop\\abc");
		DWORD dwRet = EncryptFileLayer(stFileLayerHeader, strInputFile, strOutputFile);

		item.FileId = resultpacketbuffer1;
		item.WrappingResult = "succ";
		item.SessionKey = m_sessionkey;
		item.Filed = strInputFile;
		
		
		
		item.FileName = Filename;

		socket_send(s, "wrappingRes", item);
		string strtemp;
		socket_recv(s, &strtemp);

		if (resultpacketbuffer1 == "succ")
		{
			//////////////////////////////
			
			
		}
		else
		{
			wstring temp = wstring(strOutputFile.begin(), strOutputFile.end());
			CString outfilePath = temp.c_str();
			DeleteFile(outfilePath);
			AfxMessageBox(_T("서버와 통신이 실패했습니다.1"));
		}

	}
	else
	{
		AfxMessageBox(_T("서버와 통신이 실패했습니다.2"));
	}

	closesocket(s);
	
	/*
	//반복 테스트 코드 

	for (int i = 0; i < 200 ; i++) {

		//통신 목표 설정
		SOCKET s = socketCreate();
		if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);

		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(4500);
		addr.sin_addr.s_addr = inet_addr("165.132.144.106");
		//if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
		//	AfxMessageBox(_T("connection(dir) error!"), MB_OK);
		//}

		if (sockSetting(s) == -1)
			AfxMessageBox(_T("connection error!"), MB_OK);
		else {
			begin[i] = clock();
			socket_send(s, "wrappingReq", item);
			//closesocket(s);
			//ShowWindow(SW_HIDE);
		}

		string strtemp;
		socket_recv(s, &strtemp);
		end[i] = clock();

		if (resultpacketbuffer2 == "succ")
		{

			ST_FILE_LAYER_HEADER stFileLayerHeader;
			stFileLayerHeader.dwServerId = atoi(resultpacketbuffer1.c_str());
			//AfxMessageBox(resultpacketbuffer1.c_str());
			stFileLayerHeader.dwUserId = 1;

			CT2CA pszConvertedAnsiString(Filepath), pszConvertedAnsiString2(dialog.GetFolderPath());
			std::string strInputFile(pszConvertedAnsiString);
			//std::string strInputFile("C:\\Users\\wooPC\\Desktop\\hello.hwp");
			std::string strOutputFile(pszConvertedAnsiString2);
			//std::string strOutputFile("C:\\Users\\wooPC\\Desktop");
			//DWORD dwRet = EncryptFileLayer(stFileLayerHeader, strInputFile, strOutputFile);

			item.FileId = resultpacketbuffer1;
			item.WrappingResult = "succ";
			item.SessionKey = m_sessionkey;
			item.Filed = strInputFile;



			item.FileName = Filename;

			begin2[i] = clock();
			socket_send(s, "wrappingRes", item);
			string strtemp;
			socket_recv(s, &strtemp);
			end2[i] = clock();

			if (resultpacketbuffer1 == "succ")
			{

			}
			else
			{
				wstring temp = wstring(strOutputFile.begin(), strOutputFile.end());
				CString outfilePath = temp.c_str();
				DeleteFile(outfilePath);
				AfxMessageBox(_T("서버와 통신이 실패했습니다."));
			}

		}
		else
		{
			AfxMessageBox(_T("서버와 통신이 실패했습니다."));
		}

		closesocket(s);

	}
	double time;
	for (int i = 0;i < 200;i++)
	time = (begin[i] + begin2[i] - end[i] - end2[i]);

	time = time / CLOCKS_PER_SEC;
	string message = "Duration for 200 times is " + std::to_string(time) + ".";
	AfxMessageBox(message.c_str());*/

}


void CWrapDlg::OnStnClickedWrapFilename()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
