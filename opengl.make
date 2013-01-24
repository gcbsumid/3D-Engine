# makefile

ifndef verbose
	SILENT = @
endif

ifdef clang
	CXX = clang++
else 
	CXX = g++
endif

ifndef config
	config = debug
endif

TARGETDIR = bin

ifeq ($(config),debug)
	OBJDIR 		= obj/debug
	TARGET 		= $(TARGETDIR)/program_debug
	DEFINES 	= -DDEBUG
	CPPFLAGS	= -MMD -MP $(DEFINES) -g -Wall
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= 
	LIBS      += -lGL -lglfw -lGLEW
endif

ifeq ($(config),release)
	OBJDIR 		= obj/release
	TARGET 		= $(TARGETDIR)/program_debug
	DEFINES 	= -DNDEBUG
	CPPFLAGS 	= -MMD -MP $(DEFINES) -02 -Wall
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= -s
endif

OBJECTS := \
	$(OBJDIR)/main.o \

.PHONY: clean

all: $(TARGETDIR) $(OBJDIR) ${TARGET}

$(TARGET): $(TARGETDIR) $(OBJDIR) $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LIBS) $(LDFLAGS)

$(OBJDIR):
	@echo "Creating $(OBJDIR)"
	$(SILENT) mkdir -p $(OBJDIR)

$(TARGETDIR):
	@echo "Creating $(TARGETDIR)"
	$(SILENT) mkdir -p $(TARGETDIR)

clean:
	@echo "Cleaning program"
	$(SILENT) rm -f $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
	
run: ${TARGET}
	./${TARGET}

$(OBJDIR)/main.o: source/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)