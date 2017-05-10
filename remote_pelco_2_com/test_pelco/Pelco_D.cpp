#include "stdafx.h"
//#include <windows.h>
//#include <stdlib.h>
//#include <string.h>
#include "Pelco_D.h"

namespace Pelco_D_Protocol {
// Extended Command Set
BYTE * CPelco_D::Preset(UINT deviceAddress, BYTE preset, PresetAction action)
{
	BYTE m_action;
	switch (action)
	{
		case PresetAction_Set:
			m_action = 0x03;
			break;
		case PresetAction_Clear:
			m_action = 0x05;
			break;
		case PresetAction_Goto:
			m_action = 0x07;
			break;
		default:
			m_action = 0x03;
			break;
	}
	return Package(deviceAddress,0x00,m_action,0x00,preset);
}

BYTE * CPelco_D::Flip(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x07,0x00,0x21);
}

BYTE * CPelco_D::ZeroPanPosition(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x07,0x00,0x22);
}

BYTE * CPelco_D::SetAuxiliary(UINT deviceAddress,BYTE auxiliaryID, AuxAction action)
{
	if(auxiliaryID<0x00)
		auxiliaryID = 0x00;
	else if(auxiliaryID>0x08)
		auxiliaryID = 0x08;
	return Package(deviceAddress,0x00,(BYTE)action,0x00,auxiliaryID);
}

BYTE * CPelco_D::RemoteReset(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x0F,0x00,0x00);
}

BYTE * CPelco_D::Zone(UINT deviceAddress,BYTE zone, Action action)
{
/*	if(zone<0x01 && zone>0x08)
		throw new Exception("Zone value should be between 0x01 and 0x08 include");
*/
	if(zone<0x01 || zone>0x08) {
		return Package(deviceAddress,0x00,0x00,0x00,0x00);
	}
	BYTE m_action;
	if(action == Action_Start)
		m_action = 0x11;
	else
		m_action = 0x13;

	return Package(deviceAddress,0x00,m_action,0x00,zone);
}

/*
BYTE * CPelco_D::WriteToScreen(UINT deviceAddress,string text)
{
	if(text.Length > 40)
		text = text.Remove(40,text.Length-40);
	System.Text.Encoding encoding = System.Text.Encoding.ASCII;
	BYTE[] m_bytes = new BYTE[encoding.GetByteCount(text)*7];
	int i = 0;
	BYTE m_scrPosition;
	BYTE m_ASCIIchr;
			
			foreach(char ch in text)
			{
				m_scrPosition = Convert.ToByte(i/7);
				m_ASCIIchr = Convert.ToByte(ch);
				Array.Copy(Message.GetMessage(deviceAddress,0x00,0x15,m_scrPosition,m_ASCIIchr),0,m_bytes,i,7);
				i = i + 7;
			}

			return m_bytes;
}
*/
BYTE * CPelco_D::WriteToScreen(UINT deviceAddress, char * text)
{
	if(strlen(text) > 40)
		text[40] = '\0';
	int i = 0;
	UINT m_scrPosition;
	BYTE m_ASCIIchr;
	int len;
	BYTE * Message;
	len = strlen(text);
	*((UINT*)MessageBuffer) = strlen(text)*MessageLen;
	for(i=0; i<len; i++) {
		m_scrPosition = i;
		m_ASCIIchr = text[i];
		Message = Package(deviceAddress,0x00,0x15,m_scrPosition,m_ASCIIchr);
		memcpy(MessageBuffer+i*MessageLen+MessageHead,Message+MessageHead, MessageLen);
	}
	return MessageBuffer;
}

BYTE * CPelco_D::ClearScreen(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x17,0x00,0x00);
}

BYTE * CPelco_D::AlarmAcknowledge(UINT deviceAddress, UINT alarmID)
{
//	if(alarmID < 1 & alarmID>8)
//		throw new Exception("Only 8 alarms allowed for Pelco P implementation");
/*	if(alarmID < 1)
		alarmID = 1;
	else if(alarmID>8)
		alarmID = 8; */
	if(alarmID < 1 && alarmID>8) {
		return Package(deviceAddress,0x00,0x00,0x00,0x00);
	} else {
		return Package(deviceAddress,0x00,0x19,0x00,(BYTE)alarmID);
	}
}

BYTE * CPelco_D::ZoneScan(UINT deviceAddress,Action action)
{
	BYTE m_action;
	if(action == Action_Start)
		m_action = 0x1B;
	else
		m_action = 0x1D;
	return Package(deviceAddress,0x00,m_action,0x00,0x00);
}

