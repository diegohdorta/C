TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = medipix
# medipix.dbd will be created and installed
DBD += medipix.dbd

# medipix.dbd will be made up from these files:
medipix_DBD += base.dbd
medipix_DBD += stream.dbd
medipix_DBD += asyn.dbd
medipix_DBD += drvAsynIPPort.dbd

# Include dbd files from all support applications:
#medipix_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#medipix_LIBS += xxx

# medipix_registerRecordDeviceDriver.cpp derives from medipix.dbd
medipix_SRCS += medipix_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
medipix_SRCS_DEFAULT += medipixMain.cpp
medipix_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#medipix_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
medipix_LIBS += $(EPICS_BASE_IOC_LIBS)
medipix_LIBS += stream asyn
#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

