##################################################################################
## Grupo SOL - Diego Dorta - 14/05/2015
##################################################################################
#---------------------------------------------------------------------------------
#---------------------------------------------------------------------------------
# This document contains informations about the commands of Medipix.
#---------------------------------------------------------------------------------
#---------------------------------------------------------------------------------
# Name: Acquire
Description: Starts image acquisition.
Command: -acquire <n>, where n must be 1.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:Acquire
Usage: caput PV <n>, for instance: caput BEAMLINE:MEDIPIX:Acquire 1
#---------------------------------------------------------------------------------
# Name: Time
Description: Frame acquisition time.
Command: -time <n>, where n must be 0.001 ~ 100.999 secs.
Size: float64
Type: Write
PV: BEAMLINE:MEDIPIX:AcquisitionTime
Usage: caput PV <n>, for instance: caput BEAMLINE:MEDIPIX:AcquisitionTime 10
#---------------------------------------------------------------------------------
# Name: Frames
Description: Number of frames to be acquire.
Command: -frames <n>, where n must be 1 ~ 100.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetNumberFrames
Usage: caput PV <n>, for instance: caput BEAMLINE:MEDIPIX:SetNumberFrames 5
#---------------------------------------------------------------------------------
# Name: Read Counter
Description: Counter to be read.
Command: -readcounter <n>, where n must be 0 (low), 1 (high) or 2 (both).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetReadCounter
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetReadCounter 0
						   or caput BEAMLINE:MEDIPIX:SetReadCounter low
#---------------------------------------------------------------------------------
# Name: Gap
Description: Time between frames.
Command: -gap <n>, where n must be Gap 0.001 ~ 10.999 secs.
Size: float64
Type: Write
PV: BEAMLINE:MEDIPIX:SetGap
Usage: caput PV <n>, for instance: caput BEAMLINE:MEDIPIX:SetGap 2.7
#---------------------------------------------------------------------------------
### OMR ###
#---------------------------------------------------------------------------------
# Name: Read-Write
Description: Select the count mode.
Command: -readwrite <n>, where n must be 0 (sequencial) or 1 (continuous).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetCountMode
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetCountMode 0
						   or caput BEAMLINE:MEDIPIX:SetCountMode sequencial
#---------------------------------------------------------------------------------
# Name: Polarity
Description: Select the sensor polarity, if counts electrons or holes. 
Command: -polarity <n>, where n must be 0 (electron) or 1 (holes).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetPolarity
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetPolarity 0
						   or caput BEAMLINE:MEDIPIX:SetPolarity electron
#---------------------------------------------------------------------------------
# Name: Gain Mode
Description: Select the gain mode.
Command: -gainmode <n>, where n must be 0 (Super High), 1 (High), 2 (Low) or 3 (Super Low).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetGainMode
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetGainMode 0
						   or caput BEAMLINE:MEDIPIX:SetGainMode super high
#---------------------------------------------------------------------------------
# Name: Row Block Sel
Description: ---------
Command: -rowsel <n>, where n must be 0 (all) or 1 (Row Block).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetRowBrockSel
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetRowBrockSel 1
						   or caput BEAMLINE:MEDIPIX:SetRowBrockSel row block
#---------------------------------------------------------------------------------
#Name: Color Mode
Description: Select between Fine Pitch Mode and Spectroscopic Mode.
Command: -colormode <n>, where n must be 0 (Fine Pitch Mode) or 1 (Spectroscopic Mode).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetColorMode
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetColorMode 0
						   or caput BEAMLINE:MEDIPIX:SetColorMode fine pitch
#---------------------------------------------------------------------------------
#Name: Reset
Description: Reset DACS and internal logic 
Command: -reset <n>, where n must be 1.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:Reset
Usage: caput PV <n>, for instance: caput BEAMLINE:MEDIPIX:Reset 1
#---------------------------------------------------------------------------------
#Name: Enable Test Pulse
Description: Enable or disable the test pulse
Command: -enabletp <n>, where n must be 0 (disable) or 1 (enable).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetEnableTestPulse
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetEnableTestPulse 0
						   or caput BEAMLINE:MEDIPIX:SetEnableTestPulse disable
#---------------------------------------------------------------------------------
#Name: Row Block
Description: ......
Command: -rowblock <n>, where n must be 0 (row 0), 1 (row 0:15), 2 (row 0:3), 3 (row 0:63), 4 (row 0:1), 5 (row 0:31), 6 (row 0:7) and 7 (row 0:127).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetRowBlock
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetRowBlock 3
						   or caput BEAMLINE:MEDIPIX:SetRowBlock row 0:63
#---------------------------------------------------------------------------------
#Name: Colum Block Sel
Description: .......
Command: -colsel <n>, where n must be 0 (all) or 1 (colum n block).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetColumBlockSel
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetColumBlockSel 0
						   or caput BEAMLINE:MEDIPIX:SetColumBlockSel colum n block
