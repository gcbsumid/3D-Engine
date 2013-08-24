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
GAMEDIR = src/Game
AIDIR = src/AI
INPUTDIR = src/Input
PHYSICSDIR = src/Physics
RENDERERDIR = src/Renderer
RESOURCEDIR = src/Resource
UTILDIR = src/Util

# Note: -fcolor-diagnostics, for some reason, is defaulted to false in Clang 3.4

ifeq ($(config),debug)
	OBJDIR 		= obj/debug
	TARGET 		= $(TARGETDIR)/program_debug.debug
	DEFINES 	= -DDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	COMPILER	= -std=c++11
	CPPFLAGS   += -MMD -MP $(DEFINES) -g -Wall $(INCLUDES) $(COMPILER)
	CXXFLAGS 	= $(CPPFLAGS) -fcolor-diagnostics -ferror-limit=5
	LDFLAGS 	= 
	LIBS       += -lGL -lglfw -lGLEW -lassimp
endif

ifeq ($(config),release)
	OBJDIR 		= obj/release
	TARGET 		= $(TARGETDIR)/program_debug.release
	DEFINES 	= -DNDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	COMPILER	= -std=c++11
	CPPFLAGS   += -MMD -MP $(DEFINES) -02 -Wall $(COMPILER)
	CXXFLAGS 	= $(CPPFLAGS) -fcolor-diagnostics -ferror-limit=5
	LDFLAGS 	= -s
	LIBS       += -lGL -lglfw -lGLEW -lassimp
endif

OBJECTS := \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Component.o \
	$(OBJDIR)/ComponentFactory.o \
	$(OBJDIR)/ModelAttrib.o \
	$(OBJDIR)/Engine.o \
	$(OBJDIR)/Entity.o \
	$(OBJDIR)/AIManager.o \
	$(OBJDIR)/AIComponent.o \
	$(OBJDIR)/Algorithm.o \
	$(OBJDIR)/RotateAlg.o \
	$(OBJDIR)/TranslateAlg.o \
	$(OBJDIR)/InputManager.o \
	$(OBJDIR)/GraphicsManager.o \
	$(OBJDIR)/CameraComponent.o \
	$(OBJDIR)/DrawComponent.o \
	$(OBJDIR)/LightComponent.o \
	$(OBJDIR)/Bitmap.o \
	$(OBJDIR)/Mesh.o \
	$(OBJDIR)/AABB.o \
	$(OBJDIR)/Program.o \
	$(OBJDIR)/Shader.o \
	$(OBJDIR)/Texture.o \
	$(OBJDIR)/ResourceManager.o \
	$(OBJDIR)/util.o \
	$(OBJDIR)/enum.o \

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

# ----------------------- Compile AI Folder --------------------------------- #

$(OBJDIR)/AIManager.o: $(AIDIR)/AIManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/AIComponent.o: $(AIDIR)/AIComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Algorithm.o: $(AIDIR)/Algorithm.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/RotateAlg.o: $(AIDIR)/RotateAlg.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/TranslateAlg.o: $(AIDIR)/TranslateAlg.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Game Folder ------------------------------- #

$(OBJDIR)/main.o: $(GAMEDIR)/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Engine.o: $(GAMEDIR)/Engine.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Entity.o: $(GAMEDIR)/Entity.cpp  
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Component.o: $(GAMEDIR)/Component.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/ComponentFactory.o: $(GAMEDIR)/ComponentFactory.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/ModelAttrib.o: $(GAMEDIR)/ModelAttrib.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Input Folder ------------------------------ #

$(OBJDIR)/InputManager.o: $(INPUTDIR)/InputManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Physics Folder ---------------------------- #

# ----------------------- Compile Renderer Folder --------------------------- #

$(OBJDIR)/DrawComponent.o: $(RENDERERDIR)/DrawComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/CameraComponent.o: $(RENDERERDIR)/CameraComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/LightComponent.o: $(RENDERERDIR)/LightComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/GraphicsManager.o: $(RENDERERDIR)/GraphicsManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Mesh.o: $(RENDERERDIR)/Mesh.cpp  
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Program.o: $(RENDERERDIR)/Program.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Shader.o: $(RENDERERDIR)/Shader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Texture.o: $(RENDERERDIR)/Texture.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Bitmap.o: $(RENDERERDIR)/Bitmap.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/AABB.o: $(RENDERERDIR)/AABB.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"


# ----------------------- Compile Resource Folder --------------------------- #

$(OBJDIR)/ResourceManager.o: $(RESOURCEDIR)/ResourceManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Util Folder ------------------------------- #

$(OBJDIR)/util.o: $(UTILDIR)/util.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/enum.o: $(UTILDIR)/enum.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- End of stuff -------------------------------------- #

-include $(OBJECTS:%.o=%.d)