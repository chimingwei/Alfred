#####################################################################
########                                                #############
########                Taylor Bartlett                 #############
########                muh fkin makfile                #############
########                                                #############
#####################################################################

CC            = gcc
CXX           = g++
CFLAGS        = -O3 -Wall
CXXFLAGS      = -O3
ARCFLAGS	  = $(CXXFLAGS) -fPIC -g
INCPATH       =`pkg-config opencv --cflags`

LINK          = gcc
LINKXX        = g++

LFLAGS        = -shared
LIBS          = `pkg-config opencv --libs`

PKGCFG        = `pkg-config opencv --cflags --libs`


DEL_FILE      = rm -f

####### Files
SOURCES       = facial_recognition.cpp
OBJECTS       = $(SOURCES:.cpp=.o)
DESTDIR       =
TARGET        = recog
LIBSOURCES	  = facerec.cpp
LIBOBJECTS    = $(LIBSOURCES:.cpp=.o)
ARCHIVE       = librecog.so

first: small

small:
	$(CXX) $(CXXFLAGS) $(INCPATH) $(SOURCES) -o $(TARGET) $(PKGCFG)

####### Implicit rules
.SUFFIXES: .c
.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<" $(LIBS)
.SUFFIXES: .cpp
.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<" $(LIBS)

####### Build rules
so:  $(ARCHIVE)


$(ARCHIVE):  $(LIBOBJECTS)
	$(LINKXX) $(LFLAGS) -o $(ARCHIVE) $(LIBOBJECTS) $(LIBS)

$(LIBOBJECTS): $(LIBSOURCES)
	$(CXX) -c $(ARCFLAGS) $(INCPATH) -o "$@" "$<" $(LIBS)
clean:
	-$(DEL_FILE) $(OBJECTS)
cleanlib:
	-$(DEL_FILE) $(LIBOBJECTS) $(ARCHIVE)
distclean: clean
	-$(DEL_FILE) $(TARGET)