BYTE * CPelco_D::Pattern(UINT deviceAddress,PatternAction action)
{
	BYTE m_action;
	switch (action) {
		case PatternAction_Start:
				m_action = 0x1F;
				break;
		case PatternAction_Stop:
				m_action = 0x21;
				break;
		case PatternAction_Run:
				m_action = 0x23;
				break;
		default:
				m_action = 0x23;
				break;
	}
	return Package(deviceAddress,0x00,m_action,0x00,0x00);
}

BYTE * CPelco_D::SetZoomLensSpeed(UINT deviceAddress, LensSpeed speed)
{
	return Package(deviceAddress,0x00,0x25,0x00,(BYTE)speed);
}

BYTE * CPelco_D::SetFocusLensSpeed(UINT deviceAddress, LensSpeed speed)
{
	return Package(deviceAddress,0x00,0x27,0x00,(BYTE)speed);
}

BYTE * CPelco_D::ResetCamera(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x29,0x00,0x00);
}

BYTE * CPelco_D::AutoFocus(UINT deviceAddress, SwitchAction action)
{
	return Package(deviceAddress,0x00,0x2B,0x00,(BYTE)action);
}

BYTE * CPelco_D::AutoIris(UINT deviceAddress, SwitchAction action)
{
	return Package(deviceAddress,0x00,0x2D,0x00,(BYTE)action);
}

BYTE * CPelco_D::AGC(UINT deviceAddress, SwitchAction action)
{
	return Package(deviceAddress,0x00,0x2F,0x00,(BYTE)action);
}

BYTE * CPelco_D::BackLightCompensation(UINT deviceAddress, Switch action)
{
	return Package(deviceAddress,0x00,0x31,0x00,(BYTE)action);
}

BYTE * CPelco_D::AutoWhiteBalance(UINT deviceAddress, Switch action)
{
	return Package(deviceAddress,0x00,0x33,0x00,(BYTE)action);
}

BYTE * CPelco_D::EnableDevicePhaseDelayMode(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x35,0x00,0x00);
}

BYTE * CPelco_D::SetShutterSpeed(UINT deviceAddress,BYTE speed)
{
	return Package(deviceAddress,0x00,0x37,speed,speed);//Not sure about
}

BYTE * CPelco_D::AdjustLineLockPhaseDelay(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x39,0x00,0x00);
}

BYTE * CPelco_D::AdjustWhiteBalanceRB(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x3B,0x00,0x00);
}

BYTE * CPelco_D::AdjustWhiteBalanceMG(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x3D,0x00,0x00);
}

BYTE * CPelco_D::AdjustGain(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x3F,0x00,0x00);
}

BYTE * CPelco_D::AdjustAutoIrisLevel(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x41,0x00,0x00);
}

BYTE * CPelco_D::AdjustAutoIrisPeakValue(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x43,0x00,0x00);
}

BYTE * CPelco_D::Query(UINT deviceAddress)
{
//	throw new Exception("Did not implemented");
	return Package(deviceAddress,0x00,0x45,0x00,0x00);
}

// Base Command Set

BYTE * CPelco_D::CameraSwitch(UINT deviceAddress,Switch action)
{
	BYTE m_action = CameraOnOff;
	if(action == Switch_On)
		m_action = CameraOnOff + Sense;
	return Package(deviceAddress,m_action,0x00,0x00,0x00);
}

BYTE * CPelco_D::CameraIrisSwitch(UINT deviceAddress,Iris action)
{
	return Package(deviceAddress,(BYTE)action,0x00,0x00,0x00);
}

BYTE * CPelco_D::CameraFocus(UINT deviceAddress,Focus action)
{
	if(action == Near)
		return Package(deviceAddress,(BYTE)action,0x00,0x00,0x00);
	else
		return Package(deviceAddress,0x00,(BYTE)action,0x00,0x00);
}

BYTE * CPelco_D::CameraZoom(UINT deviceAddress,Zoom action)
{
	return Package(deviceAddress,0x00,(BYTE)action,0x00,0x00);
}

BYTE * CPelco_D::CameraTilt(UINT deviceAddress,Tilt action, UINT speed)
{
	if(speed<TiltSpeedMin)
		speed = TiltSpeedMin;
	if(speed>TiltSpeedMax)	// <
		speed = TiltSpeedMax;

	return Package(deviceAddress,0x00,(BYTE)action,0x00,(BYTE)speed);
}

BYTE * CPelco_D::CameraPan(UINT deviceAddress,Pan action, UINT speed)
{
	if(speed<PanSpeedMin)
		speed = PanSpeedMin;
	if(speed>PanSpeedMax)	// <
		speed = PanSpeedMax;

	return Package(deviceAddress,0x00,(BYTE)action,(BYTE)speed,0x00);
}