#---------------------------------------------------------------------------------
#Name: Colum N Block
Description: ....... 
Command: -colblock <n>, where n must be 0 (000), 1 (001), 2 (010), 3 (011), 4 (100), 5 (101), 6 (110) and 7 (111).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetColumNBlock
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetColumNBlock 5
						   or caput BEAMLINE:MEDIPIX:SetColumNBlock 111
#---------------------------------------------------------------------------------
#Name: Disc Sel
Description: ....... 
Command: -discsel <n>, where n must be 0 (disc l), 1 (disc h).
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDiscSel
Usage: caput PV <n> or caput PV <name>, for instance: caput BEAMLINE:MEDIPIX:SetDiscSel 0
						   or caput BEAMLINE:MEDIPIX:SetDiscSel disc h
#---------------------------------------------------------------------------------
### DAC ###
#---------------------------------------------------------------------------------
#Name: Threshold 0 until 7
Description: ....... 
Command: -dacth<n> <m>, where n is a number between 0 and 7, and m must be between 0 ~ 511.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetThreshold_<n> (n is a number between 0 and 7)
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetSetThreshold_0 5
			       or caput BEAMLINE:MEDIPIX:SetSetThreshold_5 111
#---------------------------------------------------------------------------------
#Name: Current iKrum
Description: Set current iKrum 
Command: -ikrum <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetCurrentIKrum 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetCurrentIKrum 123
#---------------------------------------------------------------------------------
#Name: Shaper
Description: .... 
Command: -shaper <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetShaper 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetShaper 154
#---------------------------------------------------------------------------------
#Name: Disc
Description: .... 
Command: -disc <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDisc 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDisc 37
#---------------------------------------------------------------------------------
#Name: Disc LS
Description: .... 
Command: -discls <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDiscLS 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDiscLS 193
#---------------------------------------------------------------------------------
#Name: Dac Disc L
Description: .... 
Command: -dacdiscl <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDacDiscL 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDacDiscL 233
#---------------------------------------------------------------------------------
#Name: Dac Disc H
Description: .... 
Command: -dacdisch <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDacDiscH 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDacDiscL 233
#---------------------------------------------------------------------------------
#Name: Pre-Amplifier
Description: .... 
Command: -preamp <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetPreAmplifier 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetPreAmplifier 234
#---------------------------------------------------------------------------------
#Name: Delay
Description: .... 
Command: -delay <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDelay 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDelay 77
#---------------------------------------------------------------------------------
#Name: Dac Buffer In
Description: .... 
Command: -tpbuffin <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDacBufferIn 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDacBufferIn 44
#---------------------------------------------------------------------------------
#Name: Dac Buffer Out
Description: .... 
Command: -tpbuffout <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetDacBufferOut 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetDacBufferOut 144
#---------------------------------------------------------------------------------
#Name: Groung Voltage
Description: .... 
Command: -gnd <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetGroundVoltage 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetGroundVoltage 144
#---------------------------------------------------------------------------------
#Name: Reference Test Pulse
Description: .... 
Command: -tpref <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetReferenceTestPulse 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetReferenceTestPulse 144
#---------------------------------------------------------------------------------
#Name: Reference Test Pulse A
Description: .... 
Command: -tprefa <n>, where n must be between 0 ~ 511.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetReferenceTestPulseA 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetReferenceTestPulseA 134
#---------------------------------------------------------------------------------
#Name: Reference Test Pulse B
Description: .... 
Command: -tprefb <n>, where n must be between 0 ~ 511.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetReferenceTestPulseB 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetReferenceTestPulseB 4
#---------------------------------------------------------------------------------
#Name: FBK
Description: .... 
Command: -fbk <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetFBK 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetFBK 56
#---------------------------------------------------------------------------------
#Name: Cascode
Description: .... 
Command: -cas <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetCascode 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetCascode 39
#---------------------------------------------------------------------------------
#Name: RPZ
Description: .... 
Command: -rpz <n>, where n must be between 0 ~ 255.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:SetRPZ 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:SetRPZ 56
#---------------------------------------------------------------------------------
### CONFIGURATIONS ###
#---------------------------------------------------------------------------------
#---------------------------------------------------------------------------------
#Name: Send IP
Description: .... 
Command: -send_ip <n>, where n must be an ip address.
Size: string
Type: Write
PV: BEAMLINE:MEDIPIX:_SetSendIP 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:_SetSendIP 10.2.101.35
#---------------------------------------------------------------------------------
#Name: Send Port
Description: .... 
Command: -send_port <n>, where n must be between 1 ~ 65536.
Size: int32
Type: Write
PV: BEAMLINE:MEDIPIX:_SetSendPort 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:_SetSendPort 3000
#---------------------------------------------------------------------------------
#Name: Send IP
Description: .... 
Command: -send_mac <n>, where n must be a MAC address.
Size: string
Type: Write
PV: BEAMLINE:MEDIPIX:_SetSendMac 
Usage: caput PV <n> for instance: caput BEAMLINE:MEDIPIX:_SetSendMac 00:1E:C9:21:9C:08
#---------------------------------------------------------------------------------
#---------------------------------------------------------------------------------

