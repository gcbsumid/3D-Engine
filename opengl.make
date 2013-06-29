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
	COMPILER	= -std=c++11
	CPPFLAGS   += -MMD -MP $(DEFINES) -g -Wall $(INCLUDES) $(COMPILER)
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= 
	LIBS      += -lGL -lglfw -lGLEW
endif

ifeq ($(config),release)
	OBJDIR 		= obj/release
	TARGET 		= $(TARGETDIR)/program_debug.release
	DEFINES 	= -DNDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	COMPILER	= -std=c++11
	CPPFLAGS   += -MMD -MP $(DEFINES) -02 -Wall $(COMPILER)
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= -s
endif

OBJECTS := \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Program.o \
	$(OBJDIR)/Shader.o \
	$(OBJDIR)/Texture.o \
	$(OBJDIR)/Bitmap.o \
	$(OBJDIR)/Camera.o \
	$(OBJDIR)/Entity.o \
	$(OBJDIR)/EntityComponent.o \
	$(OBJDIR)/DrawComponent.o \
	$(OBJDIR)/CameraComponent.o \
	$(OBJDIR)/LightComponent.o \
	$(OBJDIR)/GraphicsSystem.o \
	$(OBJDIR)/InputSystem.o \
	$(OBJDIR)/Asset.o \
	$(OBJDIR)/Engine.o \
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

$(OBJDIR)/Camera.o: source/Camera.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Entity.o: source/Entity.cpp  
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/EntityComponent.o: source/EntityComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/DrawComponent.o: source/DrawComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/CameraComponent.o: source/CameraComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/LightComponent.o: source/LightComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/InputSystem.o: source/InputSystem.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/GraphicsSystem.o: source/GraphicsSystem.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Engine.o: source/Engine.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Asset.o: source/ModelAsset.cpp  
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)