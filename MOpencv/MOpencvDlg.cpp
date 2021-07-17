
// MOpencvDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MOpencv.h"
#include "MOpencvDlg.h"
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMOpencvDlg 对话框



CMOpencvDlg::CMOpencvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMOpencvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMOpencvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenVideoBtn, &CMOpencvDlg::OnBnClickedOpenvideobtn)
	ON_BN_CLICKED(IDC_OpenMP4, &CMOpencvDlg::OnBnClickedOpenmp4)
	ON_BN_CLICKED(IDC_openImg, &CMOpencvDlg::OnBnClickedopenimg)
	ON_BN_CLICKED(IDC_FaceDetect, &CMOpencvDlg::OnBnClickedFacedetect)
	ON_BN_CLICKED(IDC_openQt, &CMOpencvDlg::OnBnClickedopenqt)
END_MESSAGE_MAP()


// CMOpencvDlg 消息处理程序

BOOL CMOpencvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMOpencvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMOpencvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMOpencvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开本地摄像头
void CMOpencvDlg::OnBnClickedOpenvideobtn()
{
	VideoCapture capture(0);
	Mat frame;
	while (true)
	{
		capture.read(frame);
		flip(frame, frame, 1);//镜像
		if (frame.empty())
		{
			break;
		}
		imshow("frmew", frame);
		int c = waitKey(1);
		if (c == 27)
		{
			break;
		}
	}
}


void CMOpencvDlg::OnBnClickedOpenmp4()
{
	VideoCapture capture("D:/OpenCVPrj/MOpencv/images/钢琴1.MP4");
	//视频的属性
	//分辨率-清晰度
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	// 总帧数，一秒钟15帧是流畅的，
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	int fps = capture.get(CAP_PROP_FPS);

	//保存视频
	VideoWriter writer("D:/OpenCVPrj/opecvDemo/save/save2.MP4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);


	Mat frame;
	while (true)
	{
		capture.read(frame);
		flip(frame, frame, 1);//镜像
		if (frame.empty())
		{
			break;
		}
		imshow("frmew", frame);

		//保存视频
		writer.write(frame);

		int c = waitKey(1);
		if (c == 27)
		{
			break;
		}
	}
	capture.release();
	writer.release();

}


void CMOpencvDlg::OnBnClickedopenimg()
{
	Mat src = imread("D:/OpenCVPrj/MOpencv/images/1.jpg");
	imshow("input", src);
}

//D:\ProgramData\opencv\sources\samples\dnn\face_detector
void CMOpencvDlg::OnBnClickedFacedetect()
{
	string root_dir = "D:/ProgramData/opencv/sources/samples/dnn/face_detector/";
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb",root_dir+"opencv_face_detector.pbtxt");
	VideoCapture capture(0);

	Mat frame;
	while (true)
	{
		capture.read(frame);
		flip(frame, frame, 1);//镜像
		if (frame.empty())
		{
			break;
		}
	//1.读取模型
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104,177,123), false, false);
	//2.准备数据	
		net.setInput(blob);
	//3.完成推理
		Mat probs = net.forward();
		Mat detectionMat(probs.size[2], probs.size[3],CV_32F, probs.ptr<float>());
	//4.解析结果
		for (int i = 0; i < detectionMat.rows; i++)
		{
			float confidence = detectionMat.at<float>(i,2);
			if (confidence > 0.5)
			{
				int x1 = static_cast<int>(detectionMat.at<float>(i,3)*frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2= static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2= static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
				Rect box(x1,y1,x2-x1,y2-y1);
				rectangle(frame,box,Scalar(0,0,255),2,8,0);

			}
		}

		imshow("人脸检测演示",frame);

		int c = waitKey(1);
		if (c == 27)
		{
			break;
		}
	}
	capture.release();
	
	
}


void CMOpencvDlg::OnBnClickedopenqt()
{
	// TODO: 在此添加控件通知处理程序代码
}
