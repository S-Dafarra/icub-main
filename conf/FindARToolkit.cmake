#
# Find the ARTOOLKIT includes and library
#
# This module defines
# ARTOOLKIT_INCLUDE_DIR, where to find avcodec.h, avformat.h ...
# ARTOOLKIT_LIBRARIES, the libraries to link against to use ARTOOLKIT.
# ARTOOLKIT_FOUND, If false, do not try to use ARTOOLKIT.
# Right now this is only including the basics ..
# Frank F. (01/02/10): changed the FIND_LIBRARY line slightly, so that it works
# under Mac OS X (and hopefully Linux) too


FIND_PATH(ARTOOLKIT_INCLUDE_DIR AR/ar.h "$ENV{ARTOOLKIT_DIR}/include" )
FIND_LIBRARY(ARTOOLKIT_AR_LIBRARY NAMES libAR.a PATHS "$ENV{ARTOOLKIT_DIR}/lib" )
#FIND_LIBRARY(ARTOOLKIT_ARGSUB_LIBRARY libARgsub $ENV{ARTOOLKIT_DIR}/lib )
#FIND_LIBRARY(ARTOOLKIT_ARVIDEO_LIBRARY libARvideo $ENV{ARTOOLKIT_DIR}/lib )
#FIND_LIBRARY(ARTOOLKIT_ARGSUBLITE_LIBRARY libARgsub_lite $ENV{ARTOOLKIT_DIR}/lib )
#FIND_LIBRARY(ARTOOLKIT_ARMULTI_LIBRARY libARMulti $ENV{ARTOOLKIT_DIR}/lib )
#FIND_LIBRARY(ARTOOLKIT_ARVRML_LIBRARY libARvrml $ENV{ARTOOLKIT_DIR}/lib )
#FIND_LIBRARY(ARTOOLKIT_ARGSUBUTIL_LIBRARY libARgsubUtil $ENV{ARTOOLKIT_DIR}/lib )
#FIND_LIBRARY(ARTOOLKIT_GLUT_LIBRARY glut32 $ENV{ARTOOLKIT_DIR}/DSVL/lib )
  
  
SET( ARTOOLKIT_FOUND FALSE )

IF(ARTOOLKIT_INCLUDE_DIR)
  IF(ARTOOLKIT_AR_LIBRARY)
#    IF(ARTOOLKIT_ARGSUB_LIBRARY)
#      IF(ARTOOLKIT_ARVIDEO_LIBRARY)
#        IF(ARTOOLKIT_ARGSUBLITE_LIBRARY)
#          IF(ARTOOLKIT_ARMULTI_LIBRARY)
#            IF(ARTOOLKIT_ARVRML_LIBRARY)
#              IF(ARTOOLKIT_ARGSUBUTIL_LIBRARY)
#                IF(ARTOOLKIT_GLUT_LIBRARY)
                  SET( ARTOOLKIT_FOUND TRUE )
                  SET( ARTOOLKIT_LIBRARIES 
            	  ${ARTOOLKIT_AR_LIBRARY}
#          	  ${ARTOOLKIT_ARGSUB_LIBRARY} 
#          	  ${ARTOOLKIT_ARVIDEO_LIBRARY} 
#          	  ${ARTOOLKIT_ARGSUBLITE_LIBRARY} 
#          	  ${ARTOOLKIT_ARVRML_LIBRARY} 
#          	  ${ARTOOLKIT_ARGSUBUTIL_LIBRARY} 
#          	  ${ARTOOLKIT_GLUT_LIBRARY} 
          	)
#                ENDIF(ARTOOLKIT_GLUT_LIBRARY)
#              ENDIF(ARTOOLKIT_ARGSUBUTIL_LIBRARY)
#            ENDIF(ARTOOLKIT_ARVRML_LIBRARY)
#          ENDIF(ARTOOLKIT_ARMULTI_LIBRARY)  
#	ENDIF(ARTOOLKIT_ARGSUBLITE_LIBRARY)
#      ENDIF(ARTOOLKIT_ARVIDEO_LIBRARY)
#    ENDIF(ARTOOLKIT_ARGSUB_LIBRARY)
  ENDIF(ARTOOLKIT_AR_LIBRARY)
ENDIF(ARTOOLKIT_INCLUDE_DIR)

MARK_AS_ADVANCED(
  ARTOOLKIT_AR_LIBRARY
#  ARTOOLKIT_ARGSUB_LIBRARY
#  ARTOOLKIT_ARVIDEO_LIBRARY
#  ARTOOLKIT_ARGSUBLITE_LIBRARY
#  ARTOOLKIT_ARMULTI_LIBRARY
#  ARTOOLKIT_ARVRML_LIBRARY
#  ARTOOLKIT_ARGSUBUTIL_LIBRARY
#  ARTOOLKIT_GLUT_LIBRARY
  )

