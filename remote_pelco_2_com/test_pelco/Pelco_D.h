#ifndef PELCO_D_H
#define PELCO_D_H

/*** Pelco_D Protocol *******************/
typedef struct {
	BYTE	Sync;
	BYTE	Address;
	BYTE	Command1;
	BYTE	Command2;
	BYTE	Data1;
	BYTE	Data2;
	BYTE	CheckSum;
} PELCO_D_PROTOCOL;

#ifdef ZZZ

#define PELCO_D_MSG_LEN		7
#define PELCO_D_SYNC		0xFF
#define PELCO_D_ADDR_MIN	0
#define PELCO_D_ADDR_MAX	255
/***** Pelco_D : Command1 *****/
enum {
	PELCO_D_C1_SENSE = 0x80;
	PELCO_D_C1_AUTO_MANUAL_SCAN = 0x10;
	PELCO_D_C1_CAMERA_ON_OFF = 0x08;
	PELCO_D_C1_IRIS_CLOSE = 0x04;//光圈关
	PELCO_D_C1_IRIS_OPEN = 0x02; //光圈开
	PELCO_D_C1_FOCUS_NEAR = 0x01;
};
/***** Pelco_D : Command2 *****/
enum {
	PELCO_D_C2_FOCUS_FAR = 0x80;//焦聚远
	PELCO_D_C2_ZOOM_WIDE = 0x40;//变倍大
	PELCO_D_C2_ZOOM_TELE = 0x20;//变倍小
	PELCO_D_C2_DOWN = 0x10;		//下
	PELCO_D_C2_UP = 0x08;		//上
	PELCO_D_C2_LEFT = 0x04;		//左
	PELCO_D_C2_RIGHT = 0x02;	//右
};
/***** Pelco_D : Data1 (Pan Speed) *****/
#define PELCO_D_D1_PAN_SPEED_MIN	0x00
#define PELCO_D_D1_PAN_SPEED_MAX	0x3F
#define PELCO_D_D1_PAN_SPEED_TURBO	0xFF
/***** Pelco_D : Data2 (Tilt Speed) *****/
#define PELCO_D_D2_TILT_SPEED_MIN	0x00
#define PELCO_D_D2_TILT_SPEED_MAX	0x3F
/****************************************/

#endif

namespace Pelco_D_Protocol {
		const UINT MessageLen = 7;
		const UINT MessageHead = 0;//sizeof(UINT);	
		const BYTE SYNC = 0xFF;

		// Pan and Tilt Commands
		// Command1
		const BYTE FocusNear =	0x01;
		const BYTE IrisOpen =	0x02;
		const BYTE IrisClose =	0x04;
		const BYTE CameraOnOff = 0x08;
		const BYTE AutoManualScan =	0x10;
		const BYTE Sense =	0x80;

		// Command2
		const BYTE PanRight =	0x02;
		const BYTE PanLeft =	0x04;
		const BYTE TiltUp =		0x08;
		const BYTE TiltDown =	0x10;
		const BYTE ZoomTele =	0x20;
		const BYTE ZoomWide =	0x40;
		const BYTE FocusFar =	0x80;

		// Data1
		const BYTE PanSpeedMin = 0x00;
		const BYTE PanSpeedMax = 0xFF;