BYTE * CPelco_D::CameraPanTilt(UINT deviceAddress,Pan panAction, UINT panSpeed, Tilt tiltAction, UINT tiltSpeed)
{
	BYTE PanCmd, TiltCmd, PanSpeed, TiltSpeed;
	BYTE * m_tiltMessage = CameraTilt(deviceAddress,tiltAction,tiltSpeed);
	TiltCmd = m_tiltMessage[MessageHead+3];
	TiltSpeed = m_tiltMessage[MessageHead+5];
	BYTE * m_panMessage = CameraPan(deviceAddress,panAction,panSpeed);
	PanCmd = m_panMessage[MessageHead+3];
	PanSpeed = m_panMessage[MessageHead+4];
	return Package(deviceAddress,0x00,(BYTE)(TiltCmd|PanCmd), PanSpeed, TiltSpeed);
			/*m_bytes[0] = m_tiltMessage[0];
			m_bytes[1] = m_tiltMessage[1];
			m_bytes[2] = m_tiltMessage[2];
			m_bytes[3] = (BYTE)(m_tiltMessage[3]+m_panMessage[3]);
			m_bytes[4] = (BYTE)(m_tiltMessage[4]+m_panMessage[4]);
			m_bytes[5] = (BYTE)(m_tiltMessage[5]+m_panMessage[5]);
			m_bytes[6] = m_tiltMessage[6];
			m_bytes[7] = m_tiltMessage[7];*/
		//	m_bytes = Message.GetMessage(deviceAddress,0x00,(BYTE)(m_tiltMessage[3]+m_panMessage[3]),
		//		m_panMessage[4],m_tiltMessage[5]);
		//	return m_bytes;

}

BYTE * CPelco_D::CameraStop(UINT deviceAddress)
{
	return Package(deviceAddress,0x00,0x00,0x00,0x00);
}

BYTE * CPelco_D::CameraScan(UINT deviceAddress,Scan scan)
{
	BYTE m_byte = 0x00; //AutoManualScan;
	if(scan == Scan_Auto)
		m_byte = AutoManualScan+Sense;
	return Package(deviceAddress,m_byte,0x00,0x00,0x00);
}

BYTE * CPelco_D::Noop(UINT deviceAddress)
{
		return Package(deviceAddress,0x00,0x00,0x00,0x00);
}
BYTE * CPelco_D::Package(BYTE Address, BYTE Command1, BYTE Command2, BYTE Data1, BYTE Data2)
{
	Pelco_D.Sync = SYNC;
	Pelco_D.Address = Address;
	Pelco_D.Command1 = Command1;
	Pelco_D.Command2 = Command2;
	Pelco_D.Data1 = Data1;
	Pelco_D.Data2 = Data2;
	Pelco_D.CheckSum = (BYTE)(Pelco_D.Address + Pelco_D.Command1 + Pelco_D.Command2 + Pelco_D.Data1 + Pelco_D.Data2);
	
//	*((UINT*)Message) = (UINT)MessageLen;
	Message[MessageHead+0] = Pelco_D.Sync;
	Message[MessageHead+1] = Pelco_D.Address;
	Message[MessageHead+2] = Pelco_D.Command1;
	Message[MessageHead+3] = Pelco_D.Command2;
	Message[MessageHead+4] = Pelco_D.Data1;
	Message[MessageHead+5] = Pelco_D.Data2;
	Message[MessageHead+6] = Pelco_D.CheckSum;
	return Message;
}

/////// added by wu 
BYTE * CPelco_D::SetPanPos(UINT deviceAddress, UINT pos)
{
	BYTE highV, lowV;

	highV = pos/256;
	lowV = pos & 0xFF; 
	return Package(deviceAddress,0x00,0x4B, highV, lowV);
}

BYTE * CPelco_D::SetTiltPos(UINT deviceAddress, UINT pos)
{
	BYTE highV, lowV;

	highV = pos/256;
	lowV = pos & 0xFF; 
	return Package(deviceAddress,0x00,0x4D, highV, lowV);
}

BYTE * CPelco_D::SetZoomPos(UINT deviceAddress, UINT pos, UINT max_pos)
{
	BYTE highV, lowV;
	UINT temp_pos;

	temp_pos = (UINT)((pos*1.0f/max_pos)*65535);
	highV = temp_pos/256;
	lowV = temp_pos & 0xFF;

	return Package(deviceAddress,0x00, 0x4F, highV, lowV);
}

};