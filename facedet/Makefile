#####################################################################
########                                                #############
########                Taylor Bartlett                 #############
########                muh fkin makfile                #############
########                                                #############
#####################################################################

CC            =gcc
CXX           =g++
DEFINES       =
CFLAGS        =-O3 -Wall $(DEFINES)
CXXFLAGS      =-O3 -Wall $(DEFINES)
INCPATH       =

LINK          =gcc
LINKXX        =g++

LFLAGS        =
LIBS          =
PKGCFG        =`pkg-config opencv --cflags --libs`


DEL_FILE      =rm -f

####### Files
SOURCES       =facedetector.cpp
OBJECTS       =$(SOURCES:.cpp=.o)
DESTDIR       =
TARGET        =det

first: small

small:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(PKGCFG)


####### Implicit rules
.SUFFIXES: .c
.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<" $(LIBS)
.SUFFIXES: .cpp
.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<" $(LIBS)

####### Build rules
all:  $(TARGET)

$(TARGET):$(OBJECTS)
	$(LINKXX) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)


clean:
	$(DEL_FILE) $(OBJECTS)

distclean: clean
	$(DEL_FILE) $(TARGET)
