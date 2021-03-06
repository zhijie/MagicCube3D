// MagicCube3DView.cpp : implementation of the CMagicCube3DView class
//

#include "stdafx.h"
#include "MagicCube3D.h"

#include "MagicCube3DDoc.h"
#include "MagicCube3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMagicCube3DView

IMPLEMENT_DYNCREATE(CMagicCube3DView, CView)

BEGIN_MESSAGE_MAP(CMagicCube3DView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_NEW, &CMagicCube3DView::OnGameNew)
	ON_COMMAND(ID_FILE_SHUFFLE, &CMagicCube3DView::OnShuffle)
	ON_COMMAND(ID_FILE_RESTORE, &CMagicCube3DView::OnRestoreMagicCube)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_COMMAND(ID_FILE_SAVE32773, &CMagicCube3DView::OnSave)
	ON_COMMAND(ID_FILE_OPEN32774, &CMagicCube3DView::OnOpen)
	ON_COMMAND(ID_FILE_FIGURECUBE, &CMagicCube3DView::OnFigureCube)
END_MESSAGE_MAP()

// CMagicCube3DView construction/destruction

CMagicCube3DView::CMagicCube3DView():shuffledNum(0),figurePtr(0)
{
	// TODO: add construction code here
	srand(unsigned(time(NULL)));
}

CMagicCube3DView::~CMagicCube3DView()
{
}

BOOL CMagicCube3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMagicCube3DView drawing

void CMagicCube3DView::OnDraw(CDC* /*pDC*/)
{
	CMagicCube3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMagicCube3DView printing

BOOL CMagicCube3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMagicCube3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMagicCube3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMagicCube3DView diagnostics

#ifdef _DEBUG
void CMagicCube3DView::AssertValid() const
{
	CView::AssertValid();
}

void CMagicCube3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMagicCube3DDoc* CMagicCube3DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMagicCube3DDoc)));
	return (CMagicCube3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CMagicCube3DView message handlers

void CMagicCube3DView::OnClose()
{
	
	
	CView::OnClose();
}

void CMagicCube3DView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	((CMagicCube3DApp*)AfxGetApp())->openGL.Init();
	((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.initialize();
}

int CMagicCube3DView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	((CMagicCube3DApp*)AfxGetApp())->openGL.SetupPixelFormat(::GetDC(m_hWnd));

	return 0;
}

void CMagicCube3DView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	int height=cy;
	int width=cx;
	if (height==0){
		height=1;
	}
	((CMagicCube3DApp*)AfxGetApp())->openGL.Reshape(width,height);
}

