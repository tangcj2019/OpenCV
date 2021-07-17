
// MOpencvDlg.h: 头文件
//

#pragma once


// CMOpencvDlg 对话框
class CMOpencvDlg : public CDialogEx
{
// 构造
public:
	CMOpencvDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenvideobtn();
	afx_msg void OnBnClickedOpenmp4();
	afx_msg void OnBnClickedopenimg();
	afx_msg void OnBnClickedFacedetect();
	afx_msg void OnBnClickedopenqt();
};