		// Data2
		const BYTE TiltSpeedMin = 0x00;
		const BYTE TiltSpeedMax = 0x3F;
		
class CPelco_D
{
	public:
		CPelco_D() {};
		~CPelco_D() {};
		// Enum
		enum PresetAction {PresetAction_Set,PresetAction_Clear,PresetAction_Goto};
		enum AuxAction {AuxAction_Set=0x09,AuxAction_Clear=0x0B};
		enum Action {Action_Start,Action_Stop};
		enum LensSpeed {LensSpeed_Low=0x00,LensSpeed_Medium=0x01,LensSpeed_High=0x02,LensSpeed_Turbo=0x03};
		enum PatternAction {PatternAction_Start,PatternAction_Stop,PatternAction_Run};
		enum SwitchAction {SwitchAction_Auto=0x00,SwitchAction_On=0x01,SwitchAction_Off=0x02};
		enum Switch {Switch_On=0x01,Switch_Off=0x02};
		enum Focus {Near = FocusNear,Far = FocusFar};
		enum Zoom {Wide = ZoomWide,Tele = ZoomTele};
		enum Tilt {Up = TiltUp,Down = TiltDown};
		enum Pan {Left = PanLeft,Right = PanRight};
		enum Scan {Scan_Auto, Scan_Manual};
		enum Iris {Open = IrisOpen,Close = IrisClose};
		//Extended Command Set
		BYTE * Preset(UINT deviceAddress, BYTE preset, PresetAction action);//预制位
		BYTE * Flip(UINT deviceAddress);//旋转180
		BYTE * ZeroPanPosition(UINT deviceAddress);//0位置
		BYTE * SetAuxiliary(UINT deviceAddress,byte auxiliaryID, AuxAction action);
		BYTE * RemoteReset(UINT deviceAddress);
		BYTE * Zone(UINT deviceAddress,byte zone, Action action);
		BYTE * WriteToScreen(UINT deviceAddress, char * text);
		BYTE * ClearScreen(UINT deviceAddress);
		BYTE * AlarmAcknowledge(UINT deviceAddress, UINT alarmID);
		BYTE * ZoneScan(UINT deviceAddress,Action action);
		BYTE * Pattern(UINT deviceAddress,PatternAction action);
		BYTE * SetZoomLensSpeed(UINT deviceAddress, LensSpeed speed);
		BYTE * SetFocusLensSpeed(UINT deviceAddress, LensSpeed speed);
		BYTE * ResetCamera(UINT deviceAddress);
		BYTE * AutoFocus(UINT deviceAddress, SwitchAction action);
		BYTE * AutoIris(UINT deviceAddress, SwitchAction action);
		BYTE * AGC(UINT deviceAddress, SwitchAction action);
		BYTE * BackLightCompensation(UINT deviceAddress, Switch action);//背光补尝
		BYTE * AutoWhiteBalance(UINT deviceAddress, Switch action);
		BYTE * EnableDevicePhaseDelayMode(UINT deviceAddress);
		BYTE * SetShutterSpeed(UINT deviceAddress, BYTE speed);
		BYTE * AdjustLineLockPhaseDelay(UINT deviceAddress);
		BYTE * AdjustWhiteBalanceRB(UINT deviceAddress);
		BYTE * AdjustWhiteBalanceMG(UINT deviceAddress);
		BYTE * AdjustGain(UINT deviceAddress);
		BYTE * AdjustAutoIrisLevel(UINT deviceAddress);
		BYTE * AdjustAutoIrisPeakValue(UINT deviceAddress);
		BYTE * Query(UINT deviceAddress);

		// added by wu 
		BYTE * SetPanPos(UINT deviceAddress, UINT pos);
		BYTE * SetTiltPos(UINT deviceAddress, UINT pos);
		BYTE * SetZoomPos(UINT deviceAddress, UINT pos, UINT max_pos);

		//Base Command Set
		BYTE * CameraSwitch(UINT deviceAddress,Switch action);
		BYTE * CameraIrisSwitch(UINT deviceAddress,Iris action);//光圈
		BYTE * CameraFocus(UINT deviceAddress,Focus action);//聚焦
		BYTE * CameraZoom(UINT deviceAddress,Zoom action);//缩放
		BYTE * CameraTilt(UINT deviceAddress,Tilt action, UINT speed);//上下
		BYTE * CameraPan(UINT deviceAddress,Pan action, UINT speed);
		BYTE * CameraPanTilt(UINT deviceAddress,Pan panAction, UINT panSpeed, Tilt tiltAction, UINT tiltSpeed);
		BYTE * CameraStop(UINT deviceAddress);//停止
		BYTE * CameraScan(UINT deviceAddress,Scan scan);//扫描
		BYTE * Noop(UINT deviceAddress);
	private:
		BYTE * Package(BYTE Address, BYTE Command1, BYTE Command2, BYTE Data1, BYTE Data2);
	private:
		PELCO_D_PROTOCOL Pelco_D;
		BYTE Message[16];
		BYTE MessageBuffer[512];
};

};

#endif