void CMagicCube3DView::OnTimer(UINT_PTR nIDEvent)
{
	//because the nondeterministic feature of timer event,I rotate 
	//color table first ,then let update cube rotate from negative 
	//position to current position
	const static char asp[6]={'F','B','L','R','U','D'};
	if (nIDEvent==timerRotate){//rotate
		if (rotateInfo.angle<0){
			rotateInfo.angle+=rotateStep;
			((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
		}else{
			rotateInfo.angle=0;
			((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
			KillTimer(timerRotate);
		}
	}else if (nIDEvent==timerShuffle){//shuffle
		if (shuffledNum<totleShuffleNum){
			shuffledNum++;
			rotateInfo.type=asp[rand()%6];
			rotateInfo.reversed=rand()%2;
			//rotate color table
			Executor();
		}else{
			KillTimer(timerShuffle);
			shuffledNum=0;
		}
	}else if (nIDEvent==timerRestore){//restore
		if (restoredPos<restoreString.GetLength()){			
			Restore_UpdateRotateInfo();
			Executor();
		}else{
			KillTimer(timerRestore);
		}
	}	
	CView::OnTimer(nIDEvent);
}

void CMagicCube3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	

	CView::OnLButtonDown(nFlags, point);
}

void CMagicCube3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	

	CView::OnLButtonUp(nFlags, point);
}

void CMagicCube3DView::OnMouseMove(UINT nFlags, CPoint point)
{
	

	CView::OnMouseMove(nFlags, point);
}

void CMagicCube3DView::OnGameNew()
{
	KillTimer(timerRestore);
	KillTimer(timerRotate);
	KillTimer(timerShuffle);
	((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.initialize();	
}

void CMagicCube3DView::OnShuffle()
{	
	SetTimer(timerShuffle,rotateInterval,NULL);
}

//resemble Executor,except it turns command string into RotateInfo
//restoredPos and rotateInfo will be modified and restoreString is used.
void CMagicCube3DView::Restore_UpdateRotateInfo()
{
	//commands are assume legal here
	//while(restoreString[restoredPos]=='#'){//
	//		
	//	restoredPos++;
	//}
	bool goon=true;
	while(goon&&restoredPos<restoreString.GetLength()){
		switch(restoreString[restoredPos]){						
			case '2'://continue previous rotate state
				goon=false;
				break;
			case '#':
				do{
					restoredPos++;
				}while (restoreString[restoredPos]!='#'&&
					restoredPos<restoreString.GetLength());
				break;
			case 'F':
			case 'B':
			case 'L':
			case 'R':
			case 'U':
			case 'D':
			case 'x':
			case 'y':
			case 'z':
			case 'u':
			case 'r':
			case 'f':
			case 'd':
			case 'l':
			case 'b':
			case 'E':
			case 'M':
			case 'S':
				rotateInfo.reversed=0;
				rotateInfo.type=restoreString[restoredPos];
				if (restoreString[restoredPos+1]=='\''){
					rotateInfo.reversed=1;
					restoredPos++;
				}
				goon=false;
				break;
			default:
				break;	
		}
		restoredPos++;
	}
	if (goon){
		rotateInfo.type='\0';
	}
}

void CMagicCube3DView::Executor()
{
	rotateInfo.angle=-90;
	((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
	((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.rotateColor();
	SetTimer(timerRotate,rotateStepInterval,NULL);
}
void CMagicCube3DView::OnRestoreMagicCube()
{
	restoreString=((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.restore();
	restoredPos=0;
	//rotate
	SetTimer(timerRestore,rotateInterval,NULL);
	
	//test
	/*int len=restoreString.GetLength();
	while (restoredPos<len){
		Restore_UpdateRotateInfo();
		((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.setRotateInfo(rotateInfo);
		((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.rotateColor();
	}*/
}

//for test
void CMagicCube3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMagicCube3DView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	rotateInfo.type=nChar;
	Executor();
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CMagicCube3DView::OnSave()
{
	CFileDialog fileDlg(false,NULL,NULL,4|2,"MagicCube Layout Files(*.ml)|*.ml||");
	if (fileDlg.DoModal()==IDOK){
		CString filename=fileDlg.GetPathName();
		CString ext=fileDlg.GetFileExt();
		if (ext!="ml"){
			filename.Append(".ml");
		}
		CFile fileout(filename.GetBuffer(),CFile::modeCreate|CFile::modeWrite);
		fileout.Write(((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.getColorsPtr(),sizeof(Color)*6*9);
		fileout.Close();
	}
}

void CMagicCube3DView::OnOpen()
{	
	CFileDialog fileDlg(true,NULL,NULL,4|2,"MagicCube Layout Files(*.ml)|*.ml||");
	if (fileDlg.DoModal()==IDOK){
		CString filename=fileDlg.GetPathName();
		CFile filein(filename.GetBuffer(),CFile::modeRead);
		filein.Read(((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.getColorsPtr(),sizeof(Color)*6*9);
		filein.Close();
	}
}

void CMagicCube3DView::OnFigureCube()
{
	//figure reference:www.Rubiker.cn
	const static char* figures[45]={
		/*六面回字公式*/ "U' D F' B L R' U' D",
		/*四色回字公式*/ "B2 L R B L2 B F D U' B F R2 F' L R",
		/*对称棋盘公式*/ "L2 R2 F2 B2 U2 D2",
		/*循环棋盘公式*/ "D2 F2 U'B2 F2 L2 R2 D R' B F D'U L R D2 U2 F'U2",
		/*六面十字公式*/ "B2 F' L2 R2 D2 B2 F2 L2 R2 U2 F'",
		/*四面十字公式*/ "D F2 R2 F2 D' U R2 F2 R2 U'",
		/*双色十字公式*/ "U' D F' B L R' U' D L2 R2 F2 B2 U2 D2",
		/*三色十字公式*/ "B F' L2 R2 U D'",
		/*四色十字公式*/ "U2 R B D B F' L' U' B F' L F L' R D U2 F' R' U2",
		/*五彩十字公式*/ "L2 D' F2 D B D L F R' U' R' D' F L2 B F2 L",
		/*六面皇后公式*/ "R2 B2 U2 L2 B2 U2 F2 L2 D L' R F L2 F' U' D L",
		/*六面五色公式*/ "U B2 L2 B F' U F' D2 L D2 F D R2 F2 R' B' U' R'",
		/*六面六色公式*/ "D2 U2 L2 B R2 D' L2 R2 D2 B2 F2 U' R2 B' R2",
		/*六面彩条公式*/ "F2 U2 F2 B2 U2 F B",
		/*六面三条公式*/ "(U2 L2)U2 L2U2 L2 (U2 R2)U2 R2U2 R2 U D L2 R2",
		/*六面凹字公式*/ "F2 L' R B2 U2 L R' D2",
		/*六面凹字公式*/ "U D L2 F2 U D' B2 R2 D2",
		/*六面凸字公式*/ "F2 R F2 R'U2 F2 L U2 B2 U2 F'U2 R D' B2 D F'D2 R F",
		/*六面工字公式*/ "D2 ML' F2 B2 ML' D2",
		/*六面Q字公式*/ "D F2 U' B F' L R' D L2 U' B R2 B' U L2 U'",
		/*六面J字公式*/ "D2 L2 D R2 U B2 U2 B R' B' D B2 R' F R2 F' U R'",
		/*六面L字公式*/ "L R U D F' B' L R",
		/*六面彩E公式*/ "F2 R2 F2 U' R' B2 F L R' U L' R U B U2 F2 D' U'",
		/*六面C U公式*/ "D' U B D' L' R F D' B' D' U L",
		/*六面T字公式*/ "U2 F2 R2 D U' L2 B2 D U",
		/*四面Z字公式*/ "F B R LF B R LF B R L (U D')U D'U D'",
		/*四面I字公式*/ "R2 F2 R2 L2 F2 L2",
		/*四面L字公式*/ "B F D U L2 D U' B F'",
		/*四面O字公式*/ "U R2 L2 U D' F2 B2 D'",
		/*四面E字公式*/ "R2 U2 F2 R2 U2 R2 F2 U2",
		/*四面V Y公式*/ "D2 R L U2 R2 L2 U2 R L",
		/*四面C U公式*/ "R2 F2 B2 L2 U F2 R2 L2 B2 D'",
		/*C C T V公式一*/ "B2 R2 D2 U2 F2 L R' U2 L' R'",
		/*C C T V公式二*/ "L2 B2 R2 D2 R2 F2 U2 F2 R2 U2 R2",
		/*六面斜线公式*/ "B L2 U2 L2 B' F' U2 R' B F R2 D' L R' D' U R F'",
		/*三色斜线公式*/ "R F2 L' D2 F2 L' R2 B' L' B' F' D' U R F' D R' B R'",
		/*四面斜线公式*/ "F B L R F B L R F B L R",
		/*大小魔方公式*/ "U2 L2 F2 U' B2 D R F' R F' R F' D' B2 U'",
		/*大中小魔公式*/ "BL'D2LDF'D2FD'B'F'RU2R'U'BU2B'UF (R'D2RB'U2B)R'D2RB'U2B",
		/*大中小魔公式*/ "F D2 L2 B D B' F2 U' F U F2 U2 F' L D F' U",
		/*六面弓箭公式*/ "R U F2 D'R L'F B'D' F' R F2 R U2 F R2 F'R'U'F'U2 F R",
		/*六面双环公式*/ "B R L' D' R2 D R' L B' R2 U B2 U' D B2 R L U2 R' L' B2 D'",
		/*六面蛇形公式*/ "B R L' D' R2 D R' L B' R2 U B2 U' D R2 D'",
		/*彩带魔方公式*/ "D2 L' U2 FL2 D2 U R2 D L2 B' L2 U L D' R2 U'",
		/*六面鱼形公式*/ "L D B2 U R2 B2 D L' B2 F'D'U R'D2 R'B2 F'U'F'"
	};

	//reset first
	((CMagicCube3DApp*)AfxGetApp())->openGL.magicCube.initialize();

	if (figurePtr>=45){
		figurePtr=0;
	}
	restoreString=figures[figurePtr++];
	restoredPos=0;
	//rotate
	SetTimer(timerRestore,rotateInterval,NULL);
}
