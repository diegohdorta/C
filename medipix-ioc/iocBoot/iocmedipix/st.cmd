#!../../bin/linux-x86/medipix

#/usr/local/epics/apps/medipix/bin/linux-x86/medipix
#< /usr/local/epics/apps/medipix/iocBoot/iocmedipix/envPaths

< envPaths
< medipix.config
#< ${EPICS_CONFIG}/${BL}/medipix.config
epicsEnvSet("BL","${EPICS_HOSTNAME}")
epicsEnvSet("STREAM_PROTOCOL_PATH","${TOP}/db")

cd "${TOP}"
dbLoadDatabase("dbd/medipix.dbd",0,0)
medipix_registerRecordDeviceDriver(pdbbase)

# Establishing udp network connection to medipix
# This connection is used to send commands to medipix
drvAsynIPPortConfigure("H0","${MEDIPIX_IP/PORT} UDP",0,0,0) 
asynSetTraceIOMask("H0",-1,0x2)
asynSetTraceMask("H0",-1,0x9)

# Establishing tcp network connection to server
# This connection is used to send the file name, number of bits, frames, read counter and gap to server.
drvAsynIPPortConfigure("H1","${SERVER_IP/PORT_VARIABLE}",0,0,0) 
asynSetTraceIOMask("H1",-1,0x2)
asynSetTraceMask("H1",-1,0x9)
asynOctetSetInputEos("H1", -1, "\n")
asynOctetSetOutputEos("H1", -1, "\n")

dbLoadRecords("db/devmedipix.db" "BL=${BL},MP=${MEDIPIX_NAME},OMR=${MEDIPIX_TYPE_1},DAC=${MEDIPIX_TYPE_2},CONFIG=${MEDIPIX_TYPE_3},SERVER=${MEDIPIX_TYPE_4},SCAN=${MEDIPIX_TYPE_5},EQ=${MEDIPIX_TYPE_6},TP=${MEDIPIX_TYPE_7},PORT_MEDIPIX=H0, PORT_SERVER=H1, SERVER_IP=${SERVER_IP}, SERVER_PORT=${SERVER_PORT}")

cd "${TOP}/iocBoot/${IOC}"
iocInit

