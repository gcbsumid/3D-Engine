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
	TARGET 		= $(TARGETDIR)/program_debug.debug
	DEFINES 	= -DDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	CPPFLAGS   += -MMD -MP $(DEFINES) -g -Wall $(INCLUDES)
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= 
	LIBS      += -lGL -lglfw -lGLEW
endif

ifeq ($(config),release)
	OBJDIR 		= obj/release
	TARGET 		= $(TARGETDIR)/program_debug.release
	DEFINES 	= -DNDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	CPPFLAGS   += -MMD -MP $(DEFINES) -02 -Wall
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= -s
endif

OBJECTS := \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Program.o \
	$(OBJDIR)/Shader.o \
	$(OBJDIR)/Texture.o \
	$(OBJDIR)/Bitmap.o \
	$(OBJDIR)/util.o \

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

$(OBJDIR)/Program.o: source/Program.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Shader.o: source/Shader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/util.o: source/util.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Texture.o: source/Texture.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Bitmap.o: source/Bitmap.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)